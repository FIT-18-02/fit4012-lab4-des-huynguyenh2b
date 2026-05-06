#!/usr/bin/env bash
set -euo pipefail

echo "==> Running Wrong Key (Negative) Test..."
make all

CORRECT_KEY="0001001100110100010101110111100110011011101111001101111111110001"
# Khóa sai: Đảo 4 bit đầu tiên
WRONG_KEY="1111001100110100010101110111100110011011101111001101111111110001"
PLAINTEXT="0001001000110100010101100111100010011010101111001101111011110001"

CIPHER_OUT=$(./des encrypt "$CORRECT_KEY" "$PLAINTEXT")
CIPHERTEXT=$(echo "$CIPHER_OUT" | awk '{print $2}')

DECRYPT_OUT=$(./des decrypt "$WRONG_KEY" "$CIPHERTEXT")
DECRYPTED=$(echo "$DECRYPT_OUT" | awk '{print $2}')

if [[ "$DECRYPTED" != "$PLAINTEXT" ]]; then
  echo "[PASS] Wrong key test successful. Cannot recover plaintext with the wrong key."
else
  echo "[FAIL] Wrong key test failed."
  exit 1
fi