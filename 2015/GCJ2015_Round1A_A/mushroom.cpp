#include <iostream>

#define maxl 1000

using namespace std;

long long m[maxl];
long long a;
long long b;

void solve(int n)
{
    long long total = 0,speed = 0;
    for(int i=0;i<n-1;i++)
    {
        if (m[i]-m[i+1]>0)
        {
                total += m[i]-m[i+1];
                speed = max(speed,m[i]-m[i+1]);
        }
    }
    a = total;
    b = 0;
    for(int i=0;i<n-1;i++)
    {
        if (m[i]-speed>=0) b += speed;
        else b += m[i];
    }
}

int main()
{
    int T,N;
    cin >> T;
    for(int z=1;z<=T;z++)
    {
        cin >> N;
        for(int i=1;i<=N;i++) cin >> m[i-1];
        solve(N);
        cout << "Case #" << z << ": " << a << " " << b;
        if (z!=T) cout << endl;
    }
    return 0;
}
