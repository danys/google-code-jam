#include <iostream>
#include <vector>

#define maxlen 512

using namespace std;

int board[maxlen][maxlen];
int f[maxlen+1];
vector<int> dims;

void converttoarray(int x, int (&a)[4])
{
    for(int i=0;i<4;i++) a[i]=0;
    int counter=0;
    while (x>0)
    {
        if (x%2==1) a[3-counter]=1;
        counter++;
        x=x/2;
    }
}

void insertinboard(int x,int rowindex, int colindex)
{
    int a[4];
    converttoarray(x,a);
    for(int i=0;i<4;i++)    board[rowindex][colindex+i]=a[i];
}

int convertchartoint(char c)
{
    int res = c - 'A';
    if (res>=0) return res+10; //we have A,B,C,D,E,F
    else res = c - '0'; //we have 0,1,...,9
    return res;
}

void init(int len)
{
    for(int i=0;i<len+1;i++) f[i]=0;
    dims.clear();
}

void insertinres(int t)
{
    for(unsigned int i=0;i<dims.size();i++) if (dims[i]==t) return;
    dims.push_back(t);
}

int invert(int x)
{
    if (x==1) return 0;
    return 1;
}

int color(int ocolor,int x, int y)
{
    int res = ocolor;
    for(int i=1;i<=x+y;i++) res = invert(res);
    return res;
}

bool findboardandcut(int m, int n, int t,int &ncells)
{
    bool found;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if (board[i][j]==-1) continue; //cell is non-existent
            if ((i+t-1>=m) || (j+t-1>=n)) continue;
            found = true;
            for(int x=i;x<m && x-i+1<=t && found==true;x++)
            {
                for(int y=j;y<n && y-j+1<=t && found==true;y++)
                {
                    if (board[x][y]!=color(board[i][j],x-i,y-j))
                    {
                        found=false;
                        break;
                    }
                }
            }
            if (found)
            {
                for(int x=i;x<m && x-i+1<=t;x++)
                {
                    for(int y=j;y<n && y-j+1<=t;y++)
                    {
                        board[x][y]=-1;
                    }
                }
                ncells += t*t;
                return true;
            }
        }
    }
    return false;
}

void solve(int m, int n)
{
    int t,totalcells,cutcells;
    t = (m<n) ? m : n; // minimum of m and n
    init(t);
    totalcells = m*n;
    cutcells=0;
    while((cutcells<totalcells) && (t>=1))
    {
        if (findboardandcut(m,n,t,cutcells))
        {
            f[t]++;
            insertinres(t);
        }
        else t--;
    }
}

void printres()
{
    for(unsigned int i=0;i<dims.size();i++)  cout << dims[i] << " " << f[dims[i]] << endl;
}

int main()
{
    int T,M,N;
    char c;
    cin >> T;
    for(int z=1;z<=T;z++)
    {
        cin >> M >> N;
        for(int row=1;row<=M;row++)
        {
            for(int col=1;col<=N/4;col++)
            {
                cin >> c;
                insertinboard(convertchartoint(c),row-1,(col-1)*4);
            }
        }
        solve(M,N);
        cout << "Case #" << z << ": " << dims.size() << endl;
        printres();
    }
    return 0;
}
