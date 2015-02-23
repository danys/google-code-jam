#include <iostream>

#define maxvectlen 8
#define maxperm 40320 //== 8!

using namespace std;

int vect1[maxvectlen];
int permvect1[maxperm][maxvectlen];
int vect2[maxvectlen];
int permvect2[maxperm][maxvectlen];
int permvectlen;
int counter;

bool present(int x,int v[],int len)
{
    for(int i=0;i<len;i++) if (v[i]==x) return true;
    return false;
}

void permutations(int vect[], int pvect[], int resvect[][maxvectlen], int dims, int k)
{
    if (k==dims)
    {
        for(int i=0;i<dims;i++) resvect[counter][i]=pvect[i];
        counter++;
        return;
    }
    for(int i=0;i<dims;i++)
    {
        if (!present(vect[i],pvect,k))
        {
            pvect[k]=vect[i];
            permutations(vect,pvect,resvect,dims,k+1);
        }
    }
}

int initscalarp(int dims)
{
    int res=0;
    for(int i=0;i<dims;i++) res += vect1[i]*vect2[i];
    return res;
}

int compute(int dims)
{
    int scalarp;
    int bestscalarp=initscalarp(dims);
    for(int i=0;i<permvectlen;i++)
    {
        for(int j=0;j<permvectlen;j++)
        {
            scalarp=0;
            for(int k=0;k<dims;k++) scalarp += permvect1[i][k]*permvect2[j][k];
            if (scalarp<bestscalarp) bestscalarp = scalarp;
        }
    }
    return bestscalarp;
}

void printperm(int n,int dim)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<dim;j++)
        {
            cout << permvect1[i][j] << " ";
        }
        cout << endl;
    }
}

int fact(int n)
{
    if (n<=1) return 1;
    return n*(n-1);
}

int main()
{
    int cases, dims, c;
    int tvect[maxvectlen];
    cin >> cases;
    for(int z=1;z<=cases;z++)
    {
        cin >> dims;
        for(c=1;c<=dims;c++) cin >> vect1[c-1];
        for(c=1;c<=dims;c++) cin >> vect2[c-1];
        permvectlen=fact(dims);
        counter=0;
        permutations(vect1,tvect,permvect1,dims,0);
        counter=0;
        permutations(vect2,tvect,permvect2,dims,0);
        cout << "Case #" << z << ": " << compute(dims) << endl;
    }
    return 0;
}
