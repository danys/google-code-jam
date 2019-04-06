#include <iostream>
#include <unordered_map>

using namespace std;

long long y, z;

unordered_map<long long, long long> map;

long long findIndex(long long best){
	if (map[best]>0) return best;
	if (best%2==0){
		if (map[(best/2)-1]>0) return (best/2)-1;
		if (map[(best/2)]>0) return best/2;
	} else if (map[(best-1)/2]) return (best-1)/2;
	return -1;
}

void solve(long long N, long long K){
	map.clear();
	long long index=N;
	map[index]=1;
	for(long long i=0;i<K;i++){
		index = findIndex(index);
		map[index]--;
		if (index%2==0){
			map[(index/2)-1]++;
			map[index/2]++;
			z=(index/2)-1;
			y=index/2;
		} else {
			map[(index-1)/2] = map[(index-1)/2]+2;
			y=(index-1)/2;
			z=(index-1)/2;
		}
	}
}

int main(){
	int T;
	long long N, K;
	cin >> T;
	for(int c=1;c<=T;c++){
		cin >> N >> K;
		solve(N,K);
		cout << "Case #" << c << ": " << y << " " << z << endl;
	}
}