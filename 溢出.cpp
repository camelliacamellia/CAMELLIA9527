#include <iostream>
using namespace std;

int main() {
    char buf[5] = {0};  // 实际只能存 4 字符 + \0
    int secret = 123;    // 存储在 buf 附近的内存

    cout << "Before overflow: secret = " << secret << endl;
    cin >> buf;  // 输入 "ABCDEFGH"（8字符，远超buf容量）
    cout << "After overflow: secret = " << secret << endl;

    return 0;
}
