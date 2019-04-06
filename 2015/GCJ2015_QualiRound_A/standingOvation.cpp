#include <iostream>
#include <string>

#define max 1001

using namespace std;

int smax;

int solve(string str)
{
    int s,res,total;
    res=0;
    total=0;
    for(int i=0;i<=smax;i++)
    {
        s = str[i]-'0';
        if (total>=i) total += s;
        else
        {
            res += i-total;
            total += s + i - total;
        }
    }
    return res;
}

int main()
{
    int T;
    string s;
    cin >> T;
    for(int z=1;z<=T;z++)
    {
        cin >> smax;
        cin >> s;
        cout << "Case #" << z << ": " << solve(s);
        if (z!=T) cout << endl;
    }
    return 0;
}
