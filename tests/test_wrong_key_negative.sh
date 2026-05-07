#!/usr/bin/env bash
set -euo pipefail

PT="0000111100001111000011110000111100001111000011110000111100001111"
RIGHT_KEY="1111000011110000111100001111000011110000111100001111000011110000"
WRONG_KEY="0000111100001111000011110000111100001111000011110000111100001111"

# Mã hóa bằng key đúng
CT=$(printf "1\n%s\n%s\n" "$PT" "$RIGHT_KEY" | ./des)

# Cố gắng giải mã bằng key sai
DECRYPTED=$(printf "2\n%s\n%s\n" "$CT" "$WRONG_KEY" | ./des)

if [[ "$DECRYPTED" != "$PT" ]]; then
  echo "[PASS] test_wrong_key_negative: Wrong key successfully failed to recover the plaintext."
else
  echo "[FAIL] test_wrong_key_negative: Wrong key unexpectedly recovered the plaintext!"
  exit 1
fi