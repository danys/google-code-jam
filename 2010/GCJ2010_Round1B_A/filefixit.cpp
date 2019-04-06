#include <iostream>
#include <string>
#include <vector>

#define maxpathlen 100

using namespace std;

vector<vector<pair<string,int>>> tree;
int nnodes;

void insertroot()
{
    tree.clear();
    nnodes=0;
    vector<pair<string,int>> node;
    node.clear();
    tree.push_back(node);
    nnodes++;
}

void convertToArray(string path,string (&a)[maxpathlen], int &len)
{
    string curname="";
    len=0;
    for(unsigned int i=0;i<path.size();i++)
    {
        if ((i==0) && (path[i]!='/')) return;
        if (i==0) continue;
        if (i==path.size()-1)
        {
            curname.push_back(path[i]);
            a[len]=curname;
            len++;
            curname="";
        }
        else if (path[i]=='/')
        {
            a[len]=curname;
            len++;
            curname="";
        }
        else if (path[i]!='/') curname.push_back(path[i]);
    }
}

void insertIntoTree(int k,string a[maxpathlen],int len,int curnode)
{
    if (k==len) return;
    vector<pair<string,int>> v = tree[curnode];
    if (v.size()==0)
    {
        pair<string,int> p(a[k],tree.size());
        v.push_back(p);
        tree[curnode] = v;
        vector<pair<string,int>> vnew;
        vnew.clear();
        tree.push_back(vnew);
        nnodes++;
        insertIntoTree(k+1,a,len,p.second);
        return;
    }
    pair<string,int> p;
    string nodestr;
    int nodeindex;
    bool found=false;
    unsigned int s = v.size();
    for(unsigned int i=0;(i<s) && (found==false);i++)
    {
        p = v[i];
        nodestr=p.first;
        nodeindex=p.second;
        if (nodestr==a[k])
        {
            insertIntoTree(k+1,a,len,nodeindex);
            found=true;
        }
    }
    if (found==false)
    {
        pair<string,int> p(a[k],tree.size());
        v.push_back(p);
        tree[curnode] = v;
         vector<pair<string,int>> vnew;
        vnew.clear();
        tree.push_back(vnew);
        nnodes++;
        insertIntoTree(k+1,a,len,p.second);
    }
    return;
}

void insertPath(string path)
{
    int len;
    string stra[maxpathlen];
    convertToArray(path,stra,len);
    insertIntoTree(0,stra,len,0);
}

int main()
{
    int T,M,N,countOld;
    string s;
    cin >> T;
    for(int z=1;z<=T;z++)
    {
        insertroot();
        cin >> N >> M;
        for(int i=0;i<N;i++)
        {
            cin >> s;
            insertPath(s);
        }
        countOld = nnodes;
        for(int i=0;i<M;i++)
        {
            cin >> s;
            insertPath(s);
        }
        cout << "Case #" << z << ": " << nnodes-countOld << endl;
    }
    return 0;
}
