#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>

using namespace std;

const int maxstringlength = 100; //which is also the maximum number of buckets
const int maxnumber = 100;

string str[maxstringlength];
string compactstr[maxstringlength];

int letterbucket[maxnumber][maxstringlength];

void compact(int n)
{
    string s;
    unsigned int j;
    string t,t2;
    string result;
    for(int i=0;i<n;i++)
    {
      s=str[i];
      j=0;
      t = s[0];
      t2 = s[0];
      result = "";
      while(j<s.length())
      {
          while((t2.compare(t)==0) && (j<s.length()))
          {
              j++;
              t2=s[j];
          }
          result.append(t);
          t=s[j];
      }
      compactstr[i]=result;
    }
}

bool ispossible(int n)
{
    int counter=0;
    string s0 = compactstr[0];
    for(int i=1;i<n;i++)
    {
        if (compactstr[i].compare(s0)==0) counter++;
    }
    if (counter==n-1) return true;
    else return false;
}

void buildbucket(int maxbuckets, int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<maxbuckets;j++) letterbucket[i][j]=0;
    }
    unsigned int j, nextindex, counter;
    char c;
    for(int i=0;i<n;i++)
    {
        nextindex=0;
        counter=0;
        while(nextindex<str[i].length())
        {
            j=nextindex;
            c=str[i][j];
            while(str[i][j]==c) j++;
            counter++;
            letterbucket[i][counter-1]=j-nextindex;
            nextindex=j;
        }
    }

}

int buildmin(int maxbuckets,int n)
{
    int mini,counter,moves;
    counter=0;
    for(int i=0;i<maxbuckets;i++)
    {
        mini=(int)1e9;
        for(int l=1;l<=maxstringlength;l++)
        {
            moves=0;
            for(int j=0;j<n;j++)
            {
                moves += abs(l-letterbucket[j][i]);
            }
            if (moves<mini) mini=moves;
        }
        counter += mini;
    }
    return counter;
}

int main()
{
    string line;
    getline(cin,line);
    stringstream firstline(line);
    int numbertestcases, n;
    firstline >> numbertestcases;
    string str1;
    for(int z=1;z<=numbertestcases;z++)
    {
        getline(cin,line);
        stringstream testline(line);
        testline >> n;
        for(int y=1;y<=n;y++)
        {
            getline(cin,line);
            stringstream stringline(line);
            stringline >> str[y-1];
        }
        //no moves needed?
        string s0 = str[0];
        int counter=0;
        for(int i=1;i<n;i++)
        {
            if (str[i].compare(s0)==0) counter++;
        }
        if (counter==n-1) cout << "Case #" << z << ": " << 0 << endl;
        else
        {
            compact(n);
            if (!ispossible(n)) cout << "Case #" << z << ": " << "Fegla Won" << endl;
            else
            {
                buildbucket(maxstringlength,n);
                cout << "Case #" << z << ": " << buildmin(compactstr[0].length(),n) << endl;
            }
        }
    }
    return 0;
}
