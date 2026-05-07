#!/usr/bin/env bash
set -euo pipefail

# Chuỗi 68 bit (64 bit block 1 + 4 bit block 2)
PT="11111111111111111111111111111111111111111111111111111111111111111010"
KEY="0001001100110100010101110111100110011011101111001101111111110001"

# Plaintext mong muốn sau khi được pad thêm 60 số 0 (để đủ 128 bit / 2 block)
PADDING=$(printf '0%.0s' {1..60})
EXPECTED_PT="${PT}${PADDING}"

CT=$(printf "1\n%s\n%s\n" "$PT" "$KEY" | ./des)

if [[ ${#CT} -ne 128 ]]; then
    echo "[FAIL] test_multiblock_padding: Expected ciphertext length of 128, got ${#CT}."
    exit 1
fi

DECRYPTED=$(printf "2\n%s\n%s\n" "$CT" "$KEY" | ./des)

if [[ "$DECRYPTED" == "$EXPECTED_PT" ]]; then
  echo "[PASS] test_multiblock_padding: Successfully encrypted and decrypted multi-block with zero padding."
else
  echo "[FAIL] test_multiblock_padding: Padded plaintext mismatch."
  exit 1
fi