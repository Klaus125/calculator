#include "../Headers/BigNumber.h"
#include <iostream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int main() {
    char a[1000];
    char b[1000];
    char op;

    BigNumber dividend = 1;  // 被除数
    cout << "请输入首个运算数"<<endl;
    cin >> a;
    BigNumber divisor(a);    // 除数

    //输入重定向到in.dat文件
    while (1) {
        cout <<"输入运算符和操作数，中间以空格分割"<<endl;
        cin >>op >> b;
        BigNumber temp(b);
        //去掉前导零
//        divisor.cleanLeadZero();
//        temp.cleanLeadZero();
        switch (op) {
            case '+':
                divisor = divisor +  temp * dividend;
                cout << BigNumber::getNumericNotation(divisor, dividend) << endl;
                break;
//            case '-':
//                if (divisor < temp) cout << "-" << (temp - divisor).str() << endl;
//                else cout << (divisor - temp).str() << endl;
//                break;
            case '*':
                divisor = divisor * temp;
                cout << BigNumber::getNumericNotation(divisor, dividend) << endl;
                break;
            case '/':
                dividend = dividend * temp;
                cout << BigNumber::getNumericNotation(divisor, dividend) << endl;
                break;
//            case '%':
//                cout << (divisor % temp).str() << endl;
//                break;
        }
    }
    return 0;
}

#pragma clang diagnostic pop