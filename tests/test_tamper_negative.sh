#!/usr/bin/env bash
set -euo pipefail

PT="1111000011110000111100001111000011110000111100001111000011110000"
KEY="0000000000000000000000000000000011111111111111111111111111111111"

CT=$(printf "1\n%s\n%s\n" "$PT" "$KEY" | ./des)

# Lật bit đầu tiên của bản mã
FIRST_BIT=${CT:0:1}
if [[ "$FIRST_BIT" == "0" ]]; then
    TAMPERED_CT="1${CT:1}"
else
    TAMPERED_CT="0${CT:1}"
fi

DECRYPTED=$(printf "2\n%s\n%s\n" "$TAMPERED_CT" "$KEY" | ./des)

if [[ "$DECRYPTED" != "$PT" ]]; then
  echo "[PASS] test_tamper_negative: Tampered ciphertext successfully failed to produce original plaintext."
else
  echo "[FAIL] test_tamper_negative: Tampered ciphertext incorrectly reproduced the plaintext!"
  exit 1
fi