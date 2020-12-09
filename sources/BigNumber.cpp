#include "../Headers/BigNumber.h"
#include <iostream>
#include <bits/stdc++.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wstring-plus-int"
using namespace std;

void BigNumber::cleanLeadZero() {
    // test commit
    while (len > 1 && !s[len - 1]) len--;
}

void BigNumber::divisionTen(int n)
{
    int i;
    if (n > len) {
        while (len >= 1) s[len--] = 0;
    }
    else {
        for (i = 0; i < len - n; i++)
        {
            s[i] = s[i + n];
        }
        len -= n;
    }
}

void BigNumber::multiplyTen(int n)
{
    if (n > 0) {
        int i;
        for (i = len - 1; i >= 0; i--)
        {
            s[i + n] = s[i];
        }
        for (i = 0; i < n; i++) {
            s[i] = 0;
        }
        len += n;
    }
}

string BigNumber::str() const
{
    string res = "";
    // 每个位的数逆序添加到str末尾。
    for (int i = 0; i < len; i++) {
        res = (char)(s[i] + '0') + res;
    }
    if (res == "") res = "0";
    return res;
}

BigNumber::BigNumber()
{
    memset(s, 0, sizeof(s));
    len = 1;
}

BigNumber::BigNumber(int num) {
    *this = num;
}

BigNumber::BigNumber(const char* num) {
    *this = num;
}

BigNumber BigNumber::getSub(int n) const
{
    BigNumber c;
    c.len = 0;
    for (int i = 0; i < n; i++) {
        c.s[c.len++] = s[len - n + i];
    }
    return c;
}

BigNumber BigNumber::operator = (const char* num)
{
    len = strlen(num);
    // 整数在s数组中是逆序存放的（如："456" 在s数组中是s[0] = 6, s[1] = 5, s[2] = 4）
    for (int i = 0; i < len; i++) {
        s[i] = num[len - i - 1] - '0';
    }
    return *this;
}

BigNumber BigNumber::operator = (int num) {
    char s[MAXN];
    sprintf(s, "%d", num);
    *this = s;
    return *this;
}

BigNumber BigNumber::operator + (const BigNumber& x) const
{
    BigNumber r;
    r.len = 0;
    // up 是用来保持进位的
    int i, up;
    int maxLen = max(len, x.len);
    for (i = 0, up = 0; up || i < maxLen; i++) {
        int temp = up;
        if (i < len) temp += s[i];
        if (i < x.len) temp += x.s[i];
        up = temp / 10;
        r.s[r.len++] = temp % 10;
    }
    // 去除前导零
    r.cleanLeadZero();
    return r;
}

// 减法在使用时要注意在计算a - b时要确保a >= b;
// 如果a < b 则计算 先输出一个'-' 再输出b - a 的结果
BigNumber BigNumber::operator - (const BigNumber& b) const
{
    BigNumber c;
    c.len = 0;
    int i;
    // 用来保存退位
    int down;
    for (i = 0, down = 0; i < len; i++)
    {
        int temp = s[i] - down;
        if (i < b.len) temp -= b.s[i];
        if (temp >= 0) down = 0;
        else {
            down = 1;
            temp += 10;
        }
        c.s[c.len++] = temp;
    }
    c.cleanLeadZero();
    return c;
}

BigNumber BigNumber::operator * (const BigNumber& b) const
{
    int i, j;
    BigNumber c;
    c.len = len + b.len;
    for (i = 0; i < len; i++) {
        for (j = 0; j < b.len; j++) {
            c.s[i + j] += s[i] * b.s[j];
        }
    }

    for (i = 0; i < c.len - 1; i++) {
        c.s[i + 1] += c.s[i] / 10;
        c.s[i] %= 10;
    }
    c.cleanLeadZero();
    return c;
}

