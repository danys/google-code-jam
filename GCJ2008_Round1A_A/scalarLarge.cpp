#include <iostream>
#include <algorithm>

#define maxvectlen 800

using namespace std;

long long vect1[maxvectlen];
long long vect2[maxvectlen];
int origin;

//Computes the lowest scalar product
long long compute(int dims)
{
    long long res=0;
    if (origin==0)
    {
        for(int i=0;i<dims;i++) res += vect2[i]*vect1[dims-1-i];
        return res;
    }
    else if (origin>0)
    {
        for(int i=0;i<origin;i++) res += vect1[i]*vect2[dims-1-i];
        for(int i=dims-1;i>=origin;i--) res += vect1[i]*vect2[dims-1-i];
        return res;
    }
    else //origin = dims
    {
        for(int i=0;i<dims;i++) res += vect1[i]*vect2[dims-1-i];
        return res;
    }
}

int findOrigin(long long vect[], int dim)
{
    int i=0;
    while((i<dim) && (vect[i]<0)) i++;
    return i;
}

int main()
{
    int cases, dims, c;
    cin >> cases;
    for(int z=1;z<=cases;z++)
    {
        cin >> dims;
        for(c=1;c<=dims;c++) cin >> vect1[c-1];
        for(c=1;c<=dims;c++) cin >> vect2[c-1];
        sort(vect1,vect1+dims);
        sort(vect2,vect2+dims);
        origin=findOrigin(vect1,dims);
        cout << "Case #" << z << ": " << compute(dims) << endl;
    }
    return 0;
}