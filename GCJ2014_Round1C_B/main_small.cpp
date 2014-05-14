#include <iostream>
#include <string>

using namespace std;

#define maxsets 100
#define maxalpha 26

unsigned int nsets;
string train[maxsets];
bool table[maxalpha];

void init()
{
    for(int i=0;i<maxalpha;i++) table[i]=false;
}

long long permutations(string result,string used,unsigned int step)
{
    long long res = 0;
    if (step==nsets)
    {
        init();
        table[result[0]-'a']=true;
        for(unsigned int i=1;i<result.size();i++)
        {
            int cur = result[i]-'a';
            int prev = result[i-1]-'a';
            if ((cur!=prev) && (table[cur])) return 0;
            else if (cur!=prev) table[cur]=true;
        }
        return 1;
    }
    unsigned int j=0;
    for(unsigned int i=0;i<nsets;i++)
    {
        j=0;
        char t='0'+i;
        while((used[j]!=t) && (j<step)) j++;
        if (j==step)
        {
            res = res + permutations(result+train[i],used+t,step+1);
        }
    }
    return res;
}

int main()
{
    int T;
    cin >> T;
    for(int t=1;t<=T;t++)
    {
        cin >> nsets;
        for(unsigned int z=1;z<=nsets;z++) cin >> train[z-1];
        cout << "Case #" << t << ": " << permutations("","",0) << endl;
    }
    return 0;
}