BigNumber BigNumber::operator / (const BigNumber& b) const
{
    int i, j;
    BigNumber r;
    r.len = 0;
    // 模拟除法的过程
    // 先取blen - 1位
    BigNumber temp = this->getSub(b.len - 1);
    // 一位一位的除从而取得完整的答案
    for (i = len - b.len; i >= 0; i--)
    {
        // temp用来存储被除数的前blen位。
        temp = temp * 10 + s[i];
        // 如果temp < b则再在该位的结果为0
        if (temp < b) {
            r.s[r.len++] = 0;
        }
        else {
            // 否则找到第一个j使得b * j的结果大于 temp
            for (j = 1; j <= 10; j++) {
                if (b * j > temp) break;
            }
            // 因为此时（j - 1） * b小于等于temp，所有j - 1就是在该位除的结果
            r.s[r.len++] = j - 1;
            // temp 减去被减去部分为下一次迭代做准备
            temp = temp - (b * (j - 1));
        }
    }
    // 逆序（因为结果是要逆序存储的，而在求解过程中结果是顺序存储的）
    for (i = 0; i < r.len / 2; i++) {
        int temp = r.s[i];
        r.s[i] = r.s[r.len - 1 - i];
        r.s[r.len - 1 - i] = temp;
    }
    r.cleanLeadZero();
    return r;
}



BigNumber BigNumber::operator % (const BigNumber& b) const
{
    BigNumber r;
    r = *this / b;
    r = *this - r * b;
    return r;
}



istream& operator >> (istream& in, BigNumber& x)
{
    string s;
    in >> s;
    x = s.c_str();
    return in;
}

ostream& operator << (ostream& out, BigNumber& x)
{
    out << x.str();
    return out;
}

bool BigNumber::operator < (const BigNumber& b) const
{
    if (len != b.len) return len < b.len;
    else {
        for (int i = len - 1; i >= 0; i--) {
            if (s[i] != b.s[i]) return s[i] < b.s[i];
        }
    }
    return false;
}

bool BigNumber::operator > (const BigNumber& b) const
{
    return b < *this;
}

bool BigNumber::operator <= (const BigNumber& b) const
{
    return !(b > * this);
}

bool BigNumber::operator >= (const BigNumber& b) const
{
    return !(*this < b);
}

bool BigNumber::operator == (const BigNumber& b) const
{
    return !(b < *this) && !(b > * this);
}

void BigNumber::handle(int res[],BigNumber remainder,BigNumber num2,int cnt){
    BigNumber addition;
    while(--cnt>= 0){
        addition = remainder * 10 / num2;
        remainder = remainder * 10 % num2;
        string str = addition.str();
        res[ digitNum - cnt] = str[0] - '0';
    }
}

string BigNumber::getNumericNotation(BigNumber num1,BigNumber num2) {
    BigNumber addition  = num1 / num2;
    BigNumber remainder = num1 % num2;

    // 1. 如果商不为0，对商进行处理，计算余数需要操作的位数，过程中记录余数
    // 2. 如果商为0，完全操作余数，while循环，找到第一个不为0的小数位，过程中记录指数

    int res[digitNum + 1];
    int cnt = digitNum + 1;      // 记录找寻非0数的个数
    int exponent = 0; // 记录现阶段的指数

    string addition_str = addition.str();
    int addition_len = addition_str.length();
    if (addition_str != "0"){ // 商不为0
        // 指数部分已经确定
        exponent = addition_len - 1;
        for(int i = 0;i < addition_len;i ++){
            res[i] = addition_str[i] - '0';
            cnt --;
            if(i == digitNum + 1){
                break;
            }
        }
        // 仍需要探索cnt位，每一次探索都有效
        handle(res,remainder,num2,cnt);
    }else{
        while(true){
            addition = remainder * 10 / num2;
            remainder = remainder * 10 % num2;
            exponent --;
            // 对cnt和res[0]初始化
            if(addition.str()[0] != '0'){
                res[0] = addition.str()[0] - '0';
                cnt = digitNum;
                handle(res,remainder,num2,cnt);
                break;
            }
        }
    }



    for(int i = digitNum;i >= 1;i --){
        // 1. 末尾数字,四舍五入
        // 2. 非末位数字，逢十进一
        if(i == digitNum && res[i] >= 5 || i != digitNum && res[i] >= 10){
            res[i] %= 10;
            res[i - 1] ++ ;
        }
    }
    if(res[0] == 10){
        exponent ++;
        res[0] = 1;
    }

    // 将res数组用科学计数法表示,注意四舍五入
    string res_str;
    for(int i = 0; i < digitNum;i ++){
        if(i == 1)
            res_str += '.';
        res_str += (char)(res[i] + '0');
    }

    res_str +=  " * 10 ^ " +  to_string(exponent);
    return res_str;
}



#pragma clang diagnostic pop