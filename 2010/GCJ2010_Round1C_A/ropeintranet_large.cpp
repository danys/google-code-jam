#include <iostream>
#include <vector>
#include <algorithm>

#define maxn 1000

using namespace std;

int a[maxn];
int b[maxn];

int T,N;

int solve()
{
    int res = 0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N && j<=i;j++)
        {
            if ((a[i]-a[j])*(b[i]-b[j])<0) res++;
        }
    }
    return res;
}

bool cmp (pair<int,int> i,pair<int,int> j)
{
    return (i.first<j.first);
}

int main()
{
    cin >> T;
    int A,B;
    for(int z=1;z<=T;z++)
    {
        cin >> N;
        for(int i=0;i<N;i++)
        {
            cin >> A >> B;
            a[i]=A;
            b[i]=B;
        }
        cout << "Case #" << z << ": " << solve();
        if (z!=T) cout << endl;
    }
    return 0;
}
