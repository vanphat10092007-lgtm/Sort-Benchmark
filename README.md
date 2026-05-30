# Sort-Benchmark

BÁO CÁO ĐỒ ÁN 
SORTING BENCHMARK

Môn học: Cấu trúc Dữ liệu và Giải thuật
Học kỳ 2 — Năm học: 2025–2026
Nguyễn Văn Phát – 25120410
Lê Minh Nhân – 25120400
Nguyễn Việt Quân – 25120425

 
A. INT — Sắp xếp mảng số nguyên
I. Thuật toán được cài đặt ở lần chạy đầu tiên
Thuật toán được cài đặt ở lần chạy đầu tiên dựa trên hàm std::sort trong thư viện STL, thường được triển khai bằng thuật toán Introsort (Introspective Sort). Đây là thuật toán kết hợp giữa Quick Sort, Heap Sort và Insertion Sort nhằm tận dụng ưu điểm của từng thuật toán, đồng thời tránh được các trường hợp có độ phức tạp O(N²).
1. Tổng quan thuật toán
a) Quick Sort
Thuật toán chính được sử dụng trong hầu hết các trường hợp nhờ tốc độ nhanh và hiệu năng trung bình rất tốt.
b) Heap Sort
Mặc dù Quick Sort có tốc độ cao, một số dữ liệu đặc thù có thể khiến độ phức tạp tăng lên O(N²). Heap Sort được tích hợp để đảm bảo độ phức tạp luôn nằm trong giới hạn O(N log N).
c) Insertion Sort
Được áp dụng cho các đoạn có kích thước không vượt quá 24 phần tử. Đối với các đoạn nhỏ, chi phí đệ quy của Quick Sort và Heap Sort thường lớn hơn lợi ích mà chúng mang lại.
2. Các phương pháp tối ưu hóa
a) Đối với Quick Sort
Lựa chọn pivot: Áp dụng phương pháp Median of Three — tìm trung vị của ba mốc left (đầu đoạn), mid (giữa đoạn) và right (cuối đoạn). Phương pháp này giúp giảm khả năng chọn phải pivot xấu, tăng khả năng phân hoạch cân bằng.
Phân hoạch 3-way (Dutch National Flag): Mảng được chia thành ba vùng [ < pivot | = pivot | > pivot ]. Các phần tử bằng pivot không tham gia các lần gọi đệ quy tiếp theo, giúp giảm đáng kể số lượng lời gọi đệ quy khi mảng chứa nhiều phần tử trùng nhau. Khi toàn bộ phần tử giống nhau, thời gian thực hiện chỉ còn O(N).
b) Đối với thuật toán Introsort kết hợp
•	Insertion Sort được sử dụng khi đoạn đang xét có kích thước không quá 24 phần tử.
•	Quick Sort được sử dụng khi độ sâu đệ quy chưa vượt quá 2·log₂(N). Điều này tránh cây đệ quy phát triển quá sâu dẫn đến độ phức tạp tiến gần O(N²).
•	Heap Sort được kích hoạt khi độ sâu đệ quy vượt giới hạn 2·log₂(N), đảm bảo toàn bộ thuật toán luôn trong giới hạn O(N log N).
•	Tail Recursion Elimination: Sau bước phân hoạch 3-way, thuật toán ưu tiên đệ quy trên đoạn nhỏ hơn trước; đoạn còn lại được xử lý bằng vòng lặp, giúp giảm độ sâu ngăn xếp đệ quy và tiết kiệm bộ nhớ.
3. Sinh dữ liệu kiểm thử (test_gen.cpp)
Test case 1 — Dữ liệu ngẫu nhiên toàn miền int
Cách sinh dữ liệu:
Dữ liệu phân bố ngẫu nhiên trên toàn bộ miền int, bao gồm số âm, số dương, giá trị lớn nhỏ xen kẽ.
Thuật toán mục tiêu:
•	Quick Sort
•	Merge Sort
•	Heap Sort
Mục tiêu và lý do chọn:
Mô phỏng dữ liệu thực tế, đánh giá hiệu năng trung bình của thuật toán. Dữ liệu ngẫu nhiên phản ánh tốt hiệu năng average case của phần lớn các thuật toán sắp xếp và được dùng làm mốc so sánh với các bộ test đặc biệt khác.
Test case 2 — Mảng sắp xếp giảm dần
Cách sinh dữ liệu:
Dữ liệu được sinh theo thứ tự giảm dần từ N về 1; mảng ban đầu đã được sắp xếp ngược hoàn toàn.
Thuật toán mục tiêu:
•	Bubble Sort
•	Insertion Sort
•	Quick Sort sử dụng pivot cố định
Mục tiêu và lý do chọn:
Tạo trường hợp worst case cho các thuật toán O(N²). Với Bubble Sort và Insertion Sort, mỗi phần tử phải dịch chuyển gần như tối đa. Với Quick Sort pivot cố định, partition bị lệch hoàn toàn làm độ sâu đệ quy tăng lên O(N) và tổng thời gian chạy đạt O(N²).
Test case 3 — Toàn bộ phần tử trùng nhau
Cách sinh dữ liệu:
Toàn bộ phần tử trong mảng mang cùng một giá trị.
Thuật toán mục tiêu:
•	Quick Sort sử dụng partition 2-way
•	Các thuật toán không tối ưu cho dữ liệu có nhiều phần tử trùng nhau
Mục tiêu và lý do chọn:
Quick Sort thông thường (2-way partition) hoạt động kém khi số lượng phần tử bằng nhau quá lớn: partition mất cân bằng, làm tăng thời gian chạy. Test này cũng giúp phát hiện lỗi xử lý trường hợp bằng nhau trong hàm so sánh (comparator).
Test case 4 — Xen kẽ INT_MIN và INT_MAX
Cách sinh dữ liệu:
Dữ liệu được sinh xen kẽ giữa INT_MIN và INT_MAX; hai giá trị biên xuất hiện liên tục trong mảng.
Thuật toán mục tiêu:
•	Quick Sort
•	Merge Sort
•	Các phiên bản Radix Sort có hỗ trợ số âm
Mục tiêu và lý do chọn:
Kiểm tra khả năng xử lý giá trị biên của kiểu dữ liệu int, phát hiện lỗi tràn số (overflow) và lỗi xử lý số âm trong hàm so sánh. Test tập trung vào tính đúng đắn hơn là thời gian chạy.
Test case 5 — Mảng đã sắp xếp tăng dần
Cách sinh dữ liệu:
Dữ liệu được sinh theo thứ tự tăng dần từ 1 đến N; mảng đã được sắp xếp sẵn trước khi đưa vào thuật toán.
Thuật toán mục tiêu:
•	Quick Sort sử dụng pivot cố định ở đầu hoặc cuối đoạn
•	Các thuật toán không tối ưu cho dữ liệu đã được sắp xếp
Mục tiêu và lý do chọn:
Dữ liệu tăng dần khiến Quick Sort (pivot cố định) có partition lệch hoàn toàn, dẫn đến độ phức tạp O(N²). Ngược lại, Insertion Sort đạt hiệu năng rất tốt trên dữ liệu đã sắp xếp, giúp đánh giá khả năng tối ưu hóa của từng thuật toán.
II. Thuật toán được cài đặt ở lần chạy thứ hai
Thuật toán sử dụng ở lần thứ hai vẫn là Introsort — tương tự lần đầu. Do thuật toán lần 1 đã đạt hiệu năng tốt nhờ sự kết hợp giữa Quick Sort, Heap Sort và Insertion Sort cùng các kỹ thuật tối ưu như Median of Three, phân hoạch 3-way và Tail Recursion Elimination, lần triển khai thứ hai không thay đổi bản chất thuật toán mà tập trung tối ưu ở mức cài đặt.
Tối ưu hóa bổ sung: Từ khóa inline cho hàm Trung_vi()
Hàm Trung_vi() được gọi mỗi lần thực hiện phân hoạch để lựa chọn pivot theo phương pháp Median of Three. Đây là hàm nhỏ, chỉ bao gồm một số phép so sánh và hoán vị đơn giản. Khai báo inline cho phép compiler chèn trực tiếp nội dung hàm vào vị trí gọi, loại bỏ các thao tác overhead của lời gọi hàm thông thường:
•	Lưu địa chỉ trả về.
•	Thiết lập stack frame cho hàm.
•	Nhảy đến địa chỉ hàm và quay trở lại sau khi thực hiện xong.
Mặc dù mức cải thiện trên một lần gọi là không lớn, hàm Trung_vi() được gọi rất nhiều lần trong quá trình sắp xếp nên tổng thời gian thực thi có thể được cải thiện.
Cần lưu ý rằng từ khóa inline chỉ mang tính chất gợi ý cho compiler. Các compiler hiện đại như GCC hoặc Clang ở mức tối ưu hóa -O2 hoặc -O3 thường tự động inline các hàm ngắn mà không cần khai báo tường minh. Hiệu quả thực tế còn phụ thuộc vào compiler và mức tối ưu hóa được sử dụng.
 
