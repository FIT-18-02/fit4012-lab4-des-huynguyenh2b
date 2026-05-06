#!/usr/bin/env bash
set -euo pipefail

echo "==> Running Tamper (Negative) Test..."
make all

KEY="0001001100110100010101110111100110011011101111001101111111110001"
PLAINTEXT="0001001000110100010101100111100010011010101111001101111011110001"

CIPHER_OUT=$(./des encrypt "$KEY" "$PLAINTEXT")
CIPHERTEXT=$(echo "$CIPHER_OUT" | awk '{print $2}')

# Tamper: Đảo ngược bit đầu tiên của ciphertext (0 thành 1, 1 thành 0)
FIRST_BIT=${CIPHERTEXT:0:1}
if [[ "$FIRST_BIT" == "0" ]]; then
    TAMPERED_CIPHER="1${CIPHERTEXT:1}"
else
    TAMPERED_CIPHER="0${CIPHERTEXT:1}"
fi

DECRYPT_OUT=$(./des decrypt "$KEY" "$TAMPERED_CIPHER")
DECRYPTED=$(echo "$DECRYPT_OUT" | awk '{print $2}')

if [[ "$DECRYPTED" != "$PLAINTEXT" ]]; then
  echo "[PASS] Tamper test successful. Changing 1 bit completely corrupted the plaintext."
else
  echo "[FAIL] Tamper test failed. Decryption somehow worked."
  exit 1
fi