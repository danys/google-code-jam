#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int n,l;
string init[150];
string temp[150];
string output[150];
bool outputtable[150];
string candid[22500];

void inittable()
{
    for(int i=0;i<150;i++)
    {
        outputtable[i]=false;
    }
}

string getmask(long long n,int length)
{
    string result = "";
    for(int i=0;i<length;i++) result.append("0");
    for(int i=1;i<=length;i++)
    {
     if (n%2==1) result[length-i]='1';
        n=n/2;
    }
    return result;
}

/*long long power2(long long l)
{
    long long result = 1;
    if (l==0) return 1;
    for(int i=1;i<=l;i++)
        result=result*2;
    return result;
}*/

void inittemp(int items)
{
    for(int i=0;i<items;i++)
    {
        temp[i]=init[i];
    }
}

void initoutput(int length)
{
    for(int i=0;i<length;i++)
    {
        outputtable[i]=true;
    }
}

/*int nflipbits(string str1,string str2, int length)
{
    int result=0;
    for(int i=0;i<length;i++)
    {
        if (!(((str1[i]=='1') && (str2[i]=='1')) || ((str1[i]=='0') && (str2[i]=='0'))))
        {
            result++;
        }
    }
    return result;
}*/

string genbitmask(string str1,string str2, int length)
{
    string result = "";
    for(int i=0;i<length;i++) result.append("0");
    for(int i=0;i<length;i++)
    {
        if (!(((str1[i]=='1') && (str2[i]=='1')) || ((str1[i]=='0') && (str2[i]=='0'))))
        {
            result[i] = '1';
        }
    }
    return result;
}

int numberones(string s,int length)
{
    int result=0;
    for(int i=0;i<length;i++)
    {
     if (s[i]=='1') result++;
    }
    return result;
}

void gencandid(int length) //n
{
    string temp;
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<length;j++)
        {
            candid[i]=genbitmask(init[i],output[j],l);
        }
    }
}

int main()
{
    string line;
    getline(cin,line);
    stringstream firstline(line);
    int numbertestcases;
    firstline >> numbertestcases;
    int nones;
    int bestnones;
    string mask;
    string candidate;
    int counter;
    for(int z=1;z<=numbertestcases;z++)
    {
        getline(cin,line);
        stringstream testline(line);
        testline >> n;
        testline >> l;
        bestnones = l+1;
        getline(cin,line);
        stringstream caseline(line);
        for(int y=0;y<n;y++) caseline >> init[y];
        getline(cin,line);
        stringstream case2line(line);
        for(int y=0;y<n;y++) case2line >> output[y];
        gencandid(n);
        int i=0;
        while(i<n*n)
        {
            candidate = candid[i];
            //get number of 1s
            nones = numberones(candidate,l);
            if (nones<bestnones)
            {
                //get mask
                mask = candidate;
                //initialize temp
                inittemp(n);
                //loop for 1 to L in mask
                for(int j=0;j<l;j++)
                {
                    if (mask[j]=='1')
                    {
                        for(int k=0;k<n;k++)
                        {
                            if (temp[k][j]=='1') temp[k][j]='0';
                            else temp[k][j]='1';
                        }
                    }
                }
                //check if solution
                initoutput(n);
                //loop for 1 to N in temp
                for(int j=0;j<n;j++)
                {
                    //look for temp[j] in output
                    for(int k=0;k<n;k++)
                    {
                        if ((output[k].compare(temp[j])==0) && (outputtable[k]==true))
                        {
                           outputtable[k]=false;
                           break;
                        }
                    }
                }
                counter=0;
                for(int j=0;j<n;j++)
                {
                    if (outputtable[j]==false) counter++;
                }
                if (counter==n) //we have a solution
                {
                    bestnones=nones;
                }
            }
            i++;
        }
        if (bestnones==l+1) cout << "Case #" << z << ": " << "NOT POSSIBLE" << endl;
        else cout << "Case #" << z << ": " << bestnones << endl;
    }
    return 0;
}
