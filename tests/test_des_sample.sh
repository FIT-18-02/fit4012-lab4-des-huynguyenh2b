#!/usr/bin/env bash
set -euo pipefail

PT="0001001000110100010101100111100010011010101111001101111011110001"
KEY="0001001100110100010101110111100110011011101111001101111111110001"
EXPECTED="0111111010111111010001001001001100100011111110101111101011111000"

# Truyền Mode 1, Plaintext và Key qua stdin
CT=$(printf "1\n%s\n%s\n" "$PT" "$KEY" | ./des)

if [[ "$CT" == "$EXPECTED" ]]; then
  echo "[PASS] test_des_sample: Ciphertext matches the expected standard output."
else
  echo "[FAIL] test_des_sample: Output did not match expected."
  echo "Expected: $EXPECTED"
  echo "Got:      $CT"
  exit 1
fi