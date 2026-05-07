# Report 1 page - Lab 4 DES / TripleDES

## Mục tiêu

Mục tiêu của bài lab là nghiên cứu và cài đặt chi tiết thuật toán mã hóa khối DES (Data Encryption Standard) và TripleDES (3DES). Thông qua bài tập này, tôi đã nắm vững cấu trúc mạng Feistel, quy trình sinh 16 khóa vòng (Round Keys), các phép biến đổi toán học như hoán vị (Permutation), thay thế (S-box) và cách thức xử lý dữ liệu thực tế thông qua cơ chế phân đoạn đa khối (multi-block) cùng kỹ thuật đệm dữ liệu (padding).

## Cách làm / Method

Tôi đã thực hiện phát triển và tối ưu hóa mã nguồn từ cấu trúc starter code như sau:
- **Phát triển Class KeyGenerator:** Cài đặt đầy đủ các bảng PC1, PC2 và logic dịch chuyển bit (left shifts) theo từng vòng để tạo ra 16 khóa con từ khóa 64-bit ban đầu.
- **Xây dựng cơ chế giải mã (Decryption):** Tái cấu trúc hàm xử lý khối để có thể chạy đảo ngược thứ tự các khóa vòng (từ vòng 16 về vòng 1), cho phép thực hiện giải mã dựa trên cùng một logic mạng Feistel của quá trình mã hóa.
- **Xử lý Đa khối & Zero Padding:** Cài đặt vòng lặp để chia nhỏ plaintext thành các khối 64-bit. Nếu khối cuối cùng không đủ độ dài, chương trình tự động chèn thêm các bit `0` (Zero Padding) cho đến khi đạt đủ kích thước khối chuẩn 64-bit.
- **Triển khai TripleDES:** Kết hợp các thực thể DES để thực hiện chuỗi thao tác mã hóa/giải mã theo đúng tiêu chuẩn 3DES (E-D-E).
- **Chuẩn hóa I/O:** Cài đặt hàm `main` để nhận dữ liệu qua `stdin` và xuất kết quả qua `stdout` theo đúng "Submission Contract" để phục vụ việc kiểm thử tự động bằng script và hệ thống CI.

## Kết quả / Result

Chương trình đã vượt qua tất cả các kịch bản kiểm thử quan trọng:
- **Test mẫu (Sample):** Mã hóa thành công dữ liệu mẫu từ yêu cầu bài lab, cho kết quả bản mã (ciphertext) khớp hoàn toàn với vector kiểm thử tiêu chuẩn.
- **Test khứ hồi (Round-trip):** Thực hiện mã hóa một chuỗi nhị phân và sau đó giải mã ngược lại, kết quả thu được bản rõ (plaintext) trùng khớp 100% với dữ liệu ban đầu.
- **Xử lý Multi-block:** Mã hóa chính xác các chuỗi bit có độ dài lớn (ví dụ 128 bit, 192 bit) và kiểm chứng cơ chế padding hoạt động đúng khi khối cuối bị lẻ bit.
- **Negative Tests:** Chứng minh được rằng khi giải mã với khóa sai hoặc khi dữ liệu bản mã bị thay đổi (tampered), chương trình sẽ trả về kết quả sai lệch hoàn toàn, khẳng định tính toàn vẹn và bảo mật của thuật toán.

## Kết luận / Conclusion

Thông qua bài Lab này, tôi đã rút ra được các kết luận sau:
- **Điều học được:** Hiểu sâu sắc sức mạnh của mạng Feistel trong việc tạo ra sự xáo trộn (confusion) và khuếch tán (diffusion) dữ liệu thông qua các vòng lặp đơn giản.
- **Hạn chế hiện tại:** Cơ chế Zero Padding tuy dễ cài đặt nhưng có thể gây nhầm lẫn nếu dữ liệu gốc kết thúc bằng các bit 0. Ngoài ra, việc sử dụng chế độ ECB (Electronic Codebook) vẫn còn tiềm ẩn nguy cơ lộ lộ mẫu dữ liệu khi mã hóa nhiều khối giống nhau.
- **Hướng mở rộng:** Trong tương lai, có thể nâng cấp lên các chuẩn đệm an toàn hơn như PKCS#7 và áp dụng các chế độ vận hành nâng cao như CBC (Cipher Block Chaining) để tăng cường khả năng chống lại các cuộc tấn công phân tích thống kê.