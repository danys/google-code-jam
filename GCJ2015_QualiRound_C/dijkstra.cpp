#include <iostream>
#include <string>

using namespace std;

long long L,X;

string superstring;

void expand(string s)
{
    superstring = s;
}

char compute(char x, char y)
{
    if ((x=='1') && (y=='1')) return '1';
    if ((x=='1') && (y=='i')) return 'i';
    if ((x=='1') && (y=='j')) return 'j';
    if ((x=='1') && (y=='k')) return 'k';
    if ((x=='i') && (y=='1')) return 'i';
    if ((x=='i') && (y=='i')) return '0'; //-1
    if ((x=='i') && (y=='j')) return 'k';
    if ((x=='i') && (y=='k')) return 'J'; //-j
    if ((x=='j') && (y=='1')) return 'j';
    if ((x=='j') && (y=='i')) return 'K'; //-k
    if ((x=='j') && (y=='j')) return '0'; //-1
    if ((x=='j') && (y=='k')) return 'i';
    if ((x=='k') && (y=='1')) return 'k';
    if ((x=='k') && (y=='i')) return 'j';
    if ((x=='k') && (y=='j')) return 'I'; //-i
    if ((x=='k') && (y=='k')) return '0'; //-1
    return 'x';
}

bool computesign(bool x, bool y)
{
    if ((x) && (y)) return true;
    else if ((x) && (!y)) return false;
    else if ((!x) && (y)) return false;
    else if ((!x) && (!y)) return true;
    return false;
}

bool check(long long i, long long j, char c, bool b)
{
    char t='1';
    bool sign = b;
    bool csign;
    for(long long k=i;k<=j;k++)
    {
        t = compute(t,superstring[k%L]);
        csign=true;
        if (t=='0')
        {
            t = '1';
            csign = false;
        }
        else if (t=='I')
        {
            t = 'i';
            csign = false;
        }
        else if (t=='J')
        {
            t = 'j';
            csign = false;
        }
        else if (t=='K')
        {
            t = 'k';
            csign = false;
        }
        sign = computesign(sign,csign);
    }
    if ((t==c) && (!sign)) return true;
    return false;
}

int index(long long start, long long last, char c)
{
    long long i=start;
    char t='1';
    bool b = true,csign;
    while(i<=L*X-1)
    {
        t = compute(t,superstring[i%L]);
        csign=true;
        if (t=='0')
        {
            t = '1';
            csign = false;
        }
        else if (t=='I')
        {
            t = 'i';
            csign = false;
        }
        else if (t=='J')
        {
            t = 'j';
            csign = false;
        }
        else if (t=='K')
        {
            t = 'k';
            csign = false;
        }
        b = computesign(b,csign);
        if ((i>last) && (t==c) && (b)) return i;
        i++;
    }
    return -1;
}

bool solve()
{
    if (L*X<3) return false;
    if (!check(0,L*X-1,'1',true)) return false;
    long long indi,indj,indk,lindi,lindj,lindk;
    indi=-1;indj=-1;indk=-1;
    while(true)
    {
        indi=index(0,indi,'i');
        if (indi!=-1)
        {
            indj=index(indi+1,indj,'j');
            if (indj!=-1)
            {
                indk=index(indj+1,indk,'k');
                if (indk!=-1) return true;
            }
        }
        else return false;
    }
}

int main()
{
    int T;
    cin >> T;
    string s;
    for(int z=1;z<=T;z++)
    {
        cin >> L >> X;
        cin >> s;
        expand(s);
        if (solve()) cout << "Case #" << z << ": " << "YES" << endl;
        else cout << "Case #" << z << ": " << "NO" << endl;
    }
    return 0;
}
