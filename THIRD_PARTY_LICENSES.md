# Third-party code

The Vita build uses these libraries. Their licences apply to their parts of the build.

| Library | Used for | Licence | Source |
|---|---|---|---|
| vitaGL (Rinnegatamante) | OpenGL on the Vita's GPU | LGPL-3.0 | https://github.com/Rinnegatamante/vitaGL |
| vitaShaRK (Rinnegatamante) | runtime shader compiling | LGPL-3.0 | https://github.com/Rinnegatamante/vitaShaRK |
| math-neon (Lachlan Tychsen-Smith) | NEON math, used by vitaGL | MIT | https://github.com/andrepuschmann/math-neon |
| zlib | texture decompression | zlib licence | https://zlib.net |
| stb_vorbis (Sean Barrett) | Ogg Vorbis decoding (`engine/src/third_party/stb_vorbis.c`) | public domain or MIT | https://github.com/nothings/stb |
| dr_mp3 (David Reid) | MP3 decoding (`engine/src/third_party/dr_mp3.h`) | public domain or MIT-0 | https://github.com/mackron/dr_libs |
| vitasdk (newlib, libstdc++, stubs) | toolchain and runtime | see vitasdk | https://github.com/vitasdk |

vitaGL and vitaShaRK are statically linked. This repository has the full source of the rest of the program, so the
eboot can be rebuilt against a modified copy of either library (LGPL-3.0, section 4).

The game's own content (art, sound, music, text and the original scripts) isn't covered by anything here. It belongs
to its owners.
