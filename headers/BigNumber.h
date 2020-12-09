#ifndef WORK3_BIGNUMBER_H
#define WORK3_BIGNUMBER_H

#include <iosfwd>
#include <iostream>

using namespace std;

int const MAXN = 800;
int const digitNum = 5;
class BigNumber
{
public:

    int s[MAXN];
    int len;
public:
    // 去除前导零
    void cleanLeadZero();
    // 乘以10的n次方
    void multiplyTen(int n);
    // 除以10的n次方
    void divisionTen(int n);
    // 将结果转换成字符串
    std::string str() const;
    // 构造函数
    BigNumber();
    BigNumber(int);
    BigNumber(const char*);
    // 截取整数的前n位数（例如1234434 调用getSub(3)的话得到的结果是123）
    BigNumber getSub(int n) const;
    // 重载赋值运算符
    BigNumber operator = (const char*);
    BigNumber operator = (int num);
    // 重载加减乘除
    BigNumber operator + (const BigNumber&) const;
    BigNumber operator - (const BigNumber&) const;
    BigNumber operator * (const BigNumber&) const;
    BigNumber operator / (const BigNumber&) const;
    BigNumber operator % (const BigNumber&) const;

    // 重载比较运算符
    bool operator < (const BigNumber&) const;
    bool operator > (const BigNumber&) const;
    bool operator <= (const BigNumber&) const;
    bool operator >= (const BigNumber&) const;
    bool operator == (const BigNumber&) const;

    // 重载输入输出流
    friend std::istream& operator >> (std::istream&, BigNumber&);
    friend std::ostream& operator << (std::ostream&, BigNumber&);

    static string getNumericNotation(BigNumber num1,BigNumber num2);

    static void handle(int res[],BigNumber remainder,BigNumber num2,int cnt);
};
#endif //WORK3_BIGNUMBER_H
