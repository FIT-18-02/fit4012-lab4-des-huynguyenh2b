#!/usr/bin/env bash
set -euo pipefail

echo "==> Running Round-Trip Test..."
make all

KEY="0001001100110100010101110111100110011011101111001101111111110001"
PLAINTEXT="1010101010101010101010101010101010101010101010101010101010101010"

# Mã hóa và cắt lấy chuỗi kết quả (bỏ chữ "Result:")
CIPHER_OUT=$(./des encrypt "$KEY" "$PLAINTEXT")
CIPHERTEXT=$(echo "$CIPHER_OUT" | awk '{print $2}')

# Giải mã
DECRYPT_OUT=$(./des decrypt "$KEY" "$CIPHERTEXT")
DECRYPTED=$(echo "$DECRYPT_OUT" | awk '{print $2}')

if [[ "$DECRYPTED" == "$PLAINTEXT" ]]; then
  echo "[PASS] Round-trip test successful: Decrypted text matches original plaintext."
else
  echo "[FAIL] Round-trip mismatch."
  exit 1
fi