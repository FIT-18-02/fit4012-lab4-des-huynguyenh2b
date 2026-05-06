#!/usr/bin/env bash
set -euo pipefail

echo "==> Running Original Sample Test..."
make all

EXPECTED="Ciphertext: 0111111010111111010001001001001100100011111110101111101011111000"

OUTPUT=$(./des)
LAST_LINE=$(printf "%s\n" "$OUTPUT" | tail -n 1)

if [[ "$LAST_LINE" != "$EXPECTED" ]]; then
  echo "[FAIL] Unexpected ciphertext output"
  echo "Expected: $EXPECTED"
  echo "Actual:   $LAST_LINE"
  exit 1
fi

echo "[PASS] Sample DES program produced the expected ciphertext."