B. STRLEXI — Sắp xếp chuỗi theo thứ tự từ điển
I. Thuật toán được cài đặt ở lần chạy đầu tiên
Thuật toán được chọn là Introsort tự cài đặt — kết hợp ba thuật toán: Quick Sort, Heap Sort và Insertion Sort. Cách tiếp cận tự cài đặt cho phép kiểm soát hoàn toàn cách lưu chuỗi trong bộ nhớ và cách thực hiện phép so sánh.
1. Tổng quan thuật toán
a) Quick Sort
Thuật toán chính cho phần lớn trường hợp. Độ phức tạp trung bình O(N log N), cache locality tốt nên nhanh trong thực tế.
b) Heap Sort
Quick Sort có thể đạt O(N²) với một số dữ liệu đặc biệt. Heap Sort được kích hoạt khi số lần đệ quy vượt ngưỡng 2·log₂(N), đảm bảo worst case luôn ở O(N log N).
c) Insertion Sort
Được dùng cho các đoạn nhỏ ≤ 16 phần tử. Với đoạn ngắn, chi phí gọi đệ quy lớn hơn lợi ích mang lại; Insertion Sort chạy trực tiếp trên mảng liên tiếp nên hiệu quả hơn.
2. Các phương pháp tối ưu hóa
a) Introspective Depth Limit
Quick Sort được sử dụng làm thuật toán chính với độ phức tạp trung bình O(N log N). Để tránh suy biến thành O(N²) trong trường hợp xấu, thuật toán theo dõi độ sâu đệ quy và đặt giới hạn bằng 2·log₂(N). Khi vượt ngưỡng này, thuật toán tự động chuyển sang Heap Sort, đảm bảo worst case luôn ở O(N log N).
b) Insertion Sort cho đoạn nhỏ
Khi kích thước đoạn cần sắp xếp không vượt quá 16 phần tử, thuật toán chuyển sang Insertion Sort thay vì tiếp tục phân hoạch bằng Quick Sort. Với dữ liệu kích thước nhỏ, chi phí đệ quy và phân hoạch thường lớn hơn chi phí sắp xếp trực tiếp. Insertion Sort tận dụng tính liên tiếp của bộ nhớ và có hằng số thời gian nhỏ nên cho hiệu năng tốt hơn trong thực tế.
c) Lưu chuỗi liên tục trong bộ nhớ (Memory Pool)
Toàn bộ chuỗi được lưu trong một vùng nhớ lớn duy nhất (pool); mảng chính chỉ lưu con trỏ tới vị trí bắt đầu của từng chuỗi. Khi sắp xếp, thuật toán chỉ hoán đổi các con trỏ thay vì sao chép nội dung chuỗi, giúp giảm đáng kể lượng dữ liệu phải di chuyển, đặc biệt khi chuỗi có độ dài lớn.
d) Heap Sort cài đặt tại chỗ (In-place)
Heap Sort hoạt động trực tiếp trên mảng con trỏ hiện có mà không cần cấp phát thêm bộ nhớ phụ O(N), giúp tiết kiệm bộ nhớ và giữ tính ổn định của hiệu năng.
3. So sánh các phương án — Lý do chọn Introsort tự cài
Đề bài đưa ra các giới hạn đặc thù: N ≤ 100.000, độ dài chuỗi từ 10 đến 100 ký tự trong tập {a–z}. Sau khi cân nhắc các thuật toán thay thế, Introsort tự cài đặt được lựa chọn vì các lý do sau:

