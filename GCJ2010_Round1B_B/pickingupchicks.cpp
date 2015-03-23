#include <iostream>
#include <vector>

#define maxN 50

using namespace std;

int X[maxN];
int V[maxN];
vector<int> vpos[maxN];
double totaltime[maxN];

double newpos(double x0, double v, double t)
{
    return x0+v*t;
}

double ttocross(double x1,double x2,int v1,int v2)
{
    return (double)((double)(x2-x1)/(double)(v1-v2));
}

double ttobarn(int b, int x, int v)
{
    return (double)((double)(b-x)/(double)v);
}

int solve(int n,int k,int b,int t)
{
    double goaltime,crosstime,currentpos;
    int currentspeed;
    int counter;
    counter=0;
    for(int i=n-1;i>=0;i--)
    {
        totaltime[i]=0;
        goaltime = ttobarn(b,X[i],V[i]);
        currentpos = (double)X[i];
        currentspeed = V[i];
        if(i<n-1)
        {
            vector<int> pos = vpos[i+1];
            if (pos.size()==0)
            {
                crosstime = ttocross(X[i],X[i+1],V[i],V[i+1]);
                if ((crosstime>=0) && (crosstime<goaltime))
                {
                    totaltime[i] += crosstime;
                    currentpos = newpos(currentpos,currentspeed,crosstime);
                    vpos[i].push_back(currentpos);
                    currentspeed = V[i+1];
                    goaltime = ttobarn(b,currentpos,currentspeed);
                    totaltime[i] += goaltime;
                }
                else totaltime[i] = goaltime;
            }
            else
            {
                for(int j=0;j<pos.size();j++)
                {
                    //
                }
            }
        }
        else totaltime[i] = goaltime;
        if (totaltime[i]<=t) counter++;
    }
    if (counter>=k) return 0;
    else return -1;
}

bool ispossible(int n, int k, int b, int t)
{
    int counter=0;
    for(int i=0;i<n;i++)
    {
        if (ttobarn(b,X[i],V[i])>t)
        {
            counter++;
            if (counter>n-k) return false;
        }
    }
    return true;
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
        if (!ispossible(N, K, B, T)!=-1) cout << "Case #" << z << ": IMPOSSIBLE" << endl;
        else  cout << "Case #" << z << ":" << solve(N,K,B,T) << endl;
    }
    return 0;
}
