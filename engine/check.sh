#!/bin/bash
# Compile-check translated classes: ./check.sh ClassA [ClassB ...]  -> prints only errors, "OK <Class>" when clean
for c in "$@"; do
  out=$(cmd.exe //c "$(cygpath -w "$(dirname "$0")")\check.bat $c" 2>&1 | tr -d '\r' | grep -E "error|fatal" | sed 's/ (compiling source file.*//' | head -40)
  if [ -z "$out" ]; then echo "OK $c"; else echo "$out"; fi
done
