#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

vector<int> P;

int solve()
{
    int maxval=0,besttime,time;
    for(unsigned int i=0;i<P.size();i++) if (P[i]>maxval) maxval = P[i];
    besttime = maxval;
    for(int i=1;i<maxval;i++)
    {
        time=0;
        for(unsigned int j=0;j<P.size();j++) if (P[j]>i) time += ceil((double)P[j]/(double)i)-1;
        if (time+i<besttime) besttime = time+i;
    }
    return besttime;
}

int main()
{
    int T,temp,D;
    cin >> T;
    for(int z=1;z<=T;z++)
    {
       cin >> D;
       P.clear();
       for(int i=0;i<D;i++)
       {
           cin >> temp;
           P.push_back(temp);
       }
       cout << "Case #" << z << ": " << solve();
       if (z!=T) cout << endl;
    }
    return 0;
}
