#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define maxsets 100
#define maxalpha 26

unsigned int nsets;
string train[maxsets];

bool htable[maxalpha];

bool isvalid(string cur, string suff)
{
    if (cur.length()==0) return true;
    else
    {
        string res=cur+suff;
        for(int i=0;i<maxalpha;i++) htable[i]=false;
        htable[res[0]-'a']=true;
        for(unsigned int i=1;i<res.size();i++)
        {
            int cur = res[i]-'a';
            int prev = res[i-1]-'a';
            if ((cur!=prev) && (htable[cur])) return false;
            else if (cur!=prev) htable[cur]=true;
        }
        return true;
    }
}

long long permutations(string result,string used,unsigned int step)
{
    long long res = 0;
    if (step==nsets) return 1;
    unsigned int j=0;
    for(unsigned int i=0;i<nsets;i++)
    {
        j=0;
        char t='0'+i;
        while((used[j]!=t) && (j<step)) j++;
        if ((j==step) && (isvalid(result,train[i])))
        {
            res = res + permutations(result+train[i],used+t,step+1);
        }
    }
    return res;
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

int main()
{
    int T;
    string temp;
    cin >> T;
    for(int t=1;t<=T;t++)
    {
        cin >> nsets;
        for(unsigned int z=1;z<=nsets;z++)
        {
            cin >> temp;
            train[z-1] = compact(temp);
            cout << "Compressed = " << train[z-1] << endl;
        }

        cout << "Case #" << t << ": " << permutations("","",0) << endl;
    }
    return 0;
}
