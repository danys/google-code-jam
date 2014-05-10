#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MAXN 50

string zip[MAXN];
vector<int> city[MAXN];
int solution[MAXN];
bool visited[MAXN];
bool dvisited[MAXN];
int N;

void init()
{
    for(int i=0;i<MAXN;i++)
    {
        city[i].clear();
        zip[i]="";
    }
}

//returns the index of the string with the lowest value
int getmin(int n)
{
    int mindex=0;
    for(int i=1;i<n;i++)
    {
        if (atoi(zip[i].c_str())<atoi(zip[mindex].c_str())) mindex=i;
    }
    return mindex;
}

bool allreached(int step)
{
    int cc = 0;
    for(int i=0;i<N;i++) if (visited[i]) cc++;
    if (cc==N) return true;
    else
    {
        int mstr=-1;
        string str="";
        int i=2;
        while(step-i>=0)
        {
            int ccity=solution[step-i];
            for(unsigned int j=0;j<city[ccity].size();j++)
            {
                int ncity=city[ccity][j];
                if (visited[ncity]) continue;
                if ((str=="") || (zip[ncity]<str))
                {
                    str=zip[ncity];
                    mstr=ncity;
                }
            }
            i++;
        }
        if (mstr==-1) return true;
        solution[step]=mstr;
        visited[mstr]=true;
        return false;
    }
}

int dfs(int ccity,int targetcity,int firstcity)
{
    dvisited[ccity]=true;
    cout << "Ccity = " << ccity << endl;
    for(unsigned int i=0;i<city[ccity].size();i++)
    {
        int ncity = city[ccity][i];
        cout << "Ncity = " << ncity << " targetcoty = " << targetcity << endl;
        if (visited[ncity] || dvisited[ncity]) continue;
        if (ncity==targetcity)return firstcity;//true;
        else
        {
            if (firstcity==-1) return dfs(ncity,targetcity,ncity);
            else return dfs(ncity,targetcity,firstcity);
        }
    }
    return -1;//false;
}

bool betterreachable(int ncity,int pcity)
{
    //cout << "Betterreach = " << ncity << " go to city = " << pcity << endl;
    string temp=zip[ncity];
    // zip and city[][]
    //pcity -> ncity cheaper
    /*bool*/int fcity = dfs(pcity,ncity,-1);
    if (fcity!=-1) cout << "Ncity soltz = " << ncity << endl;
    if ((fcity!=-1) && (zip[fcity]<temp)) {cout << "Hello" << endl;return true;}
    else return false;
}

string solve(int step)
{
    int ccity = solution[step-1];
    string result = zip[ccity];
    string str="";
    int mstr=-1;
    for(unsigned int c=0;c<city[ccity].size();c++)
    {
        int ncity = city[ccity][c];
        if (visited[ncity]) continue;
        if ((str=="") || (zip[ncity]<str))
        {
            str=zip[ncity];
            mstr=ncity;
            //dvisited[mstr]=true;
        }
    }
    if (str!="")
    {
        for(int j=2;j<=step;j++)
            {
                memset(dvisited,false,sizeof(dvisited));
                cout << "Step = " << step  << endl;
             if(betterreachable(mstr,solution[step-j]))
             {
                str="";
                break;
             }
            }
    }
    if (str=="")
    {
        if (allreached(step)) return result;
        else return result+solve(step+1);
    }
    solution[step]=mstr;
    visited[mstr]=true;
    return result+solve(step+1);
}

int main()
{
    int T,M;
    cin >> T;
    for(int t=1;t<=T;t++)
    {
        cin >> N >> M;
        init(); //initialize arrays
        for(int n=1;n<=N;n++) cin >> zip[n-1];
        int node1, node2;
        for(int n=1;n<=M;n++)
        {
            cin >> node1;
            cin >> node2;
            city[node1-1].push_back(node2-1);
            city[node2-1].push_back(node1-1);
        }
        int start = getmin(N);
        //for(int i=0;i<MAXN;i++) visited[i]=false;
        memset(visited,false,sizeof(visited));
        solution[0]=start;
        visited[start]=true;
        cout << "Case #" << t << ": " << solve(1) << endl;
    }
    return 0;
}
