#include <iostream>
#include <algorithm>

#define maxl 1000

using namespace std;

int B,N;

long long barber[maxl];

long long nc(long long b,long long time)
{
    long long res = 1;
    for(int i=0;i<B;i++) res += (time%barber[i]==0) ? time/barber[i] : (time/barber[i])+1;
    for(int i=0;i<b;i++) if (time%barber[i]==0) res += 1;
    return res;
}

//Find the minimum in the array
long long mini()
{
    long long res = barber[0];
    for(int i=0;i<B;i++) if (barber[i]<res) res = barber[i];
    return res;
}

//Binary search solution
int solve()
{
    long long maxt = mini();
    maxt = ((long long)N-1)*maxt;
    long long mint = 0;
    long long middlet;
    long long ncust,ncustn;
    long long index=0;
    while(true)
    {
        middlet = (long long)(((mint+maxt)/2L)/barber[index])*barber[index];
        ncust = nc(index,middlet);
        ncustn = nc(index,middlet+barber[index]);
        if (ncust==N) return index+1;
        else if (ncustn==N) return index+1;
        else if (mint==maxt) {index++;continue;}
        else if (ncust>N)
        {
            if (nc(index,middlet-barber[index])==N) return index+1;
            maxt = middlet;
        }
        else if ((ncust<N) && (ncustn>N))
        {
            mint = middlet;
            maxt = mint+barber[index];
            index++;
            if ((nc(index,middlet)==N) && (middlet%barber[index]==0))   return index+1;
        }
        else if ((ncust<N) && (ncustn<N))
        {
            if (nc(index,middlet+barber[index]+barber[index])==N) return index+1;
            if (nc(index,middlet+barber[index]+barber[index])>N)
            {
                mint = middlet+barber[index];
                index++;
            }
            else
            {
                mint = middlet+barber[index]+barber[index];
            }
        }
    }
    return -1;
}

int main()
{
    int T;
    cin >> T;
    for(int z=1;z<=T;z++)
    {
        cin >> B >> N;
        for(int i=1;i<=B;i++) cin >> barber[i-1];
        cout << "Case #" << z << ": " << solve() << endl;
    }
    return 0;
}
