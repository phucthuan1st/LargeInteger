# Large Integer Problem

## Vấn đề số lớn:

Với các bài toán hiện đại, nhu cầu sử dụng các số nguyên lớn là rất lớn. Từ việc lưu trữ dữ liệu cho đến việc sinh khóa trong các hệ khóa bảo mật.

Một số ngôn ngữ lập trình hiện đại đã cung cắp các module built-in sẵn cho việc xử lí các số nguyên cực lớn, tuy nhiên nhiều ngôn ngữ hiện tại vẫn chưa hỗ trợ việc này.

Trong ngôn ngữ C++, kiểu dữ liệu unsigned long long là kiểu dữ liệu lưu được số lượng số chữ số cho số nguyên lớn nhất có sẵn (khoảng 20 chữ số), tuy nhiên, với nhu cầu thực tế, con số này có lẽ là chưa đáp ứng đủ (ví dụ việc sinh khóa trong các thuật toán mã hóa đôi khi cần số đến cở 2^2048 ~ 618 chữ số).

Để giải quyết vấn đề trên, tôi cung cắp một cách tiếp cận trên ngôn ngữ C++ với việc lưu mỗi chữ số trên 1 ô nhớ 1 byte (tức mỗi chữ số là 1 kí tự kiểu char).

## Cài đặt:

Với ngôn ngữ C++, thông qua lớp LargeInteger, ta có:

- Các chữ số của số lưu trên 1 vector<char> (đây là kiểu dữ liệu tiết kiệm nhất so với các loại khác).
- Số có thể được khởi tạo mặc định (null), khởi tạo thông qua một số nguyên dương lớn (kiểu unsigned long long), hoặc thông qua chuỗi (dành cho số có số chữ số lớn hơn 20).
- Các phép so sánh >, <, >=, <=, ==, != như trên số nguyên dương bình thường.
- Do chỉ biểu diễn các số nguyên lớn, tôi bỏ qua việc cài đặt số âm, do đó $range(n) = [0, +\infty)$
- Các phép toán cộng (+), trừ (-), nhân (\*), chia số nguyên (/), chia lấy dư mod (%).
  > Lưu ý: Chưa hỗ trợ các phép gán kèm phép tính +=, -=, _=, /=, _=
- Phép ghi >> vào một output stream và đọc << từ một input stream như số tự nhiên.
- Có thể thực hiện các phép toán số học (cộng, trừ, nhân, chia, mod) giữa số LargeInteger với số nguyên dương (unsigned long long hoặc unsigned int).

## Các phép so sánh:

### Phép so sánh hơn >, <

- Dựa trên cách so sánh tự nhiên.
- Số có số chữ số nhiều hơn thì lớn hơn.
- Giữa 2 số có cùng số chữ số, số nào có chữ số cùng một hàng lớn hơn là thì lớn hơn.

### Phép so sánh bằng hoặc hơn >=, <=

- Dựa trên phản đề của phép so sánh hơn:
  - $a \ge b \Leftrightarrow !(a < b)$
  - $a \le b \Leftrightarrow !(a > b)$

### Phép so sánh bằng và so sánh khác:

- 2 số bằng nhau nếu tất cả chữ số giống nhau
- Ngược lại thì khác nhau
