#!/usr/bin/env bash
set -euo pipefail

echo "==> Running Sample DES Test..."
make all  # Tận dụng Makefile để build

EXPECTED="Ciphertext: 0111111010111111010001001001001100100011111110101111101011111000"
# Chạy binary ./des và lấy dòng cuối cùng
OUTPUT=$(./des | tail -n 1)

if [[ "$OUTPUT" == "$EXPECTED" ]]; then
  echo "[PASS] Sample DES output matches expected ciphertext."
else
  echo "[FAIL] Unexpected output."
  echo "Expected: $EXPECTED"
  echo "Got:      $OUTPUT"
  exit 1
fi