// Where did a script exception come from? On PC, resolve the call stack with dbghelp (first 300 only).
#include "cs.h"
#ifdef _WIN32
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#include <cstring>
namespace cs {
std::string captureStack() {
  static int budget = 300; static bool inited = false;
  if (budget <= 0) return std::string();
  budget--;
  HANDLE proc = GetCurrentProcess();
  if (!inited) { SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME); SymInitialize(proc, nullptr, TRUE); inited = true; }
  void* frames[24]; USHORT n = CaptureStackBackTrace(1, 24, frames, nullptr);
  std::string out; int shown = 0;
  for (USHORT i = 0; i < n && shown < 5; i++) {
    char buf[sizeof(SYMBOL_INFO) + 256]; SYMBOL_INFO* sym = (SYMBOL_INFO*)buf; memset(buf, 0, sizeof buf);
    sym->SizeOfStruct = sizeof(SYMBOL_INFO); sym->MaxNameLen = 255;
    DWORD64 addr = (DWORD64)frames[i]; DWORD64 disp = 0;
    if (!SymFromAddr(proc, addr, &disp, sym)) continue;
    std::string name = sym->Name;
    // skip the exception/pointer plumbing
    if (name.find("Exception") != std::string::npos || name.find("throwNull") != std::string::npos || name.find("captureStack") != std::string::npos ||
        name.find("cs::P<") == 0 || name.find("cs::Array<") == 0 || name.find("cs::List<") == 0 || name.find("cs::String::") == 0) continue;
    IMAGEHLP_LINE64 line; memset(&line, 0, sizeof line); line.SizeOfStruct = sizeof line; DWORD ld = 0;
    std::string where;
    if (SymGetLineFromAddr64(proc, addr, &ld, &line)) { const char* f = strrchr(line.FileName, '\\'); where = std::string(f ? f + 1 : line.FileName) + ":" + std::to_string(line.LineNumber); }
    out += (shown ? " <- " : " at ") + name + (where.empty() ? "" : " (" + where + ")");
    shown++;
    if (name.find("engine::frame") != std::string::npos) break;
  }
  return out;
}
}
// Hang watchdog (PC): if a frame runs longer than 5 s, print the game thread's call stack and exit.
#include <thread>
#include <atomic>
#include <cstdio>
namespace cs {
static std::atomic<long long> beatMs{ 0 };
static HANDLE gameThread = nullptr;
static long long tickMs() { return (long long)GetTickCount64(); }
void watchdogBeat() { beatMs = tickMs(); }
void watchdogStart() {
  DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &gameThread, 0, FALSE, DUPLICATE_SAME_ACCESS);
  beatMs = tickMs();
  std::thread([] {
    for (;;) {
      Sleep(500);
      if (tickMs() - beatMs < 5000) continue;
      SuspendThread(gameThread);
      CONTEXT ctx; memset(&ctx, 0, sizeof ctx); ctx.ContextFlags = CONTEXT_FULL; GetThreadContext(gameThread, &ctx);
      HANDLE proc = GetCurrentProcess(); SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME); SymInitialize(proc, nullptr, TRUE);
      STACKFRAME64 sf; memset(&sf, 0, sizeof sf);
      sf.AddrPC.Offset = ctx.Rip; sf.AddrFrame.Offset = ctx.Rbp; sf.AddrStack.Offset = ctx.Rsp;
      sf.AddrPC.Mode = sf.AddrFrame.Mode = sf.AddrStack.Mode = AddrModeFlat;
      std::string out = "HANG: game thread stuck for 5 s:\n";
      for (int i = 0; i < 40 && StackWalk64(IMAGE_FILE_MACHINE_AMD64, proc, gameThread, &sf, &ctx, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr); i++) {
        char buf[sizeof(SYMBOL_INFO) + 256]; SYMBOL_INFO* sym = (SYMBOL_INFO*)buf; memset(buf, 0, sizeof buf); sym->SizeOfStruct = sizeof(SYMBOL_INFO); sym->MaxNameLen = 255;
        DWORD64 disp = 0; IMAGEHLP_LINE64 line; memset(&line, 0, sizeof line); line.SizeOfStruct = sizeof line; DWORD ld = 0;
        std::string name = SymFromAddr(proc, sf.AddrPC.Offset, &disp, sym) ? sym->Name : "?";
        std::string where; if (SymGetLineFromAddr64(proc, sf.AddrPC.Offset, &ld, &line)) { const char* f = strrchr(line.FileName, '\\'); where = std::string(f ? f + 1 : line.FileName) + ":" + std::to_string(line.LineNumber); }
        out += "  " + name + (where.empty() ? "" : " (" + where + ")") + "\n";
      }
      cs::log("%s", out.c_str());
      fflush(stdout); TerminateProcess(GetCurrentProcess(), 3);
    }
  }).detach();
}
}
#else
namespace cs { std::string captureStack() { return std::string(); } void watchdogStart() {} void watchdogBeat() {} }
#endif