Thuật toán	Nhược điểm với bài STRLEXI
Merge Sort	Đạt O(N log N) ổn định nhưng tốn bộ nhớ phụ O(N). Việc liên tục gán chép 10⁵ phần tử giữa mảng gốc và mảng tạm kéo dài thời gian chạy.
Counting Sort	Không áp dụng được. Chỉ dành cho số nguyên dải hẹp. Với chuỗi tối đa 100 ký tự, không gian giá trị là 26¹⁰⁰ — không thể tạo mảng đếm.
Radix Sort	Độ phức tạp O(L·N). Với L_max = 100 và N = 100.000, thuật toán xử lý khoảng 10⁷ ký tự bất kể dữ liệu thực tế.
Quick Sort 2-way	Khi dữ liệu chứa nhiều phần tử trùng nhau, partition 2-way tạo phân hoạch mất cân bằng, dẫn đến độ phức tạp O(N²).
Heap Sort	Chạy an toàn O(N log N) nhưng quá trình vun đống (Heapify) nhảy index liên tục (i → 2i+1, 2i+2) kém cache locality. Chậm hơn Quick Sort 2–3 lần trong thực tế.
Introsort tự cài ✓	Phân hoạch 3-way loại bỏ rủi ro O(N²) với chuỗi trùng. In-place, chỉ swap con trỏ 4-byte. Giới hạn độ sâu đệ quy đảm bảo O(N log N) worst case.

