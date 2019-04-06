#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#define maxN 2000
#define maxM 2000

using namespace std;

int C,N,M;

int sol[maxN];

vector<pair<int,int>> compactlikes[maxM];
int maltedi[maxM];

void printsol()
{
    for(int i=0;i<N;i++)
    {
        if(i!=N-1) cout << sol[i] << " ";
        else cout << sol[i];
    }
    cout << endl;
}

//O(N) worst-case execution time
bool custok(int id)
{
    vector<pair<int,int>> v = compactlikes[id];
    int malted,shake;
    for(unsigned int i=0;i<v.size();i++)
    {
        pair<int,int> p = v[i];
        shake = p.first;
        malted = p.second;
        if (sol[shake]==malted) return true;
    }
    return false;
}

//O(N*M) worst-case execution time
bool allcustok()
{
    for(int i=0;i<M;i++) if (!custok(i)) return false;
    return true;
}

//While loop will be executed at most two times
//O(N*M) worst-case execution time
bool solve()
{
    vector<pair<int,int>> v;
    while(true)
    {
        for(int i=0;i<M;i++)
        {
            if (custok(i)) continue;
            if (maltedi[i]==-1) return false;
            else sol[maltedi[i]]=1;
        }
        if (allcustok()) break;
    }
    return true;
}

void insertcustlikes(int id, int shake, int malted)
{
    pair<int,int> p(shake,malted);
    vector<pair<int,int>> v = compactlikes[id];
    v.push_back(p);
    compactlikes[id]=v;
}

void init()
{
    for(int i=0;i<M;i++)
    {
        compactlikes[i].clear();
        maltedi[i]=-1;
    }
    for(int j=0;j<N;j++)    sol[j]=0;
}

//Large input solution for the Milkshake problem
//O(N*M) worst-case execution time per case
int main()
{
    cin >> C;
    int T, m, malted;
    for(int z=1;z<=C;z++)
    {
        cin >> N; //#milkshake flavors
        cin >> M; //#customers
        init();
        for(int l=1;l<=M;l++)
        {
            cin >> T;
            for(int col=1;col<=T;col++)
            {
                cin >> m;
                cin >> malted;
                insertcustlikes(l-1,m-1,malted);
                if (malted==1) maltedi[l-1]=m-1;
            }
        }
        if (solve())
        {
            cout << "Case #" << z << ": ";
            printsol();
        }
        else cout << "Case #" << z << ": IMPOSSIBLE" << endl;
    }
    return 0;
}
