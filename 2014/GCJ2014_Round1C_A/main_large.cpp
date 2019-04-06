#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

long long nume;
long long deno;

long long power10(int n)
{
    long long res=1;
    if (n==0) return 1;
    for(int i=1;i<=n;i++)
        res=res*10;
    return res;
}

long long strtolong(string str)
{
    long long result = 0;
    int l=str.length();
    for(unsigned int i=0;i<str.length();i++)
    {
        result += (str[i]-'0')*power10(l-i-1);
    }
    return result;
}

void convert(string str)
{
    //double res = 0.0;
    int index=0;
    for(unsigned int i=0;i<str.length();i++)
    {
        if (str[i]=='/')
        {
            index=i;
            break;
        }
    }
    string num=str.substr(0,index);
    string den=str.substr(index+1);
    nume=strtolong(num);
    deno=strtolong(den);
}

long long power2(int n)
{
    long long res=1;
    if (n==0) return 1;
    for(int i=1;i<=n;i++)
        res=res*2;
    return res;
}

long long gcd(long long a,long long b)
{
    if (b==0) return a;
    else return gcd(b,a%b);
}

bool reduce()
{
    if (nume>deno) return false;
    if (deno%nume==0)
    {
        deno=deno/nume;
        nume=1;
        return true;
    }
    long long div = gcd(deno,nume);
    nume=nume/div;
    deno=deno/div;
    return true;
}

bool checkvalid()
{
    if (!reduce()) return false;
    double res = log2(deno);
    int r = nearbyint(res);
    if ((nume<=deno) && (power2(r)==deno)) return true;
    else return false;
}

long long compute()
{
    double x = (double)deno/(double)nume;
    double res = log2(x);
    return ceil(res);
}

int main()
{
    int T;
    string line;
    getline(cin,line);
    stringstream firstline(line);
    firstline >> T;
    for(int t=1;t<=T;t++)
    {
        getline(cin,line);
        convert(line);
        if (!checkvalid()) cout << "Case #" << t << ": " << "impossible" << endl;
        else
        {
            cout << "Case #" << t << ": " << compute() << endl;
        }
    }
    return 0;
}
