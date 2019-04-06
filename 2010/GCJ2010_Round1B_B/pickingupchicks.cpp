#include <iostream>
#include <vector>

#define maxN 50

using namespace std;

int X[maxN];
int V[maxN];
void solve(int n,int k,int b,int t)
{
    int slowchicks=0;
    int fastchicks=0;
    int res=0;
    for (int i=n-1;i>=0;i--)
    {
        if (fastchicks==k) break;
        if (X[i]+t*V[i]<b) slowchicks++;
        else
        {
            fastchicks++;
            res += slowchicks;
        }
    }
    if (fastchicks >= k) cout << res;
    else cout << "IMPOSSIBLE";
}

int main()
{
    int N,K,B,T,C;
    cin >> C;
    for(int z=1;z<=C;z++)
    {
        cin >> N >> K >> B >> T;
        for(int i=0;i<N;i++) cin >> X[i];
        for(int i=0;i<N;i++) cin >> V[i];
        cout << "Case #" << z << ":";
        solve(N,K,B,T);
        cout << endl;
    }
    return 0;
}
