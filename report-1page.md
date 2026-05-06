# Report 1 page - Lab 4 DES / TripleDES

## Mục tiêu

Mục tiêu của bài lab là nắm vững và tự tay triển khai chi tiết thuật toán mã hóa khối DES (Data Encryption Standard). Từ bộ khung mã nguồn C++ ban đầu chỉ hỗ trợ mã hóa một khối 64-bit đơn giản, yêu cầu đặt ra là hoàn thiện chương trình thành một ứng dụng mã hóa toàn diện: hỗ trợ giải mã (decryption), xử lý dữ liệu kích thước lớn (multi-block) với tính năng đệm (padding), đồng thời xây dựng các kịch bản kiểm thử (test scripts) tự động để đánh giá tính đúng đắn và an toàn của thuật toán.

## Cách làm / Method

1. **Hoàn thiện hàm `decrypt`**: Xây dựng thuật toán giải mã bằng cách giữ nguyên cấu trúc mạng Feistel nhưng đảo ngược thứ tự sử dụng các khóa phụ (Round Keys từ 15 lùi về 0).
2. **Hỗ trợ Multi-block & Padding**:
    - Viết thêm hàm `pad_plaintext` áp dụng Zero-padding (thêm bit '0') cho các chuỗi đầu vào không chia hết cho 64-bit.
    - Triển khai chế độ **ECB (Electronic Codebook)** qua hai hàm `encrypt_ecb` và `decrypt_ecb`, cho phép cắt chuỗi dài thành các block 64-bit để xử lý tuần tự.
3. **Cập nhật giao diện CLI (`main`)**: Sử dụng `argc` và `argv` để chương trình có thể nhận lệnh linh hoạt từ terminal (ví dụ: `./des encrypt <key> <data>`), nhưng vẫn đảm bảo tính tương thích ngược với các test case cũ khi chạy không có tham số.
4. **Viết kịch bản kiểm thử (Bash Scripts)**: Tích hợp `Makefile` vào các script `.sh` để tự động biên dịch và kiểm thử các trường hợp: Round-trip, Multi-block padding, Negative test (Tamper và Wrong-key).

## Kết quả / Result

Chương trình đã chạy thành công qua toàn bộ các test cases đã thiết lập:
- **Test Sample gốc (`test_sample.sh`)**: [PASS] Trả về đúng ciphertext mẫu mong đợi `01111110...`.
- **Round-trip (`test_encrypt_decrypt_roundtrip.sh`)**: [PASS] Dữ liệu sau khi đi qua chu trình `Decrypt(Encrypt(Plaintext))` trùng khớp hoàn toàn với Plaintext gốc.
- **Multi-block Padding (`test_multiblock_padding.sh`)**: [PASS] Khi đầu vào là chuỗi 80-bit, chương trình tự động đệm thêm 48 bit '0' thành 2 khối 64-bit (128-bit). Quá trình mã hóa và giải mã diễn ra trơn tru mà không mất mát dữ liệu khối đầu.
- **Tamper Test (`test_tamper_negative.sh`)**: [PASS] Khi thử lật (flip) cố ý chỉ 1 bit đầu tiên của Ciphertext, kết quả giải mã bị sai lệch hoàn toàn so với bản rõ ban đầu, chứng minh được "hiệu ứng thác" (avalanche effect) và tính toàn vẹn của thuật toán.
- **Wrong Key Test (`test_wrong_key_negative.sh`)**: [PASS] Khi dùng sai khóa giải mã (chỉ sai lệch vài bit so với khóa gốc), chương trình không thể khôi phục lại Plaintext.

## Kết luận / Conclusion

- **Điều học được**: Bài lab giúp hiểu sâu sắc về cấu trúc mạng Feistel, cách thức hoạt động của hộp S-Box, hàm sinh khóa (Key Schedule), và quy trình kiểm thử phần mềm qua các kịch bản kiểm thử biên (negative testing).
- **Hạn chế hiện tại**: Chương trình đang sử dụng Zero-padding (có thể gây nhầm lẫn nếu chuỗi gốc vô tình kết thúc bằng nhiều bit '0') và đang chạy ở chế độ ECB (chế độ này không an toàn nếu các khối dữ liệu đầu vào giống hệt nhau).
- **Hướng mở rộng**: Trong tương lai, chương trình có thể được nâng cấp lên **TripleDES (3DES)** để chống lại các cuộc tấn công Brute-force hiện đại. Thay vì dùng chế độ ECB, có thể triển khai thêm chế độ **CBC (Cipher Block Chaining)** để tăng cường tính bảo mật cho dữ liệu multi-block, và áp dụng chuẩn padding PKCS#7 thay cho Zero-padding.