#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

const int maxnodes = 1000;

struct node
{
    int parent;
    int nodeid;
};

int treematrix[maxnodes][maxnodes];
int nneighbors[maxnodes];
int rootlist[maxnodes];

void init()
{
    for(int i=0;i<maxnodes;i++)
    {
        nneighbors[i]=0;//length=0
        for(int j=0;j<maxnodes;j++)
            treematrix[i][j]=-1;
        rootlist[i]=-1;
    }
}

void populatematrix(int node1, int node2)
{
    bool found=false;
    //go to node1, check if node2 there if not insert
    for(int i=0;i<nneighbors[node1];i++)
    {
        if (treematrix[node1][i]==node2) found=true;
    }
    if (!found)
    {
        treematrix[node1][nneighbors[node1]]=node2;
        nneighbors[node1]++;
    }
    found=false;
    //go to node2, check if node1 there if not insert
    for(int i=0;i<nneighbors[node2];i++)
    {
        if (treematrix[node2][i]==node1) found=true;
    }
    if (!found)
    {
        treematrix[node2][nneighbors[node2]]=node1;
        nneighbors[node2]++;
    }
}

void rootsearcher(int nnodes)
{
    if (nnodes==2)
    {
        rootlist[0]=0;
        rootlist[1]=-1;
        return;
    }
    int counter=0;
    for(int i=0;i<nnodes;i++)
    {
        if (nneighbors[i]==2)
        {
            rootlist[counter]=i;
            counter++;
        }
    }
    for(int i=0;i<nnodes;i++)
    {
        if (nneighbors[i]>2)
        {
            rootlist[counter]=i;
            counter++;
        }
    }
    if (counter<=maxnodes-1) rootlist[counter]=-1;
}

//rearrange for each new root
void rearrange(int root,int nnodes)
{
    int temp;
    //look for a treematrix[i][0]==-1 field
    for(int i=0;i<nnodes;i++)
    {
        if (treematrix[i][0]==-1)
        {
            treematrix[i][0]=treematrix[i][nneighbors[i]-1];
            nneighbors[i]--;
            break;
        }
    }
    temp = treematrix[root][0];
    treematrix[root][0] = -1;//-1 means that root has no parent
    treematrix[root][nneighbors[root]]=temp;
    nneighbors[root]++;
    stack<node> treestack;
    node currentnode, nextnode;
    for(int i=1;i<nneighbors[root];i++)
    {
        currentnode.nodeid=treematrix[root][i];
        currentnode.parent=root;
        treestack.push(currentnode);
    }
    while(treestack.size()!=0)
    {
        currentnode = treestack.top();
        treestack.pop();
        if (treematrix[currentnode.nodeid][0]!=currentnode.parent)
        {
            temp = treematrix[currentnode.nodeid][0];
            treematrix[currentnode.nodeid][0] = currentnode.parent;
            for(int i=1;i<nneighbors[currentnode.nodeid];i++)
            {
                if (treematrix[currentnode.nodeid][i] == currentnode.parent)
                {
                    treematrix[currentnode.nodeid][i] = temp;
                    break;
                }

            }
        }
        nextnode.parent=currentnode.nodeid;
        for(int i=1;i<nneighbors[currentnode.nodeid];i++)
        {
            nextnode.nodeid=treematrix[currentnode.nodeid][i];
            if (nextnode.nodeid!=-1) treestack.push(nextnode);
        }
    }
}

//number of nodes in a maximum full tree
int nmax(int node)
{
    int counter = 0;
    int tempcounter = 0;
    if (nneighbors[node]<=2) return 1;
    else
    {
        for(int i=1;i<nneighbors[node];i++)
        {
            for(int j=i+1;j<nneighbors[node];j++)
            {
                tempcounter = 1+nmax(treematrix[node][i])+nmax(treematrix[node][j]);
                if (tempcounter>counter) counter=tempcounter;
            }
        }
    }
    return counter;
}

int main()
{
    string line;
    getline(cin,line);
    stringstream linestream(line);
    int numbertestcases;
    int nnodes;
    int node1, node2,i,mindeletes,ndeletes,currentnode;
    linestream >> numbertestcases;
    for(int z=1;z<=numbertestcases;z++)
    {
        getline(cin,line);
        stringstream caseline(line);
        caseline >> nnodes;
        init();
        for(int y=0;y<nnodes-1;y++)
        {
            getline(cin,line);
            stringstream edge(line);
            edge >> node1;
            edge >> node2;
            populatematrix(node1-1,node2-1);//-1 since matrix stores node indexes 0 to nnodes-1
        }
        i=0;
        mindeletes = nnodes;
        rootsearcher(nnodes);
        while((i<maxnodes) && (rootlist[i]!=-1))
        {
            currentnode = rootlist[i];
            rearrange(currentnode,nnodes);
            ndeletes=0;
            ndeletes = nnodes - nmax(rootlist[i]);
            if (ndeletes<mindeletes) mindeletes=ndeletes;
            i++;
        }
        cout << "Case #" << z << ": " << mindeletes << endl;
    }
}
