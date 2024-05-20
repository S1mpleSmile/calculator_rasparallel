#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Bigint.h"

using namespace std;

BigInt gcf(BigInt a, BigInt b) {
    a = a.abs();
    b = b.abs();
    if (a < b) swap(a, b);
    while (b > BigInt(0)) {
        a %= b;
        swap(a, b);
    }
    return a;
}

BigInt lcm(BigInt a, BigInt b) {
    return a * b / gcf(a, b);
}

void simplify(BigInt& a, BigInt& b) {
    if (b != BigInt(0)) {
        BigInt g;
        g = gcf(a, b);
        a /= g;
        b /= g;
        if (b < BigInt(0)) {
            a = BigInt(0) - a;
            b = BigInt(0) - b;
        }
    }
    else if (a != BigInt(0)) {
        a = BigInt(1);
        b = BigInt(0);
    }
    else {
        a = BigInt(1);
        b = BigInt(1);
    }
}


struct Ratio {
    BigInt num;
    BigInt denom;

    Ratio(BigInt m, BigInt n) {
        simplify(m, n);
        this->num = m;
        this->denom = n;
    }

    Ratio(BigInt _num) : num{ _num }, denom{ 1 } {};

    Ratio() {
        this->num = BigInt(0);
        this->denom = BigInt(1);
    }

    //operator double() const { return (1.0*num)/denom; }

    Ratio operator+(Ratio val) {
        BigInt m;
        m = lcm(this->denom, val.denom);
        return Ratio(this->num * (m / this->denom) + val.num * (m / val.denom), m);
    }

    Ratio operator-(Ratio val) {
        BigInt m;
        m = lcm(this->denom, val.denom);
        return Ratio(this->num * (m / this->denom) - val.num * (m / val.denom), m);
    }

    Ratio operator*(Ratio val) {
        return Ratio(this->num * val.num, this->denom * val.denom);
    }

    Ratio operator/(Ratio val) {
        return Ratio(this->num * val.denom, this->denom * val.num);
    }

    Ratio operator%(Ratio val) {
        BigInt m;
        m = lcm(this->denom, val.denom);
        return Ratio(this->num * (m / this->denom) % val.num * (m / val.denom), m);
    }

    Ratio operator-() {
        this->num = BigInt(0) - this->num;
        return *this;
    }

    void operator+=(Ratio val) {
        *this = *this + val;
    }

    void operator-=(Ratio val) {
        *this = *this - val;
    }

    void operator*=(Ratio val) {
        *this = *this * val;
    }

    void operator/=(Ratio val) {
        *this = *this / val;
    }

    void operator%=(Ratio val) {
        *this = *this % val;
    }

    Ratio operator++() {
        this->num += this->denom;
        return *this;
    }

    Ratio operator--() {
        this->num -= this->denom;
        return *this;
    }

    Ratio operator++(int i) {
        Ratio r;
        r = *this;
        this->num += this->denom;
        return r;
    }

    Ratio operator--(int i) {
        Ratio r;
        r = *this;
        this->num -= this->denom;
        return r;
    }

    bool operator<(Ratio val) {
        BigInt m;
        m = lcm(this->denom, val.denom);
        return (this->num * (m / this->denom) < val.num * (m / val.denom));
    }

    bool operator>(Ratio val) {
        BigInt m;
        m = lcm(this->denom, val.denom);
        return (this->num * (m / this->denom) > val.num * (m / val.denom));
    }

    bool operator==(Ratio val) {
        return (this->num == val.num && this->denom == val.denom);
    }

    bool operator!=(Ratio val) {
        return (this->num != val.num || this->denom != val.denom);
    }

    bool operator<=(Ratio val) {
        return !(*this > val);
    }

    bool operator>=(Ratio val) {
        return !(*this < val);
    }
};