4. Sinh dữ liệu kiểm thử (test_gen.cpp)
Bộ test gồm 5 test case, mỗi test có N = 100.000 chuỗi, độ dài 10–100 ký tự gồm chữ thường a–z. Seed cố định mt19937 rng(999) đảm bảo output trùng khớp với bộ test đã nộp trên Moodle.
Test case 1 — Random hoàn toàn
Cách sinh dữ liệu:
Mỗi chuỗi có độ dài cố định 100 ký tự; toàn bộ ký tự được sinh ngẫu nhiên đều trong tập a–z. Dữ liệu hoàn toàn không có quy luật.
Thuật toán mục tiêu:
•	Quick Sort
•	Merge Sort
•	Heap Sort
Mục tiêu và lý do chọn:
Mô phỏng dữ liệu thực tế, đánh giá hiệu năng trung bình của thuật toán. Dữ liệu ngẫu nhiên phản ánh thời gian trung bình của hầu hết các thuật toán sắp xếp và được dùng làm mốc so sánh cơ bản.
Test case 2 — Prefix 'a' dài 90 ký tự
Cách sinh dữ liệu:
90 ký tự đầu của mỗi chuỗi đều là 'a'; 10 ký tự cuối được sinh ngẫu nhiên.
Thuật toán mục tiêu:
•	Các thuật toán sắp xếp dựa trên phép so sánh (Quick Sort, Merge Sort, Heap Sort, Introsort, std::sort...)
•	Các hàm so sánh chuỗi tuần tự như strcmp hoặc vòng lặp tự cài đặt
Mục tiêu và lý do chọn:
Khi 90 ký tự đầu giống nhau, mỗi lần so sánh hai chuỗi phải duyệt qua 90 bước trước khi tìm ra sự khác biệt. Với N·log(N) lần so sánh và mỗi lần tốn ~90 bước, tổng chi phí tăng lên gần O(N·L·log N). Test nhắm vào hàm so sánh chuỗi tự viết — không được tối ưu như memcmp.
Test case 3 — Toàn bộ chuỗi giống hệt nhau
Cách sinh dữ liệu:
100.000 chuỗi đều là cùng một giá trị cố định: "abcdefghij" + string(90, 'a'). Mọi phép so sánh trả về 0 (bằng nhau).
Thuật toán mục tiêu:
•	Quick Sort dùng 2-way partition
•	Các thuật toán không xử lý tốt nhánh 'bằng nhau'
Mục tiêu và lý do chọn:
Đây là test khó nhất với Quick Sort 2-way partition. Khi tất cả phần tử bằng nhau, partition đặt pivot vào một đầu khiến hai nửa lệch hoàn toàn (1 phần tử vs N-1 phần tử). Cây đệ quy suy biến thành danh sách tuyến tính, độ phức tạp đạt O(N²). Với N = 100.000, đây là ~10 tỷ phép toán, chắc chắn dẫn đến TLE. Thuật toán dùng 3-way partition xử lý được vì toàn bộ N phần tử nằm vào vùng '= pivot' ngay lần đầu, không cần đệ quy thêm.
Test case 4 — Đã sắp xếp giảm dần (Reverse Sorted)
Cách sinh dữ liệu:
Sinh N chuỗi ngẫu nhiên độ dài 100, sau đó sắp xếp giảm dần bằng sort(tmp.rbegin(), tmp.rend()). Kết quả là mảng đã sắp xếp ngược hoàn toàn theo thứ tự từ điển.
Thuật toán mục tiêu:
•	Insertion Sort (worst case O(N²) khi mảng đảo ngược)
•	Quick Sort chọn pivot đầu hoặc cuối cố định
Mục tiêu và lý do chọn:
Với Insertion Sort: mỗi phần tử phải dịch chuyển gần hết mảng về phía trái, tổng số lần dịch đạt N·(N-1)/2 ≈ 5 tỷ lần với N = 100.000. Với Quick Sort pivot cố định: mảng giảm dần khiến partition luôn chia thành (0, N-1), độ sâu đệ quy O(N), tổng phép toán O(N²). Test kiểm tra xem thuật toán có cơ chế phòng tránh worst case hay không.
Test case 5 — Prefix 'z' dài 99 ký tự
Cách sinh dữ liệu:
99 ký tự đầu của mỗi chuỗi đều là 'z'; chỉ ký tự cuối là ngẫu nhiên. Ví dụ: zzz...zzza hoặc zzz...zzzm.
Thuật toán mục tiêu:
•	Các thuật toán sắp xếp dựa trên phép so sánh (Quick Sort, Merge Sort, Heap Sort, Introsort, std::sort...)
•	Các hàm so sánh chuỗi tuần tự như strcmp hoặc vòng lặp tự cài đặt
Mục tiêu và lý do chọn:
99 ký tự đầu giống nhau buộc hàm so sánh phải duyệt gần hết chuỗi mỗi lần. Trong khi Test 2 dùng ký tự 'a' (nhỏ nhất), Test 5 dùng 'z' — khiến toàn bộ chuỗi nằm ở cuối bảng chữ cái và số lần so sánh dài tăng thêm. Hai test kết hợp đảm bảo thuật toán được đánh giá trên nhiều kiểu prefix dài, không chỉ một trường hợp.
II. Thuật toán được cài đặt ở lần chạy thứ hai
Lần triển khai thứ hai giữ nguyên cấu trúc Introsort nhưng khắc phục hai điểm yếu cụ thể trong cài đặt lần 1.
1. Phân hoạch 3-way — Khắc phục O(N²) khi nhiều chuỗi trùng nhau
Lần 1 sử dụng 2-way partition chuẩn: mỗi lần chỉ đặt pivot vào đúng vị trí rồi chia hai nửa. Khi nhiều phần tử bằng pivot (Test 3: toàn chuỗi giống nhau), chúng vẫn bị chia đều vào hai nửa và tiếp tục đệ quy, khiến cây đệ quy mất cân bằng và tổng thời gian tăng lên O(N²).
Lần 2 thay bằng 3-way partition (Dutch National Flag): chia thành [ < pivot | = pivot | > pivot ]. Phần tử bằng pivot được xử lý xong trong một lần, không bao giờ đệ quy vào lại. Test 3 giảm từ timeout (O(N²)) về ~25 ms.
2. Thay hàm so sánh tự viết bằng memcmp()
Hàm cmp() lần 1 dùng vòng while so sánh từng ký tự một. Với chuỗi 100 ký tự mà 90 ký tự đầu giống nhau (Test 2, 5), mỗi lần so sánh phải chạy qua 90 bước trước khi tìm ra sự khác nhau.
Lần 2 chuyển sang memcmp() của thư viện chuẩn. Hàm này được compiler và CPU tối ưu sẵn để so sánh 16–32 byte mỗi lần thay vì 1 byte. Với chuỗi 100 ký tự, chỉ cần 4–7 lần so sánh thay vì 100 lần như code cũ. Để tránh gọi strlen() lặp lại trong mỗi lần so sánh, chương trình lưu thêm mảng lens[] chứa độ dài từng chuỗi.
 
