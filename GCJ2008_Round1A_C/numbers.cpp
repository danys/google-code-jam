#include <iostream>
#include <math.h>

using namespace std;

int** sol;
int** init;

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

void solve(int** in,long long n,int** out)
{
    if (n==1)
    {
        out[0][0] = in[0][0];
        out[0][1] = in[0][1];
        out[1][0] = in[1][0];
        out[1][1] = in[1][1];
        return;
    }
    else
    {
        int** t = new int*[2];
        t[0]=new int[2];
        t[1]=new int[2];
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
        delete [] t[0];
        delete [] t[1];
        delete [] t;
    }
}

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
    init = new int*[2];
    init[0]=new int[2];
    init[1]=new int[2];
    init[0][0]=3;
    init[0][1]=5;
    init[1][0]=1;
    init[1][1]=3;
    sol = new int*[2];
    sol[0]=new int[2];
    sol[1]=new int[2];
    sol[0][0]=0;
    sol[0][1]=0;
    sol[1][0]=0;
    sol[1][1]=0;
    for(int z=1;z<=T;z++)
    {
        cin >> n;
        cout << "Case #" << z << ": ";
        printn(n);
        cout << endl;
    }
    delete [] init[0];
    delete [] init[1];
    delete [] init;
    delete [] sol[0];
    delete [] sol[1];
    delete [] sol;
    return 0;
}
