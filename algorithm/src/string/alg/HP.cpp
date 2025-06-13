// #include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

void revStr(string &s)
{
    if (s.empty())
        return;
    int start = 0;
    int end = s.size() - 1;
    for (int i = 0; i <= (end - start) / 2; i++)
    {
        int t = s[i + start];
        s[i + start] = s[end - i];
        s[end - i] = t;
    }
}

// is s1 < s2.
bool cmpStr(const string &s1, const string &s2)
{
    if (s1.size() != s2.size())
        return s1.size() < s2.size();
    for (int i = 0; i < s1.size(); i++)
    {
        if (s1[i] != s2[i])
            return s1[i] < s2[i];
    }
    return false;
}

// assume s1 and s2 is reversed.
string hpPlus(const string &s1, const string &s2)
{
    int s1len = s1.size(), s2len = s2.size();
    string ans;
    int cin = 0;
    int ind1 = 0, ind2 = 0;
    while (ind1 < s1len && ind2 < s2len)
    {
        int tot = s1[ind1] - '0' + s2[ind2] - '0' + cin;
        ans.push_back(tot % 10 + '0');
        cin = tot / 10;

        ind1++;
        ind2++;
    }
    while (ind1 < s1len)
    {
        int tot = s1[ind1] - '0' + cin;
        ans.push_back(tot % 10 + '0');
        cin = tot / 10;

        ind1++;
    }
    while (ind2 < s2len)
    {
        int tot = s2[ind2] - '0' + cin;
        ans.push_back(tot % 10 + '0');
        cin = tot / 10;

        ind2++;
    }
    while (cin)
    {
        ans.push_back(cin % 10 + '0');
        cin /= 10;
    }
    return ans;
}

string hpMinus(const string &s1, const string &s2)
{
    string ans;

    string ts1 = s1, ts2 = s2;
    revStr(ts1), revStr(ts2);
    if (!cmpStr(ts1, ts2))
    {
        int s1len = s1.size(), s2len = s2.size();
        int ind1 = 0, ind2 = 0;
        int cin = 0;
        while (ind1 < s1len && ind2 < s2len)
        {
            int tot = s1[ind1] - '0' - (s2[ind2] - '0') - cin;
            cin = 0;
            while (tot < 0)
            {
                tot += 10;
                cin++;
            }
            ans.push_back(tot + '0');

            ind1++;
            ind2++;
        }
        while (ind1 < s1len)
        {
            int tot = s1[ind1] - '0' - cin;
            cin = 0;
            while (tot < 0)
            {
                tot += 10;
                cin++;
            }
            ans.push_back(tot + '0');

            ind1++;
        }
        while (ans.size() > 1 && ans.back() == '0')
        {
            ans.pop_back();
        }
    }
    else
    {
        ans = "-";
        ans += hpMinus(s2, s1);
    }
    return ans;
}

string hpMult(const string &s1, const string &s2)
{
    string ans = "0";
    int s1len = s1.size(), s2len = s2.size();
    for (int i = 0; i < s1len; i++)
    {
        string temp;
        for (int j = 0; j < i; j++)
        {
            temp.push_back('0');
        }
        int cin = 0;
        for (int j = 0; j < s2len; j++)
        {
            int tot = (s1[i] - '0') * (s2[j] - '0') + cin;
            temp.push_back(tot % 10 + '0');
            cin = tot / 10;
        }
        while (cin)
        {
            temp.push_back(cin % 10 + '0');
            cin /= 10;
        }
        ans = hpPlus(ans, temp);
    }
    while (ans.size() > 1 && ans.back() == '0')
    {
        ans.pop_back();
    }
    return ans;
}

string fastPow(const string &base, int index)
{
    string ans = "1";
    string t = base;
    while (index)
    {
        if (index & 1)
            ans = hpMult(ans, t);
        t = hpMult(t, t);
        index >>= 1;
    }
    return ans;
}

// high presion number divide low presion number.
// note: the dividend here is NOT reversed.
string hpDiv1(const string &dividend, int divisor)
{
    string ans;
    int remainder = 0;

    int divsize = dividend.size();
    for (int i = 0; i < divsize; i++)
    {
        int curdigit = dividend[i] - '0';
        int curnum = remainder * 10 + curdigit;
        ans.push_back((curnum / divisor) + '0');
        remainder = curnum % divisor;
    }

    revStr(ans);
    while (ans.size() > 1 && ans.back() == '0')
    {
        ans.pop_back();
    }
    revStr(ans);
    return ans;
}

#define MAXN 10002
class hp
{
public : 
    int a[MAXN];
    hp() { memset(a, 0, sizeof(a)); }
    void clear() { memset(a, 0, sizeof(a)); }
    hp(int x)
    {
        clear();
        while (x)
        {
            a[++a[0]] = x % 10;
            x /= 10;
        }
        while (a[a[0]] == 0 && a[0])
            a[0]--;
    }
    hp &operator=(int x)
    {
        clear();
        while (x)
        {
            a[++a[0]] = x % 10;
            x /= 10;
        }
        while (a[a[0]] == 0 && a[0])
            a[0]--;
        return *this;
    }

    short cmp(const hp &x)
    {
        if (a[0] > x.a[0])
            return 1;
        if (a[0] < x.a[0])
            return -1;
        for (register int i = a[0]; i >= 1; i--)
        {
            if (a[i] > x.a[i])
                return 1;
            if (a[i] < x.a[i])
                return -1;
        }
        return 0;
    }
    bool operator>(const hp &x)
    {
        return cmp(x) == 1;
    }
    bool operator==(const hp &x)
    {
        return cmp(x) == 0;
    }
    bool operator<(const hp &x)
    {
        return cmp(x) == -1;
    }
    bool operator>=(const hp &x)
    {
        return !(*this < x);
    }
    bool operator<=(const hp &x)
    {
        return !(*this > x);
    }

    hp operator-(const hp &x)
    {
        hp a = *this, c;
        c.a[0] = a.a[0] > x.a[0] ? a.a[0] : x.a[0];
        for (register int i = 1; i <= c.a[0]; i++)
        {
            c.a[i] += a.a[i] - x.a[i];
            if (c.a[i] < 0)
            {
                c.a[i] += 10;
                a.a[i + 1]--;
            }
        }
        while (c.a[c.a[0]] == 0 && c.a[0])
            c.a[0]--;
        return c;
    }
    hp operator*(const hp &x)
    {
        hp c;
        for (register int i = 1; i <= a[0]; i++)
        {
            for (register int j = 1; j <= x.a[0]; j++)
            {
                c.a[i + j - 1] += a[i] * x.a[j];
            }
        }
        c.a[0] = a[0] + x.a[0];
        for (register int i = 1; i <= c.a[0]; i++)
        {
            if (c.a[i] >= 10)
            {
                c.a[i + 1] += c.a[i] / 10;
                c.a[i] %= 10;
            }
        }
        while (c.a[c.a[0]] == 0 && c.a[0] > 0)
            c.a[0]--;
        return c;
    }
    hp operator/(const int &x)
    {
        hp c;
        int t = 0, s = 0;
        bool flag = 1;
        for (register int i = a[0]; i >= 1; i--)
        {
            t = s * 10 + a[i];
            if (t / x > 0 || t == 0)
            {
                c.a[++c.a[0]] = t / x;
                s = t % x;
                flag = 0;
            }
            else
            {
                s = t;
                if (!flag)
                    c.a[++c.a[0]] = 0;
            }
        }
        reverse(c.a + 1, c.a + c.a[0] + 1);
        return c;
    }
};