# Báo cáo Đồ án — Sorting Benchmark

**Môn học:** Cấu trúc Dữ liệu và Giải thuật
**Học kỳ:** 2 — Năm học 2025–2026

| Họ tên | MSSV |
|---|---|
| Nguyễn Văn Phát | 25120410 |
| Lê Minh Nhân | 25120400 |
| Nguyễn Việt Quân | 25120425 |

---

## Mục lục

- [A. INT — Sắp xếp mảng số nguyên](#a-int--sắp-xếp-mảng-số-nguyên)
- [B. STRLEXI — Sắp xếp chuỗi theo thứ tự từ điển](#b-strlexi--sắp-xếp-chuỗi-theo-thứ-tự-từ-điển)
- [C. STRLENLEXI — Sắp xếp chuỗi theo độ dài rồi từ điển](#c-strlenlexi--sắp-xếp-chuỗi-theo-độ-dài-rồi-từ-điển)

---

## A. INT — Sắp xếp mảng số nguyên

### I. Lần chạy đầu tiên

Thuật toán được chọn là **Introsort** (Introspective Sort) — kết hợp Quick Sort, Heap Sort và Insertion Sort — thường là cài đặt nội bộ của `std::sort` trong STL.

#### Tổng quan thuật toán

- **Quick Sort** — thuật toán chính cho hầu hết trường hợp, hiệu năng trung bình O(N log N) rất tốt.
- **Heap Sort** — kích hoạt khi độ sâu đệ quy vượt `2·log₂(N)`, đảm bảo worst case luôn O(N log N).
- **Insertion Sort** — áp dụng cho các đoạn ≤ 24 phần tử; chi phí đệ quy của Quick/Heap Sort lớn hơn lợi ích trên đoạn nhỏ.

#### Các phương pháp tối ưu hóa

**Quick Sort:**
- **Median of Three** — pivot là trung vị của `left`, `mid`, `right`, giảm khả năng phân hoạch lệch.
- **3-way partition (Dutch National Flag)** — chia mảng thành `[ < pivot | = pivot | > pivot ]`; phần tử bằng pivot không tham gia đệ quy, giảm xuống O(N) khi toàn bộ phần tử giống nhau.

**Introsort kết hợp:**
- Insertion Sort khi đoạn ≤ 24 phần tử.
- Quick Sort khi độ sâu < `2·log₂(N)`.
- Heap Sort khi độ sâu ≥ `2·log₂(N)`.
- **Tail Recursion Elimination** — ưu tiên đệ quy nửa nhỏ hơn, nửa còn lại xử lý bằng vòng lặp, giảm độ sâu ngăn xếp.

#### Sinh dữ liệu kiểm thử (`test_gen.cpp`)

| Test | Mô tả | Thuật toán mục tiêu | Lý do |
|---|---|---|---|
| 1 | Ngẫu nhiên toàn miền `int` | Quick Sort, Merge Sort, Heap Sort | Mô phỏng dữ liệu thực tế, đánh giá average case |
| 2 | Giảm dần (N → 1) | Bubble Sort, Insertion Sort, Quick Sort pivot cố định | Worst case O(N²) cho các thuật toán lệch partition |
| 3 | Toàn phần tử trùng nhau | Quick Sort 2-way partition | Partition mất cân bằng → O(N²) |
| 4 | Xen kẽ `INT_MIN` và `INT_MAX` | Quick Sort, Merge Sort, Radix Sort | Kiểm tra xử lý giá trị biên, overflow, số âm |
| 5 | Tăng dần (1 → N) | Quick Sort pivot đầu/cuối cố định | Partition lệch hoàn toàn → O(N²) |

### II. Lần chạy thứ hai

Giữ nguyên **Introsort**, tối ưu hóa ở mức cài đặt.

**Tối ưu bổ sung — `inline` cho hàm `Trung_vi()`:**
Hàm được gọi mỗi lần phân hoạch; khai báo `inline` loại bỏ overhead gọi hàm (lưu địa chỉ trả về, thiết lập stack frame, nhảy đến hàm). Mức cải thiện trên một lần gọi nhỏ nhưng đáng kể do hàm được gọi rất nhiều lần.

> **Lưu ý:** `inline` chỉ là gợi ý cho compiler. GCC/Clang ở `-O2`/`-O3` thường tự inline hàm ngắn không cần khai báo tường minh.

---

## B. STRLEXI — Sắp xếp chuỗi theo thứ tự từ điển

### I. Lần chạy đầu tiên

Thuật toán được chọn là **Introsort tự cài đặt** — kết hợp Quick Sort, Heap Sort và Insertion Sort. Cách tự cài đặt cho phép kiểm soát hoàn toàn cách lưu chuỗi trong bộ nhớ và cách thực hiện phép so sánh.

#### Tổng quan thuật toán

- **Quick Sort** — thuật toán chính, O(N log N) trung bình, cache locality tốt.
- **Heap Sort** — kích hoạt khi độ sâu đệ quy vượt `2·log₂(N)`, đảm bảo worst case O(N log N).
- **Insertion Sort** — dùng cho đoạn ≤ 16 phần tử; chi phí gọi đệ quy lớn hơn lợi ích trên đoạn ngắn.

#### Các phương pháp tối ưu hóa

- **Introspective Depth Limit** — giới hạn độ sâu đệ quy tại `2·log₂(N)`; vượt ngưỡng tự động chuyển sang Heap Sort.
- **Insertion Sort cho đoạn nhỏ** — ngưỡng ≤ 16 phần tử, tận dụng tính liên tiếp của bộ nhớ.
- **Memory Pool** — toàn bộ chuỗi lưu trong một vùng nhớ liên tục; mảng chính chỉ lưu con trỏ. Khi sắp xếp, chỉ hoán đổi con trỏ thay vì sao chép nội dung chuỗi.
- **Heap Sort in-place** — hoạt động trực tiếp trên mảng con trỏ, không cấp phát thêm O(N) bộ nhớ phụ.

#### So sánh các phương án — Lý do chọn Introsort tự cài

Giới hạn bài: N ≤ 100.000, độ dài chuỗi 10–100 ký tự, tập `{a–z}`.

| Thuật toán | Nhược điểm với STRLEXI |
|---|---|
| Merge Sort | Tốn bộ nhớ phụ O(N); liên tục gán chép 10⁵ phần tử giữa mảng gốc và mảng tạm |
| Counting Sort | Không áp dụng được; không gian giá trị với chuỗi 100 ký tự là 26¹⁰⁰ |
| Radix Sort | O(L·N); với L_max = 100, N = 100.000 → xử lý ~10⁷ ký tự bất kể dữ liệu thực tế |
| Quick Sort 2-way | Nhiều phần tử trùng nhau → partition mất cân bằng → O(N²) |
| Heap Sort | O(N log N) an toàn nhưng Heapify nhảy index liên tục (i → 2i+1, 2i+2) → kém cache locality, chậm hơn Quick Sort 2–3 lần |
| **Introsort tự cài ✓** | 3-way partition loại rủi ro O(N²) với chuỗi trùng; in-place, chỉ swap con trỏ 4 byte; worst case O(N log N) |

#### Sinh dữ liệu kiểm thử (`test_gen.cpp`)

N = 100.000 chuỗi, độ dài 10–100, tập `a–z`. Seed cố định `mt19937 rng(999)`.

| Test | Mô tả | Thuật toán mục tiêu | Lý do |
|---|---|---|---|
| 1 | Ngẫu nhiên hoàn toàn (100 ký tự) | Quick Sort, Merge Sort, Heap Sort | Average case benchmark |
| 2 | Prefix `a` dài 90 ký tự, 10 ký tự cuối ngẫu nhiên | Các thuật toán so sánh tuần tự | Mỗi lần so sánh phải duyệt 90 bước → O(N·L·log N) |
| 3 | 100.000 chuỗi giống hệt nhau | Quick Sort 2-way partition | Partition lệch hoàn toàn → cây đệ quy tuyến tính → O(N²) (~10⁹ phép toán) |
| 4 | Giảm dần theo từ điển | Insertion Sort, Quick Sort pivot đầu/cuối | Insertion Sort dịch tối đa; Quick Sort partition hoàn toàn lệch |
| 5 | Prefix `z` dài 99 ký tự, 1 ký tự cuối ngẫu nhiên | Các thuật toán so sánh tuần tự | So sánh gần hết chuỗi mỗi lần; kết hợp Test 2 bao phủ nhiều kiểu prefix dài |

### II. Lần chạy thứ hai

Giữ nguyên cấu trúc Introsort, khắc phục hai điểm yếu cụ thể của lần 1.

**1. Thay 2-way partition bằng 3-way partition (Dutch National Flag)**

Lần 1 dùng 2-way partition: phần tử bằng pivot vẫn bị chia vào hai nửa và tiếp tục đệ quy → mất cân bằng → O(N²) khi nhiều chuỗi trùng nhau.

Lần 2 chia thành `[ < pivot | = pivot | > pivot ]`; phần tử bằng pivot xử lý xong trong một lần, không đệ quy vào lại.
**2. Thay hàm so sánh tự viết bằng `memcmp()`**

Hàm `cmp()` lần 1 dùng `while` so sánh từng ký tự một: chuỗi 90 ký tự prefix giống nhau cần 90 bước mỗi lần.

`memcmp()` được compiler và CPU tối ưu sẵn, so sánh 16–32 byte/lần. Với chuỗi 100 ký tự chỉ cần 4–7 lần thay vì 100. Để tránh gọi `strlen()` lặp lại, chương trình lưu thêm mảng `lens[]` chứa độ dài từng chuỗi.

---

## C. STRLENLEXI — Sắp xếp chuỗi theo độ dài rồi từ điển

### I. Lần chạy đầu tiên

Thuật toán được chọn là sự kết hợp của **Bucket Sort + LSD Radix Sort + Counting Sort**, tận dụng đặc điểm bài toán để đạt độ phức tạp gần tuyến tính.

#### Tổng quan thuật toán

- **Bucket Sort** — phân nhóm chuỗi theo độ dài vào 91 bucket (độ dài 10–100), loại bỏ nhu cầu so sánh độ dài trong các bước tiếp theo.
- **LSD Radix Sort** — sắp xếp từng bucket theo thứ tự từ điển, từ ký tự cuối đến ký tự đầu; chuỗi trong cùng bucket có cùng độ dài nên áp dụng trực tiếp.
- **Counting Sort** — thuật toán ổn định trong mỗi bước Radix Sort; tập ký tự chỉ có 26 giá trị → mảng đếm cố định 26 phần tử → O(N + 26) ≈ O(N).

#### Sự kết hợp các thuật toán

Bucket Sort (O(N)) xử lý tiêu chí độ dài → LSD Radix Sort xử lý tiêu chí từ điển từng bucket → Counting Sort đảm bảo tính ổn định. Cách kết hợp này tránh hầu hết các phép so sánh chuỗi tốn kém của Merge Sort hay Quick Sort.

**Lý do lựa chọn:** Bài toán có hai đặc điểm quan trọng — độ dài trong [10, 100] và ký tự trong {a–z} — cho phép dùng Bucket + Radix Sort để đạt độ phức tạp gần tuyến tính theo kích thước đầu vào.

#### Các phương pháp tối ưu hóa

**Bucket Sort:**
- 91 bucket cố định tương ứng từng độ dài, phân phối trực tiếp không cần so sánh.
- Lưu **chỉ số** của chuỗi thay vì sao chép dữ liệu vào bucket → giảm chi phí bộ nhớ.

**LSD Radix Sort:**
- Sắp xếp từ ký tự cuối đến đầu; không cần xử lý trường hợp thiếu ký tự vì chuỗi cùng bucket có cùng độ dài.
- Phân phối theo giá trị ký tự, tránh phép so sánh trực tiếp giữa hai chuỗi.

**Counting Sort:**
- Mảng đếm 26 phần tử khai báo cục bộ, tránh cấp phát động mỗi lần gọi.
- Mảng output khai báo `static`, tái sử dụng bộ nhớ giữa các lần gọi.
- Thao tác trên mảng chỉ số (kiểu `int`) thay vì đối tượng `string` → tăng hiệu quả cache CPU.
- Gộp toàn bộ output vào một chuỗi lớn qua biến `out` trước khi xuất → giảm số lần ghi ra luồng xuất.

#### Sinh dữ liệu kiểm thử (`test_gen.cpp`)

N = 10.000 chuỗi.

| Test | Mô tả | Mục tiêu |
|---|---|---|
| 1 | Ngẫu nhiên hoàn toàn (100 ký tự) | Average case benchmark |
| 2 | Tất cả chuỗi giống hệt nhau | Kiểm tra xử lý khóa trùng lặp nhiều |
| 3 | Giảm dần theo từ điển | Worst case cho O(N²) và Quick Sort pivot xấu |
| 4 | Prefix 99 ký tự `a`, 1 ký tự cuối ngẫu nhiên | Tăng chi phí phép so sánh chuỗi; phải duyệt gần hết chuỗi |
| 5 | Tăng dần theo từ điển | Worst case cho Quick Sort pivot đầu/cuối cố định |

**Thuật toán mục tiêu:**
- **Quick Sort** (pivot xấu) — test giảm dần/tăng dần → partition lệch → O(N²).
- **Insertion Sort** — test giảm dần → số lần dịch chuyển tối đa ≈ N·(N-1)/2.
- **Bubble Sort / Selection Sort** — luôn O(N²); test kích thước lớn làm nổi bật hiệu năng kém.
- **Thuật toán so sánh chuỗi** — test prefix dài → mỗi lần so sánh duyệt gần hết chuỗi, tăng đáng kể hằng số thời gian.

### II. Lần chạy thứ hai

# Thuật toán cài đặt tốt nhất ở lần thứ hai cùng các phương thức tối ưu hóa liên quan

Thuật toán được cài đặt ở lần chạy 2 là sự kết hợp của Merge Sort và Index Sorting.

## 1/ Tổng quan về thuật toán:

**a) Merge Sort:**
Thuật toán được sử dụng để thực hiện quá trình sắp xếp chính. Merge Sort hoạt động dựa trên nguyên lý chia để trị (Divide and Conquer), liên tục chia mảng thành các đoạn nhỏ hơn cho đến khi mỗi đoạn chỉ còn một phần tử, sau đó thực hiện quá trình trộn để tạo thành dãy đã được sắp xếp.

**b) Index Sorting:**
Thay vì sắp xếp trực tiếp các đối tượng string, chương trình sử dụng một mảng chỉ số `idx` để lưu vị trí của từng chuỗi trong dữ liệu gốc. Trong toàn bộ quá trình Merge Sort, thuật toán chỉ thao tác trên các giá trị nguyên của mảng `idx`.

**c) Comparator:**
Tiêu chí so sánh được xây dựng theo yêu cầu của đề bài. Chuỗi có độ dài nhỏ hơn sẽ đứng trước. Nếu hai chuỗi có cùng độ dài thì chuỗi có thứ tự từ điển nhỏ hơn sẽ đứng trước.

