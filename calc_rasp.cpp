#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include "Ratio2.h"

#pragma warning(disable : 4996)

using namespace std;

class Operand
{
    Ratio a;

public:
    Operand() = default;
    Operand(Ratio x) :a(x) {};
    Operand operator + (Operand x) { return Operand(a + x.a); }
    Operand operator - (Operand x) { return Operand(a - x.a); }
    Operand operator * (Operand x) { return Operand(a * x.a); }
    Operand operator / (Operand x) { return Operand((x.a != Ratio(0)) ? a / x.a : Ratio(0)); }
    Operand operator % (Operand x) { return Operand(a % x.a); }
    Operand operator ^ (Operand x)
    {
        if (x.a == Ratio(0)) return Ratio(1);

        Ratio v = a;

        for (Ratio i = x.a - Ratio(1); i > Ratio(0); i--) a = a * v;

        return *this;

    }
    Operand operator = (Operand x)
    {
        a = x.a;
        return *this;
    }


    void operator << (Operand x) { cout << x.a; }

    void set(Ratio x) { a = x; }

    Ratio get() { return a; }
};

int contains(string source, string find)
{
    int pos, length = find.size();
    char* temp = new char[length + 1];

    strcpy(temp, find.c_str());

    for (int i = 0; i < length; i++)
        if ((pos = source.find(temp[i])) != string::npos)
            return pos;
    return -1;
}

int main()
{
    string s;
    Ratio x, y;
    char* opr = new char[1];
    int pos;

    Operand a, b, c;

    while (getline(cin, s))
    {
        pos = contains(s, "+-*/%^");

        if (pos != -1)
        {
            if (pos != 0)
                x = Ratio(stoi(s.substr(0, pos)));
            else
                x = c.get();

            string temp = s.substr(pos, 1);
            strcpy(opr, temp.c_str());

            y = Ratio(stoi(s.substr(pos + 1)));

            a.set(x);
            b.set(y);

            switch (*opr)
            {
            case '+': cout << "="; c << (c = a + b); cout << endl; break;
            case '-': cout << "="; c << (c = a - b); cout << endl; break;
            case '*': cout << "="; c << (c = a * b); cout << endl; break;
            case ':': cout << "="; c << (c = a / b); cout << endl; break;
            case '%': cout << "="; c << (c = a % b); cout << endl; break;
            case '^': cout << "="; c << (c = (a ^ b)); cout << endl; break;
            }
        }
        else
        {
            x = Ratio(0); y = Ratio(0); c.set(Ratio(0));

            system("cls");   //for windows
            system("clear"); //for linux

        }
    };

    return 0;
}

