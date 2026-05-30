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

Lần 2 chia thành `[ < pivot | = pivot | > pivot ]`; phần tử bằng pivot xử lý xong trong một lần, không đệ quy vào lại. Test 3 giảm từ timeout (O(N²)) về ~25 ms.

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

Thuật toán được chọn là **Merge Sort + Index Sorting**.

#### Tổng quan thuật toán

- **Merge Sort** — O(N log N) trong mọi trường hợp, tránh worst case của Quick Sort. Dùng mảng `temp` được cấp phát **một lần duy nhất** trước khi sắp xếp, tái sử dụng qua tất cả bước Merge.
- **Index Sorting** — sắp xếp trên mảng chỉ số `idx` (kiểu `int`) thay vì trực tiếp trên đối tượng `string`. Dữ liệu chuỗi giữ nguyên vị trí trong bộ nhớ → chi phí sao chép trong mỗi bước Merge giảm đáng kể; thao tác trên `int` nhỏ và liên tục → tăng hiệu quả cache CPU.
- **Comparator** — ưu tiên so sánh **độ dài** trước; chỉ so sánh từ điển khi hai chuỗi cùng độ dài, giảm số lần phải duyệt ký tự khi dữ liệu có nhiều chuỗi khác độ dài.

#### Tối ưu tiếp tục so với lần 1

Lần 1 (Bucket + Radix + Counting Sort) hiệu quả theo lý thuyết nhưng phức tạp về cài đặt và phụ thuộc nhiều vào đặc điểm phân phối dữ liệu. Lần 2 chọn hướng đơn giản hơn nhưng vẫn tối ưu hóa hệ số hằng số:

- **Một lần cấp phát bộ nhớ** cho mảng `temp` thay vì cấp phát động nhiều lần trong Merge.
- **Thao tác trên `int`** thay vì `string` → dữ liệu nhỏ hơn, liên tục hơn trong bộ nhớ.
- **So sánh độ dài trước** → tránh duyệt ký tự không cần thiết khi hai chuỗi khác độ dài.
- Lưu trữ trong `vector` để truy cập ngẫu nhiên O(1).

Mặc dù độ phức tạp lý thuyết vẫn là O(N log N), các tối ưu trên giảm hệ số hằng số và cải thiện hiệu năng thực tế trên dữ liệu lớn.