## 2/ Sự kết hợp các thuật toán:

Merge Sort được sử dụng làm thuật toán sắp xếp chính nhờ khả năng duy trì độ phức tạp O(nlogn) trong mọi trường hợp. Trong quá trình sắp xếp, thuật toán không thao tác trực tiếp trên dữ liệu chuỗi mà sử dụng kỹ thuật Index Sorting để giảm chi phí di chuyển dữ liệu.

Mỗi lần cần so sánh hai phần tử, chương trình truy cập đến chuỗi tương ứng thông qua chỉ số trong mảng `idx` và áp dụng tiêu chí so sánh đã xây dựng.

## 3/ Lý do lựa chọn: Tối ưu tiếp tục so với lần 1?

Mục tiêu của lần cài đặt thứ hai là tìm kiếm một phương án có khả năng giảm chi phí thao tác trên dữ liệu trong quá trình sắp xếp. 

So với việc di chuyển trực tiếp các đối tượng string, việc chỉ di chuyển các giá trị nguyên giúp giảm lượng dữ liệu phải xử lý trong mỗi bước Merge. Ngoài ra, việc tái sử dụng bộ nhớ và tối ưu quá trình so sánh giúp cải thiện hiệu năng thực tế của chương trình trên các bộ dữ liệu lớn.

