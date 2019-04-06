#include <iostream>
#include <vector>

#define maxlen 25

using namespace std;

int combination[maxlen];
vector<int> v;

int power2(int n)
{
    if (n<=0) return 1;
    return 2*power2(n-1);
}

void convert(int x,int n)
{
    for(int i=0;i<maxlen;i++) combination[i]=0;
    int counter=0;
    while(x>0)
    {
        if (x%2==0) combination[counter]=0;
        else combination[counter]=1;
        counter++;
        x=x/2;
    }
    counter=0;
    v.clear();
    while(counter<maxlen-2)
    {
        if (combination[counter]==1) v.push_back(counter+2);
        counter++;
    }
    v.push_back(n);
}

int indexof(int x)
{
    for(unsigned int i=0;i<v.size();i++) if (v[i]==x) return i+1;
    return -1;
}

bool ispure(int n)
{
    int index;
    while(true)
    {
        index = indexof(n);
        n = index;
        if (index==-1) return false;
        else if (index==1) return true;
    }
}

int solve(int n)
{
    int len = n-2;
    int result = 0;
    for(int i=0;i<power2(len);i++)
    {
        convert(i,n);
        if (ispure(n)) result = (result+1)%100003;
    }
    return result;
}

int main()
{
    int T, n;
    cin >> T;
    for(int z=1;z<=T;z++)
    {
        cin >> n;
        cout << "Case #" << z << ": " << solve(n);
        if (z!=T) cout << endl;
    }
    return 0;
}
