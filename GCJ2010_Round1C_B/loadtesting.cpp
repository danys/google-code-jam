#include <iostream>

using namespace std;

long long power(long long base, long long exp)
{
    if (exp==0) return 1;
    if (exp==1) return base;
    if (exp%2==0)
    {
        long long t = power(base,exp/2);
        return t*t;
    }
    else
    {
        return base*power(base,exp-1);
    }
}

long long factor(long long C, long long n)
{
    long long t = power(2,n);
    return power(C,t);
}

int solve(long L,long P, long C)
{
    int i=0;
    while(L*factor(C,i)<P)
    {
        i++;
    }
    return i;
}

int main()
{
    int L,P,C,T;
    cin >> T;
    for(int z=1;z<=T;z++)
    {
        cin >> L >> P >> C;
        cout << "Case #" << z << ": " << solve(L,P,C);
        if (z!=T) cout << endl;
    }
    return 0;
}
