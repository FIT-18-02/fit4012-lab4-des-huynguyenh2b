#!/usr/bin/env bash
set -euo pipefail

echo "==> Running Multi-block & Padding Test..."
make all

KEY="0001001100110100010101110111100110011011101111001101111111110001"
# 80 bits plaintext (1 block đầy + 16 bit dư)
PLAINTEXT="11110000111100001111000011110000111100001111000011110000111100001010101010101010"
# Cần padding thêm 48 số 0 để đủ 128 bits (2 blocks)
EXPECTED_PADDED="${PLAINTEXT}000000000000000000000000000000000000000000000000"

CIPHER_OUT=$(./des encrypt "$KEY" "$PLAINTEXT")
CIPHERTEXT=$(echo "$CIPHER_OUT" | awk '{print $2}')

DECRYPT_OUT=$(./des decrypt "$KEY" "$CIPHERTEXT")
DECRYPTED=$(echo "$DECRYPT_OUT" | awk '{print $2}')

if [[ "$DECRYPTED" == "$EXPECTED_PADDED" ]]; then
  echo "[PASS] Multi-block padding successful. Padding verified."
else
  echo "[FAIL] Padding test failed."
  echo "Expected: $EXPECTED_PADDED"
  echo "Got:      $DECRYPTED"
  exit 1
fi