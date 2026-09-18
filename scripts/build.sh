#!/usr/bin/env bash
set -euo pipefail

make clean
make
make check

echo
echo "DOVE build successful: build/dove.iso"
