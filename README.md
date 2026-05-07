[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/B72A5Yyp)
# FIT4012 - Lab 4: DES / TripleDES Starter Repository

Repo này là **starter repo** cho Lab 4 của FIT4012.

## 1. Cấu trúc repo

```text
.
├── .github/
│   ├── scripts/
│   │   └── check_submission.sh
│   └── workflows/
│       └── ci.yml
├── logs/
│   ├── .gitkeep
│   └── README.md
├── scripts/
│   └── run_sample.sh
├── tests/
│   ├── test_des_sample.sh
│   ├── test_encrypt_decrypt_roundtrip.sh
│   ├── test_multiblock_padding.sh
│   ├── test_tamper_negative.sh
│   └── test_wrong_key_negative.sh
├── .gitignore
├── CMakeLists.txt
├── Makefile
├── README.md
├── des.cpp
└── report-1page.md
```

## 2. Cách chạy chương trình (How to run)

### Cách 1: Dùng Makefile

```bash
make
./des
```

### Cách 2: Biên dịch trực tiếp

```bash
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
./des
```

### Cách 3: Dùng CMake

```bash
cmake -S . -B build
cmake --build build
./build/des
```

## 3. Input / Đầu vào

Chương trình được thiết kế để nhận dữ liệu tương tác trực tiếp từ bàn phím thông qua luồng nhập chuẩn (`stdin`).

- **Cách nhập Plaintext/Ciphertext:** Người dùng nhập trực tiếp một chuỗi các ký tự nhị phân (`0` và `1`). Chương trình sẽ đọc toàn bộ chuỗi này để xử lý.
- **Cách nhập Key:** Khóa được nhập dưới dạng chuỗi nhị phân. Đối với chế độ DES, yêu cầu nhập 01 khóa 64-bit. Đối với chế độ TripleDES, yêu cầu nhập lần lượt 03 khóa riêng biệt (K1, K2, K3), mỗi khóa dài đúng 64-bit.
- **Xử lý khối (Block processing):** Chương trình hỗ trợ xử lý nhiều block (multi-block). Nếu dữ liệu đầu vào có độ dài vượt quá 64 bit, chương trình sẽ tự động chia nhỏ thành các khối 64-bit để tiến hành mã hóa hoặc giải mã tuần tự.
- **Định dạng dữ liệu:** Dữ liệu hoàn toàn là chuỗi bit (binary string). Chương trình không nhận trực tiếp file hay chuỗi ký tự ASCII thông thường để tập trung vào việc mô phỏng chính xác thuật toán.

## 4. Output / Đầu ra

Kết quả đầu ra của chương trình được tối ưu để hiển thị rõ ràng và phục vụ việc tự động chấm điểm (CI).

- **Hiển thị Ciphertext / Plaintext:** Kết quả cuối cùng (bản mã hoặc bản rõ) được in ra dưới dạng một chuỗi nhị phân dài liên tục trên một dòng duy nhất, không chứa khoảng trắng hay ký tự thừa.
- **Round Keys:** Để đảm bảo output sạch sẽ cho hệ thống đối chiếu tự động, chương trình **không** in ra các round keys hay các bước tính toán trung gian.
- **Hỗ trợ giải mã:** Chương trình hỗ trợ đầy đủ tính năng giải mã ngược lại thành plaintext ban đầu cho cả DES và TripleDES.
- **Kết quả TripleDES:** Đầu ra là một chuỗi nhị phân đã trải qua toàn bộ chuỗi 3 phép toán mã hóa/giải mã tương ứng (ví dụ: `E(K3, D(K2, E(K1, P)))` đối với mã hóa 3DES).

## 5. Padding đang dùng

Chương trình sử dụng cơ chế **Zero Padding** để đảm bảo dữ liệu đầu vào luôn vừa vặn với kích thước khối chuẩn của thuật toán DES.

- **Cơ chế chia block và đệm:** Nếu chuỗi plaintext đầu vào dài hơn 64 bit, nó sẽ được cắt tuần tự thành các block 64-bit. Nếu block cuối cùng bị thiếu bit (độ dài không chia hết cho 64), chương trình sẽ tự động chèn thêm các ký tự `0` vào phía cuối khối đó cho đến khi đủ 64 bit.
- **Hạn chế của Zero Padding:** Nhược điểm lớn nhất là tính nhập nhằng (ambiguity) khi giải mã. Nếu bản thân dữ liệu gốc đã kết thúc bằng một hoặc nhiều bit `0`, sau khi giải mã, hệ thống không thể phân biệt được đâu là dữ liệu gốc và đâu là bit đệm được thêm vào.
- **Mục đích sử dụng:** Cách padding này chỉ phù hợp cho các bài học nhập môn hoặc môi trường học thuật vì nó dễ cài đặt, giúp sinh viên hiểu rõ luồng chạy của thuật toán mã hóa khối. Trong thực tế bảo mật (production), các chuẩn padding như PKCS#7 sẽ được sử dụng để giải quyết triệt để vấn đề nhập nhằng và an toàn hơn.

