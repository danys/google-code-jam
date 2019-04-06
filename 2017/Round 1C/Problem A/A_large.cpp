#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#define pi 3.141592653589793238462643383279502884L

using namespace std;

struct pancake{
	long long radius;
	long long height;
};

vector<pancake> pancakes;

struct radiusSort
{
    inline bool operator() (const pancake& pc1, const pancake& pc2)
    {
        return (pc1.radius < pc2.radius);
    }
};

double solve(int n, int k){
	sort(pancakes.begin(), pancakes.end(), radiusSort());
	long long res = 0;
	vector<long long> shells;
	long long shell;
	long long curSum;
	for(int i=0;i<n;i++){
		shell = 2*pancakes[i].radius*pancakes[i].height;
		if (i>=k-2){
			sort(shells.begin(), shells.end()); //sort at least K-1 shells
			//Sum up pancakes with top K-1 top surface. Include current pancake top surface and shell
			curSum = shell;
			for(int j=shells.size()-1;j>=shells.size()-k+1 && j>=0;j--) curSum += shells[j];
			res = max(res,curSum+pancakes[i].radius*pancakes[i].radius);
		}
		shells.push_back(shell);
	}
	return pi*(double)res;
}

int main(){
	int T, K, N;
	long long R, H;
	cin >> T;
	for(int z=1;z<=T;z++){
		cin >> N >> K;
		pancakes.clear();
		for(int i=0;i<N;i++){
			cin >> R >> H;
			pancake p;
			p.radius = R;
			p.height = H;
			pancakes.push_back(p);
		}
		cout << "Case #" << z << ": " << fixed << setprecision(8) << solve(N, K) << endl;
	}
}
