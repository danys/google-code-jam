#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,int>> pairs;
vector<int> h;

int T,N;

void insertpair(int a,int b)
{
    pair<int,int> p(a,b);
    pairs.push_back(p);
    h.push_back(b);
}

int binsearch(int l,int r, int x)
{
    int index = (l+r)/2;
    if ((r-l==0) && (h[index]!=x)) return -1; //Nothing found
    if (h[index]==x) return index;
    if (h[index]<x)
    {
        return binsearch(index+1,r,x);
    }
    else return binsearch(l,index-1,x);
}

int solve()
{
    int res = 0;
    int second,newindex,diff;
    for(unsigned int i=0;i<pairs.size();i++)
    {
        second = pairs[i].second;
        newindex = binsearch(0,h.size()-1,second);
        diff = newindex-i;
        if (diff>0) res += diff;
    }
    return res;
}

bool cmp (pair<int,int> i,pair<int,int> j)
{
    return (i.first<j.first);
}

int main()
{
    cin >> T;
    int a,b;
    for(int z=1;z<=T;z++)
    {
        pairs.clear();
        h.clear();
        cin >> N;
        for(int i=0;i<N;i++)
        {
            cin >> a >> b;
            insertpair(a,b);
        }
        sort(pairs.begin(),pairs.end(),cmp);
        sort(h.begin(),h.end());
        cout << "Case #" << z << ": " << solve() << endl;
    }
    return 0;
}
