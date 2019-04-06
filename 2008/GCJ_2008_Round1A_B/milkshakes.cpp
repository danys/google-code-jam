#include <iostream>
#include <vector>
#include <algorithm>

#define maxN 2000
#define maxM 2000

using namespace std;

int C,N,M;

vector<int> ht[maxN];
int sol[maxN];
int ressol[maxN];
int cust[maxM][maxN];
bool custt[maxM];

void insertm(int m, int malted)
{
    vector<int> v = ht[m];
    if (find(v.begin(), v.end(), malted)==v.end())
    {
        v.push_back(malted);
        ht[m]=v;
    }
}

void printsol()
{
    for(int i=0;i<N;i++)
    {
        if(i!=N-1) cout << ressol[i] << " ";
        else cout << ressol[i];
    }
}

void init()
{
    for(int i=0;i<N;i++)
    {
        sol[i]=0;
        ressol[i]=-1;
        ht[i].clear();
    }
    for(int i=0;i<maxM;i++)
    {
        for(int j=0;j<maxN;j++)
        {
            cust[i][j]=-1;
        }
    }
}

void clearcustt()
{
    for(int i=0;i<maxM;i++) custt[i]=false;
}

bool isSol()
{
    int res=0;
    clearcustt();
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++)
        {
            if ((cust[j][i]==sol[i]) && (custt[j]==false))
            {
                res++;
                custt[j]=true;
            }
        }
    }
    if (res==M) return true;
    return false;
}

void copysol()
{
    for(int i=0;i<N;i++) ressol[i]=sol[i];
}

bool isBetter()
{
    int csol,cressol;
    csol=0;
    cressol=0;
    for(int i=0;i<N;i++)
    {
        if (sol[i]==1) csol++;
        if (ressol[i]==1) cressol++;
    }
    return (csol<cressol);
}

bool solve(int m)
{
    bool b=false;
    if ((m==N) && (isSol()) && ((ressol[0]==-1) || (isBetter())))
    {
        b=true;
        copysol();
    }
    else
    {
        if (m>=N)
        {
            b=false;
        }
        else
        {
            vector<int> v=ht[m];
            if (v.size()==0)
            {
                b=solve(m+1);
            }
            else
            {
                for(unsigned int i=0;i<v.size();i++)
                {
                    sol[m]=v[i];
                    if (solve(m+1)) b=true;
                }
            }
        }
    }
    return b;
}

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
                insertm(m-1,malted);
                if ((T>1) && (malted==1)) insertm(m-1,0);
                cust[l-1][m-1]=malted;
            }
        }
        if (solve(0))
        {
            cout << "Case #" << z << ": ";
            printsol();
            cout << endl;
        }
        else cout << "Case #" << z << ": IMPOSSIBLE" << endl;
    }
    return 0;
}
