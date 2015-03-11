#include <iostream>
#include <math.h>

using namespace std;

int** sol;
int** init;

//Multiply two matrices A and B store the result in C
void matrixmult(int** A, int** B, int** C)
{

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            C[i][j]=0;
            for(int k=0;k<2;k++) C[i][j] = (C[i][j]+A[i][k]*B[k][j])%1000;
        }
    }
}

//Set values a,b,c,d in matrix in matrix with rows
//Row 0: a,b
//Row 1: c,b
void seta(int** m, int a, int b, int c, int d)
{
    m[0][0]=a;
    m[0][1]=b;
    m[1][0]=c;
    m[1][1]=d;
}

//Allocate storage for matrix a
int** anew(int** a)
{
    a = new int*[2];
    a[0]=new int[2];
    a[1]=new int[2];
    return a;
}

//Free storage of matrix a
void rema(int** a)
{
    delete [] a[0];
    delete [] a[1];
    delete [] a;
}

//Method computes the in^n using the fast exponentiation algorithm
void solve(int** in,long long n,int** out)
{
    if (n==1)
    {
        seta(out,in[0][0],in[0][1],in[1][0],in[1][1]);
        return;
    }
    else
    {
        int** t = 0;
        t = anew(t);
        if (n%2==0)
        {
            solve(in,n/2,t);
            matrixmult(t,t,out);
            return;
        }
        else
        {
            solve(in,n-1,t);
            matrixmult(in,t,out);
            return;
        }
        rema(t);
    }
}

//Method calls solve and prints the final result
void printn(long long n)
{
    solve(init,n,sol);
    int res = (2*sol[0][0]-1)%1000;
    if (res<10) cout << "00" << res;
    else if (res<100) cout << "0" << res;
    else cout << res;
}

int main()
{
    int T;
    long long n;
    cin >> T;
    init = anew(init);
    seta(init,3,5,1,3);
    sol = anew(sol);
    seta(sol,0,0,0,0);
    for(int z=1;z<=T;z++)
    {
        cin >> n;
        cout << "Case #" << z << ": ";
        printn(n);
        cout << endl;
    }
    rema(init);
    rema(sol);
    return 0;
}
