#include <iostream>
#include <string.h>

#define maxlen 502
#define mod 100003

using namespace std;

long long table[maxlen];
long long matrix[maxlen][maxlen-1];
long long combinations[maxlen][maxlen];

void init()
{
    memset(table,0,maxlen*sizeof(long long));
    memset(matrix,0,maxlen*(maxlen-1)*sizeof(long long));
    memset(combinations,-1,maxlen*maxlen*sizeof(long long));
    for(int i=0;i<maxlen;i++) matrix[i][1]=1;
}

long long nchoosek(long long n, long long k)
{
    if ((k==0) || (n==k)) return 1;
    if (n<k) return 0;
    if (combinations[n][k]!=-1) return combinations[n][k];
    combinations[n][k]=(nchoosek(n-1,k-1)+nchoosek(n-1,k))%mod;
    return combinations[n][k];
}

void computeMatrix()
{
    init();
    for(int i=2;i<maxlen;i++)
    {
        for(int j=2;j<i;j++)
        {
            matrix[i][j]=0;
            for(int k=1;k<j;k++)
            {
                matrix[i][j] += matrix[j][k]*nchoosek(i-j-1,j-k-1);
            }
            matrix[i][j] %= mod;
        }
    }
    for(int i=2;i<=maxlen;i++)
    {
        for(int j=1;j<maxlen;j++) table[i] = (table[i]+matrix[i][j])%mod;
    }
}

void printmatrix()
{
    for(int i=0;i<maxlen;i++)
    {
        cout << "Row " << i << " : ";
        for(int j=0;j<maxlen-1;j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int T, n;
    cin >> T;
    computeMatrix();
    for(int z=1;z<=T;z++)
    {
        cin >> n;
        cout << "Case #" << z << ": " << table[n];
        if (z!=T) cout << endl;
    }
    return 0;
}
