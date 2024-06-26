#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <chrono>
#include "Ratio2.h"

#pragma warning(disable : 4996)

using namespace std;

Ratio stor(string const& str)
{
    Ratio a;
    std::istringstream is(str, ios_base::in);
    is >> a;
    return a;
}

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

Operand factorial(Operand a)
{
    return Operand(factorial(a.get()));
}

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
        auto start = chrono::high_resolution_clock::now();
        pos = contains(s, "+-*:%^!");

        if (pos != -1)
        {
            if (pos != 0)
                x = stor(s.substr(0, pos));
            else
                x = c.get();

            string temp = s.substr(pos, 1);
            strcpy(opr, temp.c_str());

            y = stor(s.substr(pos + 1));

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
            case '!': cout << "="; c << (c = factorial(a)); cout << endl; break;
            }
        }
        else
        {
            x = Ratio(0); y = Ratio(0); c.set(Ratio(0));

            system("cls");   //for windows
            //system("clear"); //for linux

        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        string out = "timelog_fact_nopar.txt";
        fstream f;
        f.open(out, ios::app);
        f << a.get() << ", " << duration << endl;
        f.close();
    };

    return 0;
}
