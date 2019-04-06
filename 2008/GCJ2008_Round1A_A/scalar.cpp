#include <iostream>

#define maxvectlen 8
#define maxperm 40320 //== 8!

using namespace std;

int vect1[maxvectlen];
int permvect1[maxperm][maxvectlen];
int vect2[maxvectlen];
int permvectlen;
int counter;

//Checks whether the position x is already in the position vector v[]
bool present(int x,int v[],int len)
{
    for(int i=0;i<len;i++) if (v[i]==x) return true;
    return false;
}

//Computes and stores all permutations of a given vector
void permutations(int vect[], int pvect[], int positions[],int resvect[][maxvectlen], int dims, int k)
{
    if (k==dims)
    {
        for(int i=0;i<dims;i++) resvect[counter][i]=pvect[i];
        counter++;
        return;
    }
    for(int i=0;i<dims;i++)
    {
        if (!present(i,positions,k))
        {
            positions[k]=i;
            pvect[k]=vect[i];
            permutations(vect,pvect,positions,resvect,dims,k+1);
        }
    }
    return;
}

//Computes an initial inner product
int initscalarp(int dims)
{
    int res=0;
    for(int i=0;i<dims;i++) res += vect1[i]*vect2[i];
    return res;
}

//Computes the lowest scalar product
int compute(int dims,int vect[])
{
    int scalarp;
    int bestscalarp=initscalarp(dims);
    for(int i=0;i<permvectlen;i++)
    {
            scalarp=0;
            for(int k=0;k<dims;k++) scalarp += permvect1[i][k]*vect[k];
            if (scalarp<bestscalarp) bestscalarp = scalarp;
    }
    return bestscalarp;
}

//Computes the factorial of a given number n
int fact(int n)
{
    if (n<=1) return 1;
    return n*fact(n-1);
}

int main()
{
    int cases, dims, c;
    int tvect[maxvectlen];
    int positions[maxvectlen];
    cin >> cases;
    for(int z=1;z<=cases;z++)
    {
        cin >> dims;
        for(c=1;c<=dims;c++) cin >> vect1[c-1];
        for(c=1;c<=dims;c++) cin >> vect2[c-1];
        permvectlen=fact(dims);
        counter=0;
        permutations(vect1,tvect,positions,permvect1,dims,0);
        cout << "Case #" << z << ": " << compute(dims,vect2) << endl;
    }
    return 0;
}
