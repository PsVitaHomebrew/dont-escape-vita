#!/bin/bash
# Builds the Vita eboot and VPK for Don't Escape (title ID DESC00001).
# Usage: ./build_vita.sh          (build + package VPK)
#        NOVPK=1 ./build_vita.sh  (just eboot.bin, for FTP updates)
#        JOBS=6 ./build_vita.sh   (parallel compiles, default 6)
set -e
R=$(cd "$(dirname "$0")/.." && pwd)
E=$R/engine
VSDK=${VITASDK:-/usr/local/vitasdk}
B=$VSDK/bin
OUT=$E/out/vita
JOBS=${JOBS:-6}
mkdir -p $OUT/obj
SRCS="$E/src/cs.cpp $E/src/stacktrace.cpp $E/src/engine.cpp $E/src/audio.cpp $E/src/main_vita.cpp"
SRCS="$SRCS $E/src/game/registry.gen.cpp $(ls $E/src/game/game_*.cpp)"
CXXFLAGS="-O2 -std=gnu++17 -Wno-psabi -fno-strict-aliasing -I$E/src -DVITA"
NEWEST_H=$(find $E/src -name '*.h' -printf '%T@\n' | sort -n | tail -1)
NEWEST_GAME=$(find $E/src/game/cpp $E/src/game/stubs -printf '%T@\n' 2>/dev/null | sort -n | tail -1)
OBJS=""; TODO=""
for s in $SRCS; do
  o=$OUT/obj/$(basename ${s%.cpp}).o
  OBJS="$OBJS $o"
  if [ ! -f "$o" ]; then TODO="$TODO $s"; continue; fi
  ot=$(stat -c %Y "$o")
  st=$(stat -c %Y "$s")
  if [ "$st" -gt "$ot" ] || [ "${NEWEST_H%.*}" -gt "$ot" ]; then TODO="$TODO $s"; continue; fi
  if [[ "$s" == *game_* ]] && [ "${NEWEST_GAME%.*}" -gt "$ot" ]; then TODO="$TODO $s"; fi
done
if [ -n "$TODO" ]; then
  echo "compiling $(echo $TODO | wc -w) files with $JOBS jobs"
  printf '%s\n' $TODO | xargs -P $JOBS -I{} sh -c 'f="{}"; o="'$OUT'/obj/$(basename "${f%.cpp}").o"; "'$B'/arm-vita-eabi-g++" '"$CXXFLAGS"' -c "$f" -o "$o" || { echo "FAILED $f"; exit 255; }'
fi
echo link
$B/arm-vita-eabi-g++ -Wl,-q -o $OUT/DontEscape.elf $OBJS \
  -lvitaGL -lvitashark -lSceShaccCgExt -lmathneon -ltaihen_stub -lSceShaccCg_stub -lSceKernelDmacMgr_stub \
  -lSceGxm_stub -lSceDisplay_stub -lSceCtrl_stub -lSceTouch_stub -lSceAudio_stub -lSceAppUtil_stub -lSceAppMgr_stub \
  -lSceCommonDialog_stub -lScePower_stub -lSceSysmodule_stub -lSceIofilemgr_stub -lSceLibKernel_stub \
  -lz -lstdc++ -lm -lc -lpthread
$B/vita-elf-create $OUT/DontEscape.elf $OUT/DontEscape.velf >/dev/null
$B/vita-make-fself -s -c $OUT/DontEscape.velf $OUT/eboot.bin
echo "eboot: $(stat -c %s $OUT/eboot.bin) bytes"
[ -n "$NOVPK" ] && exit 0
STAGE=$OUT/vpk; rm -rf $STAGE; mkdir -p $STAGE/sce_sys
cp $OUT/eboot.bin $STAGE/eboot.bin
$B/vita-mksfoex -s TITLE_ID=DESC00001 -d ATTRIBUTE2=12 "Don't Escape" $STAGE/sce_sys/param.sfo
node $R/tools/livearea/make_art.js $STAGE/sce_sys >/dev/null
cd $STAGE && rm -f $OUT/DontEscape.vpk && $B/vita-pack-vpk -s sce_sys/param.sfo -b eboot.bin \
  -a sce_sys/icon0.png=sce_sys/icon0.png -a sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
  -a sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
  -a sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml $OUT/DontEscape.vpk
echo "vpk: $OUT/DontEscape.vpk ($(stat -c %s $OUT/DontEscape.vpk) bytes)"