Mặc dù độ phức tạp lý thuyết vẫn là O(nlogn), các phương pháp tối ưu hóa trên giúp giảm hệ số hằng số của thuật toán và nâng cao hiệu quả thực thi trong thực tế.

## 4/ Các phương pháp tối ưu hóa được sử dụng trong thuật toán:

**a) Đối với Merge Sort:**
- Thuật toán sử dụng một mảng `temp` được cấp phát duy nhất một lần trước khi thực hiện sắp xếp.
- Trong quá trình Merge, dữ liệu được ghi vào `temp` rồi sao chép trở lại `idx`.
- Việc tái sử dụng bộ nhớ giúp giảm chi phí cấp phát động nhiều lần.
- Merge Sort được lựa chọn vì luôn đảm bảo độ phức tạp O(nlogn) trong mọi trường hợp, tránh các trường hợp xấu có thể xảy ra ở một số thuật toán sắp xếp khác.

**b) Đối với Index Sorting:**
- Thay vì di chuyển trực tiếp các đối tượng string có độ dài từ 10 đến 100 ký tự, thuật toán chỉ di chuyển các giá trị nguyên trong mảng `idx`.
- Dữ liệu chuỗi được giữ nguyên vị trí trong bộ nhớ, giúp giảm đáng kể chi phí sao chép dữ liệu trong quá trình Merge.
- Việc thao tác trên dữ liệu kiểu `int` giúp tăng hiệu quả sử dụng cache của CPU do kích thước dữ liệu nhỏ và liên tục trong bộ nhớ.

**c) Đối với hàm so sánh:**
- Thuật toán ưu tiên so sánh độ dài chuỗi trước.
- Chỉ khi hai chuỗi có cùng độ dài mới thực hiện so sánh từ điển.
- Cách làm này giúp giảm số lần phải duyệt ký tự của chuỗi, đặc biệt hiệu quả khi dữ liệu chứa nhiều chuỗi có độ dài khác nhau.
- Dữ liệu được lưu trữ trong `vector` để tận dụng khả năng truy cập ngẫu nhiên O(1).
