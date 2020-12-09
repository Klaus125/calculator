#include "../Headers/BigNumber.h"
#include <iostream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int main() {
    char a[1000];
    char b[1000];
    char op;
    //输入重定向到in.dat文件
    while (1) {
        cin >> a >> op >> b;
        BigNumber lvalue(a);
        BigNumber rvalue(b);
        //去掉前导零
        lvalue.cleanLeadZero();
        rvalue.cleanLeadZero();
        cout << lvalue << " " << op << " " << rvalue << " = ";
        switch (op) {
            case '+':
                cout << (lvalue + rvalue).str() << endl;
                break;
            case '-':
                if (lvalue < rvalue) cout << "-" << (rvalue - lvalue).str() << endl;
                else cout << (lvalue - rvalue).str() << endl;
                break;
            case '*':
                cout << (lvalue * rvalue).str() << endl;
                break;
            case '/':
                cout << BigNumber::getNumericNotation(lvalue,rvalue)<<endl;
//                cout << (lvalue / rvalue).str() << endl;
                break;
            case '%':
                cout << (lvalue % rvalue).str() << endl;
                break;
        }
    }
    return 0;
}

#pragma clang diagnostic pop