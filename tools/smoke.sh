#!/bin/bash
# Smoke test: boot normally (font already chosen), reach the main menu, then jump to each scene and run 5 s.
# Writes run/smoke/report.txt: scene, exit code (3 = hang watchdog), script error count, first error.
R=$(cd "$(dirname "$0")/.." && pwd)/run
mkdir -p $R/smoke
cd $R
: > smoke/report.txt
for s in ${@:-$(seq 1 134)}; do
  rm -rf smoke/save; mkdir -p smoke/save
  printf 'font\ts:pixel\nstati\ti:50\nmusic\ti:100\nsound\ti:100\nlang\ts:EN\n' > smoke/save/prefs.txt
  timeout 90 ../engine/out/pc/detest.exe ../data smoke/save 0 700 smoke/s$s.png --goto $s@380 > /dev/null 2>&1
  rc=$?
  n=$(grep -c "script error" smoke/save/log.txt 2>/dev/null)
  first=$(grep -m1 "script error\|HANG" smoke/save/log.txt 2>/dev/null | sed 's/\[script error\] //' | cut -c1-170)
  [ $rc -eq 3 ] && first="HANG: $(grep -A2 HANG smoke/save/log.txt | tail -2 | tr -s ' ' | tr '\n' ' ' | cut -c1-170)"
  echo "$s rc=$rc errors=$n $first" >> smoke/report.txt
done
awk '{split($3,a,"="); if (a[2]>0 || $2!="rc=0") bad++} END {print "scenes with problems:", bad+0, "of", NR}' smoke/report.txt
