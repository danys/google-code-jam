#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define maxsets 100
#define maxalpha 26
#define maxmod 1000000007

int nsets;
string train[maxsets];
int first[maxsets];
int last[maxsets];
bool utilized[maxsets];
int sametable[maxalpha];
bool htable[maxalpha];

long long fact(long long n)
{
    if (n<=1) return 1;
    long long result = 1;
    while(n>1)
    {
        result=(result%maxmod)*(n%maxmod);
        result=result%maxmod;
        n--;
    }
    return result;
}

bool isvalid(string str)
{
    for(int i=0;i<maxalpha;i++) htable[i]=false;
    htable[str[0]-'a']=true;
    for(unsigned int i=1;i<str.size();i++)
    {
        int cur = str[i]-'a';
        int prev = str[i-1]-'a';
        if ((cur!=prev) && (htable[cur])) return false;
        else if (cur!=prev) htable[cur]=true;
    }
    return true;
}

string compact(string str)
{
    string res="";
    unsigned int i=0;
    while(i<str.length())
    {
        char t = str[i];
        res += t;
        while(str[i]==t) i++;
    }
    return res;
}

int reduce()
{
    for(int i=0;i<nsets;i++) if (!isvalid(train[i])) return -1; //find invalid words such as 'aba'
    for(int i=0;i<nsets;i++)
    {
        int len = train[i].length();
        first[i] = train[i][0]-'a';
        last[i] = train[i][len-1]-'a';
    }
    //find inconsistent matches
    for(int i=0;i<nsets;i++)
    {
        utilized[i]=false; //initialize for later use
        for(int j=0;j<nsets;j++)
        {
            if (i==j) continue;
            if ((first[i]==first[j]) && (train[i].size()>1) && (train[j].size()>1)) return -1;
            if ((last[i]==last[j]) && (train[i].size()>1) && (train[j].size()>1)) return -1;
        }
    }
    int res = 0;
    //invalidate sets with size one that appear in previous sets
    for(int i=0;i<maxalpha;i++) htable[i]=false;
    for(int i=0;i<nsets;i++)
    {
        if(train[i].size()==1)
        {
            if (htable[train[i][0]-'a'])
            {
                utilized[i]=true;
                res++;
            }
            else htable[train[i][0]-'a']=true;
        }
        else
        {
            for(unsigned int j=0;j<train[i].size();j++)
            {
                if ((j>0) && (j<train[i].size()-1) && (train[i][j-1]!=train[i][j]) && (htable[train[i][j]-'a'])) return -1;
                htable[train[i][j]-'a']=true;
            }
        }
    }
    //find left to right match
    for(int i=0;i<nsets;i++)
    {
        for(int j=0;j<nsets;j++)
        {
            if ((i==j) || (utilized[i]) || (utilized[j])) continue;
            if (first[i]==last[j])
            {
                res++;
                utilized[i]=true;
                last[j]=last[i];
                if (last[j]==first[j]) return -1;
            }
            else if (last[i]==first[j])
            {
                res++;
                utilized[i]=true;
                first[j]=first[i];
                if (last[j]==first[j]) return -1;
            }
        }
    }
    return res;
}

long long same()
{
    long long res = 1;
    for(int i=0;i<maxalpha;i++) sametable[i]=0;
    for(int i=0;i<nsets;i++)
    {
        if (train[i].size()==1) sametable[train[i][0]-'a']++;
    }
    for(int i=0;i<maxalpha;i++) if (sametable[i]!=0) res = res%maxmod * fact(sametable[i])%maxmod;
    return res%maxmod;
}

long long compute()
{
    int r = reduce();
    if (r == -1) return 0;
    int m = nsets-r;
    long long p = same();
    long long res = ((fact((long long)m)%maxmod)*(p%maxmod))%maxmod;
    return res;
}

int main()
{
    int T;
    string temp;
    cin >> T;
    for(int t=1;t<=T;t++)
    {
        cin >> nsets;
        for(int z=1;z<=nsets;z++)
        {
            cin >> temp;
            train[z-1] = compact(temp);
        }

        cout << "Case #" << t << ": " << compute() << endl;
    }
    return 0;
}