C. LENLEXI — Sắp xếp chuỗi theo độ dài rồi từ điển
I. Thuật toán được cài đặt ở lần chạy đầu tiên
Thuật toán được cài đặt ở lần chạy đầu tiên là sự kết hợp của Bucket Sort, LSD Radix Sort và Counting Sort. Cách kết hợp này tận dụng các đặc điểm cụ thể của bài toán để đạt độ phức tạp gần tuyến tính theo kích thước dữ liệu đầu vào.
1. Tổng quan thuật toán
a) Bucket Sort
Thuật toán được sử dụng để phân nhóm các chuỗi theo độ dài. Vì tiêu chí sắp xếp ưu tiên độ dài tăng dần, việc đưa các chuỗi có cùng độ dài vào cùng một bucket loại bỏ nhu cầu so sánh độ dài trong các bước tiếp theo.
b) LSD Radix Sort
Sau khi phân nhóm theo độ dài, mỗi bucket được sắp xếp bằng LSD Radix Sort từ ký tự cuối đến ký tự đầu. Vì các chuỗi trong cùng bucket có cùng độ dài, Radix Sort có thể áp dụng trực tiếp và cho hiệu quả cao.
c) Counting Sort
Được sử dụng làm thuật toán ổn định trong mỗi bước của LSD Radix Sort. Do dữ liệu chỉ gồm các ký tự từ 'a' đến 'z', số lượng giá trị cần xử lý chỉ là 26, nên Counting Sort hoạt động hiệu quả với độ phức tạp O(N + 26) ≈ O(N).
2. Sự kết hợp các thuật toán
•	Bucket Sort xử lý tiêu chí độ dài chuỗi với chi phí O(N).
•	LSD Radix Sort xử lý tiêu chí thứ tự từ điển trong từng bucket.
•	Counting Sort đóng vai trò thuật toán ổn định cho từng bước của Radix Sort.
Việc kết hợp ba thuật toán trên cho phép tránh phần lớn các phép so sánh chuỗi tốn kém của các thuật toán so sánh thông thường như Merge Sort hoặc Quick Sort, cho thời gian thực thi thấp hơn đáng kể.
3. Lý do lựa chọn
Bài toán có hai đặc điểm quan trọng:
•	Độ dài chuỗi chỉ nằm trong đoạn [10, 100].
•	Ký tự chỉ thuộc tập {a, ..., z}.
Nhờ đó có thể tận dụng Bucket Sort và Radix Sort để tránh các phép so sánh chuỗi tốn kém. Độ phức tạp thực tế gần tuyến tính theo kích thước dữ liệu đầu vào.
4. Các phương pháp tối ưu hóa
a) Đối với Bucket Sort
•	Tận dụng đặc điểm độ dài chuỗi chỉ nằm trong đoạn [10, 100]: phân phối trực tiếp các chuỗi vào 91 bucket tương ứng với từng độ dài thay vì thực hiện phép so sánh.
•	Sau khi phân phối, các bucket được duyệt theo thứ tự từ nhỏ đến lớn, đảm bảo tiêu chí sắp xếp theo độ dài mà không cần thêm phép so sánh nào.
•	Chương trình lưu chỉ số của chuỗi thay vì sao chép dữ liệu vào bucket, giúp giảm chi phí sao chép và lượng bộ nhớ truy cập.
b) Đối với LSD Radix Sort
•	Sắp xếp từ ký tự cuối đến ký tự đầu trong từng bucket; vì chuỗi cùng bucket có cùng độ dài nên không cần xử lý trường hợp thiếu ký tự.
•	Thay vì so sánh trực tiếp giữa các chuỗi, dữ liệu được phân phối dựa trên giá trị ký tự tại từng vị trí, giảm đáng kể số phép toán cần thực hiện.
c) Đối với Counting Sort
•	Mảng đếm có kích thước cố định 26 phần tử, được khai báo cục bộ, tránh cấp phát bộ nhớ động trong mỗi lần gọi.
•	Mảng output được khai báo static để tái sử dụng bộ nhớ giữa các lần gọi hàm, giảm chi phí cấp phát và giải phóng bộ nhớ.
•	Hàm Counting Sort và Radix Sort chỉ thao tác trên mảng chỉ số thay vì di chuyển trực tiếp các đối tượng string, tăng hiệu quả sử dụng cache CPU.
•	Kết quả được ghép vào một chuỗi lớn thông qua biến out trước khi xuất ra màn hình, giảm đáng kể số lần ghi dữ liệu ra luồng xuất.
5. Sinh dữ liệu kiểm thử
Bộ test gồm 5 nhóm dữ liệu khác nhau với kích thước N = 10.000.
Test 1 — Random hoàn toàn
Cách sinh dữ liệu:
Sinh ngẫu nhiên 10.000 chuỗi có độ dài 100 ký tự.
Mục tiêu:
Mô phỏng dữ liệu tổng quát; đánh giá hiệu năng trung bình của thuật toán.
Test 2 — Tất cả chuỗi giống nhau
Cách sinh dữ liệu:
Sinh 10.000 chuỗi có cùng nội dung và cùng độ dài.
Mục tiêu:
Kiểm tra khả năng xử lý dữ liệu có số lượng phần tử trùng lặp rất lớn; đánh giá hiệu quả khi xuất hiện nhiều khóa giống nhau.
Test 3 — Dữ liệu sắp xếp giảm dần
Cách sinh dữ liệu:
Sinh dữ liệu ngẫu nhiên, sau đó sắp xếp theo thứ tự từ điển giảm dần trước khi xuất ra.
Mục tiêu:
Tạo trường hợp bất lợi cho các thuật toán O(N²) và dữ liệu gần worst case cho một số biến thể Quick Sort chọn pivot không phù hợp.
Test 4 — Prefix dài giống nhau
Cách sinh dữ liệu:
Mỗi chuỗi gồm 99 ký tự 'a' và 1 ký tự ngẫu nhiên ở cuối. Ví dụ: aaa...aab, aaa...aac, aaa...aad.
Mục tiêu:
Buộc các thuật toán dựa trên phép so sánh chuỗi phải kiểm tra gần như toàn bộ chuỗi trước khi tìm được ký tự khác biệt, làm tăng đáng kể chi phí của mỗi phép so sánh.
Test 5 — Dữ liệu đã sắp xếp tăng dần
Cách sinh dữ liệu:
Sinh dữ liệu ngẫu nhiên, sau đó sắp xếp tăng dần trước khi xuất ra.
Mục tiêu:
Kiểm tra khả năng xử lý dữ liệu đã có thứ tự; tạo trường hợp bất lợi cho một số biến thể Quick Sort hoặc các thuật toán chọn pivot không tốt.
6. Các thuật toán mục tiêu của bộ test
Quick Sort
Nếu pivot được chọn không hợp lý (luôn chọn phần tử đầu hoặc cuối), các bộ test giảm dần hoặc tăng dần có thể làm cây đệ quy mất cân bằng, khiến độ phức tạp tăng từ O(N log N) lên O(N²).
Insertion Sort
Với các bộ test giảm dần, thuật toán phải thực hiện số lượng phép dịch chuyển phần tử rất lớn, đạt độ phức tạp O(N²) và trở nên rất chậm khi N lớn.
Bubble Sort và Selection Sort
Các thuật toán này luôn có độ phức tạp O(N²); các bộ test kích thước lớn được sử dụng để làm nổi bật sự khác biệt về hiệu năng so với các thuật toán tối ưu hơn.
Các thuật toán sắp xếp dựa trên so sánh chuỗi
Các bộ test có prefix dài giống nhau được thiết kế riêng để làm tăng chi phí của phép so sánh từ điển. Ví dụ, hai chuỗi aaa...aab và aaa...aac phải so sánh gần như toàn bộ 100 ký tự trước khi xác định được thứ tự. Mặc dù số lần so sánh không thay đổi, thời gian thực hiện của mỗi phép so sánh tăng đáng kể.
II. Thuật toán được cài đặt ở lần chạy thứ hai
Thuật toán được cài đặt ở lần chạy thứ hai là sự kết hợp của Merge Sort và Index Sorting. Mục tiêu là tìm kiếm phương án giảm chi phí thao tác trên dữ liệu trong quá trình sắp xếp.
1. Tổng quan thuật toán
a) Merge Sort
Thuật toán sắp xếp chính. Merge Sort hoạt động theo nguyên lý Divide and Conquer: liên tục chia mảng thành các đoạn nhỏ hơn cho đến khi mỗi đoạn chỉ còn một phần tử, sau đó trộn để tạo thành dãy đã sắp xếp. Đảm bảo O(N log N) trong mọi trường hợp.
b) Index Sorting
Thay vì sắp xếp trực tiếp các đối tượng string, chương trình sử dụng mảng chỉ số idx lưu vị trí từng chuỗi trong dữ liệu gốc. Trong toàn bộ quá trình Merge Sort, thuật toán chỉ thao tác trên các giá trị nguyên của mảng idx.
c) Comparator
•	Chuỗi có độ dài nhỏ hơn đứng trước.
•	Nếu hai chuỗi có cùng độ dài thì chuỗi có thứ tự từ điển nhỏ hơn đứng trước.
2. Tối ưu tiếp tục so với lần 1
a) Đối với Merge Sort
•	Sử dụng một mảng temp được cấp phát duy nhất một lần trước khi thực hiện sắp xếp, tái sử dụng qua tất cả các bước Merge, giảm chi phí cấp phát động nhiều lần.
•	Merge Sort đảm bảo O(N log N) trong mọi trường hợp, tránh các worst case có thể xảy ra ở một số thuật toán sắp xếp khác.
b) Đối với Index Sorting
•	Thay vì di chuyển trực tiếp các đối tượng string (độ dài 10–100 ký tự), thuật toán chỉ di chuyển các giá trị nguyên trong mảng idx. Dữ liệu chuỗi giữ nguyên vị trí trong bộ nhớ, giảm đáng kể chi phí sao chép trong quá trình Merge.
•	Thao tác trên dữ liệu kiểu int giúp tăng hiệu quả sử dụng cache CPU do kích thước dữ liệu nhỏ và liên tục trong bộ nhớ.
•	Dữ liệu được lưu trữ trong vector để tận dụng khả năng truy cập ngẫu nhiên O(1).
c) Đối với hàm so sánh
•	Ưu tiên so sánh độ dài chuỗi trước; chỉ khi hai chuỗi có cùng độ dài mới thực hiện so sánh từ điển.
•	Cách làm này giúp giảm số lần phải duyệt ký tự của chuỗi, đặc biệt hiệu quả khi dữ liệu chứa nhiều chuỗi có độ dài khác nhau.
3. Đánh giá tổng thể
Mặc dù độ phức tạp lý thuyết vẫn là O(N log N), các phương pháp tối ưu hóa trên giúp giảm hệ số hằng số của thuật toán và nâng cao hiệu quả thực thi trong thực tế, đặc biệt trên các bộ dữ liệu lớn.
