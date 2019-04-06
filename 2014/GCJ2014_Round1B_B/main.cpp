#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

string A,B,K;

string binary(int x,unsigned int len)
{
    string res="";
    while(x>0)
    {
        if (x%2==0) res.insert(0,"0");
        else res.insert(0,"1");
        x=x/2;
    }
    if (len>res.length())
    {
        unsigned int c=len-res.length();
        for(unsigned int i=1;i<=c;i++) res.insert(0,"0");
    }
    return res;
}

long long memo[30][2][2][2];

long long solve(int p,bool aismax,bool bismax, bool kismax)
{
    if (p==30) return aismax || bismax || kismax ? 0 : 1;
    long long & result = memo[p][aismax][bismax][kismax];
    if (result!=-1) return result;
    int k;
    result=0;
    for(int a=0;a<2;a++)
    {
        //skip combinations where we try a 1 at a position that contains a 0
        //A[p] cannot assume the value 1 since we are at the maximum value already: aismax==true
        if (a==1 && A[p]=='0' && aismax) continue; //means that we have a 0 in A
        for(int b=0;b<2;b++)
        {
            //same comment as far A above
            if (b==1 && B[p]=='0' && bismax) continue;
            k = a & b;
            //same comment as far A above
            if (k==1 && K[p]=='0' && kismax) continue;
            //set the bool argument values such that we know if the maxvalue is being submitted
            result += solve(p+1,aismax && a == A[p]-'0',bismax && b == B[p]-'0',kismax && k == K[p]-'0');
        }
    }

    return result;
}

int main()
{
    string line;
    getline(cin,line);
    stringstream firstline(line);
    int numbertestcases, a, b, k;
    firstline >> numbertestcases;
    for(int z=1;z<=numbertestcases;z++)
    {
        getline(cin,line);
        stringstream caseline(line);
        caseline >> a >> b >> k;
        A = binary(a,30);
        B = binary(b,30);
        K = binary(k,30);
        memset(memo, -1, sizeof(memo));
        cout << "Case #" << z << ": " << solve(0,true,true,true) << endl;
    }
    return 0;
}
