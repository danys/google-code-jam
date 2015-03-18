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
        if (path[i]!='/') curname.push_back(path[i]);
        else if ((path[i]=='/') || (i==path.size()-1))
        {
            a[len]=curname;
            len++;
            curname="";
        }
    }
}

void insertIntoTree(int k,string a[maxpathlen],int len)
{
    //recursive algorithm
}

void insertPath(string path)
{
    int len;
    string stra[maxpathlen];
    convertToArray(path,stra,len);
    //insertInToTree(...)
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