## 6. Tests bắt buộc

Repo này đã tạo sẵn **5 tên file test mẫu** để sinh viên điền nội dung:

- `tests/test_des_sample.sh`
- `tests/test_encrypt_decrypt_roundtrip.sh`
- `tests/test_multiblock_padding.sh`
- `tests/test_tamper_negative.sh`
- `tests/test_wrong_key_negative.sh`

Sinh viên phải tự hoàn thiện test và bổ sung minh chứng chạy.

## 7. Logs / Minh chứng

Thư mục `logs/` dùng để nộp minh chứng, ví dụ:
- ảnh chụp màn hình khi chạy chương trình
- output của test
- log thử đúng / sai key / tamper
- log cho mã hóa nhiều block

## 8. Ethics & Safe use

- Chỉ chạy và kiểm thử trên dữ liệu học tập hoặc dữ liệu giả lập.
- Không dùng repo này để tấn công hay can thiệp hệ thống thật.
- Không trình bày đây là công cụ bảo mật sẵn sàng cho môi trường sản xuất.
- Nếu tham khảo mã, tài liệu, công cụ hoặc AI, phải ghi nguồn rõ ràng.
- Khi cộng tác nhóm, cần trung thực học thuật và mô tả đúng phần việc của mình.
- Việc kiểm thử chỉ phục vụ học DES / TripleDES ở mức nhập môn.

## 9. Checklist nộp bài

Trước khi nộp, cần có:
- `des.cpp`
- `README.md` hoàn chỉnh
- `report-1page.md` hoàn chỉnh
- `tests/` với ít nhất 5 test
- có negative test cho `tamper` và `wrong key`
- `logs/` có ít nhất 1 file minh chứng thật
- không còn dòng `TODO_STUDENT`

## 10. Lưu ý về CI

CI sẽ **không chỉ kiểm tra file có tồn tại** mà còn kiểm tra:
- các mục bắt buộc trong README
- các mục bắt buộc trong report
- sự hiện diện của negative tests
- có minh chứng trong `logs/`
- repo **không còn placeholder `TODO_STUDENT`**

Vì vậy repo starter này sẽ **chưa pass CI** cho tới khi sinh viên hoàn thiện nội dung.


## 11. Submission contract để auto-check Q2 và Q4

Để GitHub Actions kiểm tra được **Q2** và **Q4**, repo này dùng **một contract nhập/xuất thống nhất**.
Sinh viên cần sửa `des.cpp` để chương trình nhận dữ liệu từ **stdin** theo đúng thứ tự sau:

```text
Chọn mode:
1 = DES encrypt
2 = DES decrypt
3 = TripleDES encrypt
4 = TripleDES decrypt
```

### Mode 1: DES encrypt
Nhập lần lượt:
1. `1`
2. plaintext nhị phân
3. key 64-bit

Yêu cầu:
- nếu plaintext dài hơn 64 bit: chia block 64 bit và mã hóa tuần tự
- nếu block cuối thiếu bit: zero padding
- in ra **ciphertext cuối cùng** dưới dạng chuỗi nhị phân

### Mode 2: DES decrypt
Nhập lần lượt:
1. `2`
2. ciphertext nhị phân
3. key 64-bit

Yêu cầu:
- giải mã DES theo round keys đảo ngược
- in ra plaintext cuối cùng

### Mode 3: TripleDES encrypt
Nhập lần lượt:
1. `3`
2. plaintext 64-bit
3. `K1`
4. `K2`
5. `K3`

Yêu cầu:
- thực hiện đúng chuỗi **E(K3, D(K2, E(K1, P)))**
- in ra ciphertext cuối cùng

### Mode 4: TripleDES decrypt
Nhập lần lượt:
1. `4`
2. ciphertext 64-bit
3. `K1`
4. `K2`
5. `K3`

Yêu cầu:
- thực hiện giải mã TripleDES ngược lại
- in ra plaintext cuối cùng

### Lưu ý về output
- Có thể in prompt tiếng Việt hoặc tiếng Anh.
- Có thể in thêm round keys hay thông báo trung gian.
- Nhưng **kết quả cuối cùng phải xuất hiện dưới dạng một chuỗi nhị phân dài hợp lệ** để CI tách và đối chiếu.

## 14. CI hiện kiểm tra được gì

Ngoài checklist nộp bài, CI hiện còn kiểm tra tự động:
- chương trình thực sự nhận plaintext/key từ bàn phím và mã hóa multi-block với zero padding đúng.
- chương trình thực sự mã hóa và giải mã TripleDES đúng theo vector kiểm thử.

Nói cách khác, nếu sinh viên chỉ sửa README/tests cho đủ hình thức mà **không làm Q2 hoặc Q4**, CI sẽ vẫn fail.
