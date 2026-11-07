// Store SDKs (Steam, GOG Galaxy, Kongregate Kartridge) are not available on the Vita.
// Translated code drops store calls; this header exists for the few types the generator meets.
#pragma once
#include "cs.h"
using SteamAPIWarningMessageHook_t = std::function<void(int, String)>;
struct StringBuilder { String s; String ToString() const { return s; } };
