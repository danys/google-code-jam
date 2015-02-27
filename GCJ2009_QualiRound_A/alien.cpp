#include <iostream>
#include <vector>
#include <set>
#include <string>

#define maxl 15
#define maxd 5000
#define maxn 500
#define maxa 26

using namespace std;

//Hashtable with set chaining strategy
set<int> ht[maxa][maxl];

int l,d,n;

//For every character of the string put the dictionary index into a hash table
void pushinto(int index, string s)
{
    for(unsigned int i=0;i<s.length();i++)  ht[s[i]-'a'][i].insert(index);
}

//Returns the smallest common subset of two sets or set s2 if first==true
set<int> minify(set<int> s1, set<int> s2, bool first)
{
    if (first) return s2;
    set<int> res;
    for (set<int>::iterator it=s1.begin(); it!=s1.end(); ++it)
    {
        if (s2.find(*it) != s2.end()) res.insert(*it);
    }
    return res;
}

int compute(string s)
{
    unsigned int i=0,relativei=0;
    set<int> indexs, temps, singles;
    bool first=true;
    while(i<s.length())
    {
        if (s[i]=='(')
        {
            temps.clear();
            i++;
            singles.clear();
            while(s[i]!=')')
            {
                //merge matching dictionary possibilities
                singles.insert(ht[s[i]-'a'][relativei].begin(),ht[s[i]-'a'][relativei].end());
                i++;
            }
            temps = singles;
            relativei++;
        }
        else if (s[i]==')')
        {
            indexs=minify(indexs,temps,first);
            if (first) first=false;
            i++;
        }
        else
        {
            temps.clear();
            singles.clear();
            singles.insert(ht[s[i]-'a'][relativei].begin(),ht[s[i]-'a'][relativei].end());
            temps = singles;
            i++;
            indexs=minify(indexs,temps,first);
            if (first) first=false;
            relativei++;
        }
    }
    return indexs.size();
}

int main()
{
    cin >> l >> d >> n;
    string s;
    for(int z=1;z<=d;z++)
    {
        cin >> s;
        pushinto(z-1,s);
    }
    for(int z=1;z<=n;z++)
    {
        cin >> s;
        cout << "Case #" << z << ": " << compute(s) << endl;
    }
    return 0;
}
