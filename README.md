# Large Integer Problem

## Vấn đề số lớn:

Với các bài toán hiện đại, nhu cầu sử dụng các số nguyên lớn là rất lớn. Từ việc lưu trữ dữ liệu cho đến việc sinh khóa trong các hệ khóa bảo mật.

Một số ngôn ngữ lập trình hiện đại đã cung cắp các module built-in sẵn cho việc xử lí các số nguyên cực lớn, tuy nhiên nhiều ngôn ngữ hiện tại vẫn chưa hỗ trợ việc này.

Trong ngôn ngữ C++, kiểu dữ liệu unsigned long long là kiểu dữ liệu lưu được số lượng số chữ số cho số nguyên lớn nhất có sẵn (khoảng 20 chữ số), tuy nhiên, với nhu cầu thực tế, con số này có lẽ là chưa đáp ứng đủ (ví dụ việc sinh khóa trong các thuật toán mã hóa đôi khi cần số đến cở 2^2048 ~ 618 chữ số).

Để giải quyết vấn đề trên, tôi cung cắp một cách tiếp cận trên ngôn ngữ C++ với việc lưu mỗi chữ số trên 1 ô nhớ 1 byte (tức mỗi chữ số là 1 kí tự kiểu char).

## Ý tưởng cài đặt:

Với ngôn ngữ C++, thông qua lớp LargeInteger, ta có:

- Các chữ số của số lưu trên 1 vector<char> (đây là kiểu dữ liệu tiết kiệm nhất so với các loại khác).
- Số có thể được khởi tạo mặc định (null), khởi tạo thông qua một số nguyên dương lớn (kiểu unsigned long long), hoặc thông qua chuỗi (dành cho số có số chữ số lớn hơn 20).
- Các phép so sánh >, <, >=, <=, ==, != như trên số nguyên dương bình thường.
- Do chỉ biểu diễn các số nguyên lớn, tôi bỏ qua việc cài đặt số âm, do đó $range(n) = [0, +\infty)$
- Các phép toán cộng (+), trừ (-), nhân (\*), chia số nguyên (/), chia lấy dư mod (%).
  > Lưu ý: Chưa hỗ trợ các phép gán kèm phép tính +=, -=, _=, /=, %=
- Phép ghi >> vào một output stream và đọc << từ một input stream như số tự nhiên.
- Có thể thực hiện các phép toán số học (cộng, trừ, nhân, chia, mod) giữa số LargeInteger với số nguyên dương (unsigned long long hoặc unsigned int).

## Các phép so sánh:

### Phép so sánh hơn >, <

- Dựa trên cách so sánh tự nhiên.
- Số có số chữ số nhiều hơn thì lớn hơn.
- Giữa 2 số có cùng số chữ số, số nào có chữ số cùng một hàng lớn hơn là thì lớn hơn.

### Phép so sánh bằng hoặc hơn >=, <=

- Dựa trên phản đề của phép so sánh hơn:
  - $a \ge b \Leftrightarrow \neg(a < b)$
  - $a \le b \Leftrightarrow \neg(a > b)$

### Phép so sánh bằng và so sánh khác =, !=:

- 2 số bằng nhau nếu tất cả chữ số giống nhau
- Ngược lại thì khác nhau

## Các phép toán số học:

Chủ yếu được xây dựng trên phương pháp toán phổ thông:

### Phép cộng (+):

Được thực hiện bằng cách cộng từ chữ số từ phải qua trái của 2 số, quy tắc cộng như quy tắc cộng phổ thông (bao gồm cộng là lưu phần nhớ/cộng thừa vào lần cộng cho hàng kế).

### Phép trừ (-):

Tương tự như phép cộng, phép trừ được thực hiện bằng cách trừ lần lượt các chữ số từ phải qua trái của 2 số, mỗi lần trừ lưu ý trừ thêm phần đã mượn ở lần cộng trước (chữ số hàng trước của số bị trừ nhỏ hơn số trừ).

### Phép nhân (\*):

Được xây dựng dựa trên nguyên tắc nhân sắp hàng:

Giả sử:

$a = a_na_{n-1}...a_1a_0 = a_n \cdot 10^n + a_{n-1} \cdot 10^{n-1} + ... a_1^n + a_0$

$b = b_mb_{m-1}...b_1b_0 = b_m \cdot 10^m + b_{m-1} \cdot 10^{m-1} + ... b_1^n + b_0$

Khi đó $a \cdot b = \sum\limits_{i = 0, j = 0}^{n,m} a_i \cdot b_j * 10^{i + j}$

### Phép chia (/):

Được xây dựng bằng phương pháp chia số dài phổ thông:

1. Nhận một phần trong $Dividend$ từ trái sang phải như $SubDividend$ (đây là phần ngắn nhất từ trái qua phải thỏa $SubDividend > Divisor$)
2. Chia $SubDividend$ cho $Divisor$ bằng phương pháp chia chậm:
   - Trừ $SubDividend$ cho $Divisor$ cho đến khi không thể trừ được nữa
   - Hoặc lấy $quotient$ = 1, trong khi $quotient * Divisor \le SubDividend$ thì tăng quotient lên 1.
3. Lưu các chữ số trong $quotient$ vào kết quả, nếu chưa duyệt hết các chữ số của $Dividend$ thì thêm chữ số kế tiếp của $Dividend$ vào sau cùng của $SubDividend$, sau đó thực hiện bước 2, ngược lại trả về kết quả/.

### Phép modulo chia lấy dư (%):

Với việc thực hiện chia như trên, phần còn lại cuối cùng của $SubDividend$ sau khi thực hiện chia chính là phần dư.

## Người thực hiện:
Nguyễn Phúc Thuần - khoa Công nghệ thông tin, trường Đại học Khoa học Tự nhiên, ĐHQG-HCM
