#!/usr/bin/env bash
set -euo pipefail

PT="1010101010101010111100001111000011001100110011001000100010001000"
KEY="1111111111111111000000000000000011111111111111110000000000000000"

# Mã hóa
CT=$(printf "1\n%s\n%s\n" "$PT" "$KEY" | ./des)

# Giải mã
DECRYPTED=$(printf "2\n%s\n%s\n" "$CT" "$KEY" | ./des)

if [[ "$DECRYPTED" == "$PT" ]]; then
  echo "[PASS] test_encrypt_decrypt_roundtrip: Decrypted ciphertext correctly matches original plaintext."
else
  echo "[FAIL] test_encrypt_decrypt_roundtrip: Failed to recover original plaintext."
  exit 1
fi