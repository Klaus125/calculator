#include "../Headers/BigNumber.h"
#include <iostream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int main() {
    char a[1000];
    char b[1000];
    char op;

    BigNumber dividend = 1;  // ������
    cout << "�������׸�������"<<endl;
    cin >> a;
    BigNumber divisor(a);    // ����

    //�����ض���in.dat�ļ�
    while (1) {
        cout <<"����������Ͳ��������м��Կո�ָ�"<<endl;
        cin >>op >> b;
        BigNumber temp(b);
        //ȥ��ǰ����
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