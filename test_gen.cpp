#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <cassert>
#include <climits>

using namespace std;

const string MSSV = "25120410";

mt19937 rng(999);

int randInt(int l, int r) {
    uniform_int_distribution<int> dist(l, r);
    return dist(rng);
}

char randChar() {
    return 'a' + randInt(0, 25);
}

string randString(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; i++)
        s += randChar();
    return s;
}

void printData(const vector<string>& data) {
    // data[0] là n, data[1..n] là các phần tử
    cout << data.size() - 1 << '\n';
    for (int i = 1; i < (int)data.size(); i++)
        cout << data[i] << '\n';
}

// bài 1 int
void Int(int tc) {
    int n = 100000;
    vector<string> data;
    data.push_back(to_string(n));

    if (tc == 1) {
        // Random hoàn toàn — test tổng quát nhất
        for (int i = 0; i < n; i++)
            data.push_back(to_string(randInt(INT_MIN, INT_MAX)));
    }
    else if (tc == 2) {
        // Giảm dần — worst case cho insertion sort / bubble sort
        for (int i = n; i >= 1; i--)
            data.push_back(to_string(i));
    }
    else if (tc == 3) {
        // Tất cả bằng nhau — test nhánh so sánh bằng
        for (int i = 0; i < n; i++)
            data.push_back("123456789");
    }
    else if (tc == 4) {
        // Xen kẽ INT_MIN và INT_MAX — test biên giá trị 32-bit
        for (int i = 0; i < n; i++) {
            if (i & 1)
                data.push_back(to_string(INT_MIN));
            else
                data.push_back(to_string(INT_MAX));
        }
    }
    else if (tc == 5) {
        // Tăng dần — đã sắp xếp sẵn, test thuật toán đã sorted
        for (int i = 1; i <= n; i++)
            data.push_back(to_string(i));
    }

    printData(data);
}

// bài 2 strlexi
void Strlexi(int tc) {
    int n = 100000;
    vector<string> data;
    data.push_back(to_string(n));

    if (tc == 1) {
        // Random hoàn toàn, độ dài 100
        for (int i = 0; i < n; i++)
            data.push_back(randString(100));
    }
    else if (tc == 2) {
        // 90 ký tự 'a' đầu + 10 ký tự random — prefix dài giống nhau
        for (int i = 0; i < n; i++)
            data.push_back(string(90, 'a') + randString(10));
    }
    else if (tc == 3) {
        // Tất cả chuỗi giống nhau — test nhánh bằng nhau
        string same = "abcdefghij" + string(90, 'a');
        for (int i = 0; i < n; i++)
            data.push_back(same);
    }
    else if (tc == 4) {
        // Sắp xếp giảm dần trước — worst case cho các thuật toán O(n^2)
        vector<string> tmp;
        for (int i = 0; i < n; i++)
            tmp.push_back(randString(100));
        sort(tmp.rbegin(), tmp.rend());
        for (auto& s : tmp)
            data.push_back(s);
    }
    else if (tc == 5) {
        // 99 ký tự 'z' + 1 ký tự random — prefix cực dài giống nhau
        for (int i = 0; i < n; i++)
            data.push_back(string(99, 'z') + randChar());
    }

    printData(data);
}

// bài 3 strlenlexi
void Strlenlexi(int tc) {
    int n = 10000;
    vector<string> data;
    data.push_back(to_string(n));

    vector<string> tmp;

    if (tc == 1) {
        // Random hoàn toàn
        for (int i = 0; i < n; i++)
            tmp.push_back(randString(100));
    }
    else if (tc == 2) {
        // Tất cả cùng 1 chuỗi — cùng độ dài, cùng nội dung
        string s = randString(100);
        for (int i = 0; i < n; i++)
            tmp.push_back(s);
    }
    else if (tc == 3) {
        // Random rồi sort giảm dần — worst case cho O(n^2)
        for (int i = 0; i < n; i++)
            tmp.push_back(randString(100));
        sort(tmp.rbegin(), tmp.rend());
    }
    else if (tc == 4) {
        // 99 ký tự 'a' + 1 random — cùng độ dài, prefix dài giống nhau
        for (int i = 0; i < n; i++)
            tmp.push_back(string(99, 'a') + randChar());
    }
    else if (tc == 5) {
        // Random rồi sort tăng dần — đã sắp xếp sẵn
        for (int i = 0; i < n; i++)
            tmp.push_back(randString(100));
        sort(tmp.begin(), tmp.end());
    }

    for (auto& s : tmp)
        data.push_back(s);

    printData(data);
}

int main(int argc, char* argv[]) {

    // Lấy tên của problem
    string problem = argv[1];

    // Chuyển test case từ chuỗi sang số nguyên
    int tc = stoi(argv[2]);

    // Kiểm tra test case hợp lệ
    if (tc < 1 || tc > 5) {
        cerr << "Loi: test case phai nam trong khoang tu 1 den 5\n";
        return 1;
    }

    // Sinh test cho bài 1
    if (problem == "int") {
        Int(tc);
    }
    // Sinh test cho bài 2
    else if (problem == "strlexi") {
        Strlexi(tc);
    }

    // Sinh test cho bài 3
    else if (problem == "strlenlexi") {
        Strlenlexi(tc);
    }

    else {
        cerr << "Loi: bai toan phai la int, strlexi hoac strlenlexi\n";
        return 1;
    }

    return 0;
}