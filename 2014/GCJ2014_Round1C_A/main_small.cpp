#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

int nume;
int deno;

double convert(string str)
{
    double res = 0.0;
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
    nume=atoi(num.c_str());
    deno=atoi(den.c_str());
    res=(double)atoi(num.c_str())/(double)atoi(den.c_str());
    return res;
}

int power2(int n)
{
    int res=1;
    if (n==0) return 1;
    for(int i=1;i<=n;i++)
        res=res*2;
    return res;
}

bool checkvalid()
{
    double res = log2(deno);
    int r = nearbyint(res);
    if ((nume<=deno) && (power2(r)==deno)) return true;
    else return false;
}

int compute(double x)
{
    double res = log2(1.0/x);
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
        double x;
        getline(cin,line);
        x = convert(line);
        if (!checkvalid()) cout << "Case #" << t << ": " << "impossible" << endl;
        else
        {
            cout << "Case #" << t << ": " << compute(x) << endl;
        }
    }
    return 0;
}
