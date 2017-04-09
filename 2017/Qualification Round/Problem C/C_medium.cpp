#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>

#define maxl 1000001

using namespace std;

int y, z;

int table[maxl];

int findIndex(int best){
	for(int i=best;i>=1;i--){
		if (table[i]>0) return i;
	}
	return -1;
}

void solve(int N, int K){
	for(int i=1;i<=N;i++) table[i] = 0;
	int index=N;
	table[index]=1;
	for(int i=0;i<K;i++){
		index = findIndex(index);
		table[index]--;
		if (index%2==0){
			table[(index/2)-1]++;
			table[index/2]++;
			z=(index/2)-1;
			y=index/2;
		} else {
			table[(index-1)/2] = table[(index-1)/2]+2;
			y=(index-1)/2;
			z=(index-1)/2;
		}
	}
}

int main(){
	int T;
	int N, K;
	cin >> T;
	for(int c=1;c<=T;c++){
		cin >> N >> K;
		solve(N,K);
		cout << "Case #" << c << ": " << y << " " << z << endl;
	}
}