istream& operator>>(istream& is, Ratio& r) {
    BigInt m, n;
    char c;
    is >> m;
    c = is.get();
    if (c == '\n') {
        r = Ratio(m);
    }
    else
        if (c != '/')
        {
            r = Ratio(m);
            is.putback(c);
        }
        else
        {
            is >> n;
            r = Ratio(m, n);
        }
    return is;
}

ostream& operator<<(ostream& os, const Ratio& r) {
    return r.denom == BigInt(1) ? os << r.num : os << r.num << "/" << r.denom;
}

BigInt floor(Ratio a) {
    return a.num >= BigInt(0) ? a.num / a.denom : (a.num + BigInt(1)) / a.denom - BigInt(1);
}

BigInt ceil(Ratio a) {
    return a.num >= BigInt(0) ? (a.num - BigInt(1)) / a.denom + BigInt(1) : a.num / a.denom;
}

BigInt absfloor(Ratio a) {
    return a.num / a.denom;
}

BigInt absceil(Ratio a) {
    return a.num >= BigInt(0) ? (a.num - BigInt(1)) / a.denom + BigInt(1) : (a.num + BigInt(1)) / a.denom - BigInt(1);
}

Ratio fractpart(Ratio a) {
    return a - floor(a);
}

Ratio absfractpart(Ratio a) {
    return a - absfloor(a);
}

/*double approx(Ratio a) {
    return a.num / (double)a.denom;
}*/

BigInt round(Ratio a) {
    return fractpart(a) >= Ratio(BigInt(1), BigInt(2)) ? ceil(a) : floor(a);
}

BigInt nop(BigInt n) { // (-1)^n, negonepower
    return (int)(n % BigInt(2) == BigInt(0)) * 2 - 1;
}

BigInt factorial(BigInt n) {
    BigInt f = 1;
    for (BigInt i = 2; i <= n; ++i) {
        f *= i;
    }
    return f;
}

BigInt factorial(Ratio n) {
    if (n.denom == 1)
        return factorial(n.num);
    return BigInt(-1);
}

BigInt subfactorial(BigInt n) {
    BigInt f, s = 0;
    f = factorial(n);
    for (BigInt i = 0; i <= n; ++i) {
        s += f * nop(i) / factorial(i);
    }
    return s;
}

BigInt C(BigInt k, BigInt n) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

Ratio C(BigInt k, Ratio n) {
    if (k < BigInt(0)) return Ratio();
    else
    {
        Ratio f = BigInt(1);
        for (BigInt i = 0; i < k; ++i) {
            f *= (n - i);
            f /= (k - i);
        }
        return f;
    }
}

BigInt mod(BigInt a, BigInt b) {
    return a % b >= BigInt(0) ? a % b : a % b + b;
}

vector<Ratio> egyptify(Ratio a) {
    vector<Ratio> v;
    while (a.denom % a.num != BigInt(0)) {
        v.push_back(Ratio(BigInt(1), ceil(Ratio(a.denom, a.num))));
        a = Ratio(mod(BigInt(0) - a.denom, a.num), a.denom * ceil(Ratio(a.denom, a.num)));
    }
    v.push_back(Ratio(BigInt(1), ceil(Ratio(a.denom, a.num))));
    return v;
}

/*long long* fibonacci(BigInt n) {
    long long* f = new long long[atoi(n.getValue()) + 1];
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= atoi(n.getValue()); ++i) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f;
}*/

/*Ratio* bernoulli(BigInt n) {
    Ratio* b = new Ratio[atoi(n.getValue()) + 1];
    Ratio s;
    b[0] = BigInt(1);
    for (long long i = 1; BigInt(i) <= n; ++i) {
        b[i] = BigInt(0);
        for (long long k = 1; k <= i; ++k) {
            b[i] += (Ratio(BigInt(0) - BigInt(1) * C(BigInt(k + 1), BigInt(i + 1))) * b[i - k]) / BigInt(i + 1);
        }
    }
    return b;
}*/
