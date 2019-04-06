#include <iostream>
#include <string>

using namespace std;

#define maxcount 20
int board[maxcount][maxcount];

int power2(int x)
{
    if (x<=0) return 1;
    int res=1;
    for(int i=1;i<=x;i++) res=res*2;
    return res;
}

string ntostr(int x, int len)
{
    string str="";
    if (x==0) str="0";
    else
    {
        while(x>0)
        {
            if (x%2==0) str.insert(0,"0");
            else str.insert(0,"1");
            x=x/2;
        }
    }
    int l=str.length();
    if (l<len) for(int i=1;i<=len-l;i++) str.insert(0,"0");
    return str;
}

int countones(string str)
{
    int res=0;
    for(unsigned int i=0;i<str.length();i++)
    {
        if (str[i]=='1') res++;
    }
    return res;
}

void fillcells(string str,int n,int m)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            board[i][j]=0; //initialization
            int pos=m*i+j;
            if (str[pos]=='1') board[i][j]=1;
        }
    }
}

int countborder(int n, int m)
{
    int res=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if ((board[i][j]==1) && (i-1>=0) && (j-1>=0) && (i+1<=n-1) && (j+1<=m-1) && (board[i-1][j]==1) && (board[i+1][j]==1) && (board[i][j-1]==1) && (board[i][j+1]==1))
            {
                res++;
            }
        }
    }
    return res;
}

int solve(int n,int m,int k)
{
    int ncells = n*m;
    int ncomb = power2(ncells);
    string str;
    int maxres = k;
    int counter;
    for(int i=0;i<ncomb;i++)
    {
        str = ntostr(i,ncells);
        if (countones(str)!=k) continue;
        fillcells(str,n,m);
        counter = k-countborder(n,m);
        if (counter<maxres)
        {
            maxres=counter;
        }
    }
    return maxres;
}

int main()
{
    int T, n, m, k;
    cin >> T;
    for(int t=1;t<=T;t++)
    {
        cin >> n >> m >> k;
        cout << "Case #" << t << ": " << solve(n,m,k) << endl;
    }
    return 0;
}
