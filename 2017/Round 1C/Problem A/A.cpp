#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <string>
#include <math.h>
#define pi 3.141592653589793238462643383279502884L
#define maxl 1000

using namespace std;

long long r[maxl];
long long h[maxl];
bool selected[maxl];
vector<int> sel;

long double solve(int n, int k){
	long double result=0.0L;
	string binary;
	int ones;
	int maxCount = pow(2,n);
	for(int counter=0;counter<maxCount;counter++){
		sel.clear();
		binary = bitset<maxl>(counter).to_string();
		binary = binary.substr(maxl-n);
		ones=0;
		for(int i=0;i<binary.size();i++){
			if (binary[i]=='1') ones++;
			selected[i]=false;
		}
		if (ones!=k) continue;
		int maxi;
		for(int i=0;i<k;i++){
			maxi=-1;
			for(int j=0;j<n;j++){
				if ((binary[j]!='1') || (selected[j])) continue;
				if (maxi==-1) maxi=j;
				else if (r[j]>=r[maxi]){
					maxi=j;
				}
			}
			selected[maxi]=true;
			sel.push_back(maxi);
		}
		long long res=0;
		int index;
		for(int i=0;i<k;i++){
			index=sel[i];
			res+=2*r[index]*h[index];
			if (i!=k-1) {
				res+= (r[index]*r[index])-(r[sel[i+1]]*r[sel[i+1]]);
			}
			else res+= r[index]*r[index];
		}
		long double newRes = pi*(long double)(res);
		if (newRes>result) result=newRes;
	}
	return result;
}

int main(){
	int T, K, N;
	long long R, H;
	cin >> T;
	for(int z=1;z<=T;z++){
		cin >> N >> K;
		for(int i=0;i<N;i++){
			cin >> R >> H;
			r[i] = R;
			h[i] = H;
		}
		cout << "Case #" << z << ": " << setprecision(30) << solve(N, K) << endl;
	}
}
