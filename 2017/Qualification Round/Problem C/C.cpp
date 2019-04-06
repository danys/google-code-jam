#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>

#define maxStalls 1000002

using namespace std;

int y, z;
bool stalls[maxStalls];
int minStallNum[maxStalls];
int maxStallNum[maxStalls];
vector<int> minStallTable[maxStalls];
vector<int> maxStallTable[maxStalls];

void solve(int N, int K){
	for(int i=0;i<maxStalls;i++) stalls[i]=false;
	stalls[0]=true;
	stalls[N+1]=true;
	int ls, rs, start;
	bool exit=false;
	for(int i=0;i<K;i++){
		memset(minStallNum, 0, sizeof(int)*(N+2));
		memset(maxStallNum, 0, sizeof(int)*(N+2));
		for(int j=0;j<=N;j++) minStallTable[j].clear();
		for(int j=1;j<N+1;j++){
			if (stalls[j]) continue;
			ls=0;
			start=j-1;
			while(start>=0 && !stalls[start]) {
				ls++;
				start--;
			}
			rs=0;
			start=j+1;
			while(start<N+2 && !stalls[start]) {
				rs++;
				start++;
			}
			minStallNum[j]=min(ls,rs);
			maxStallNum[j]=max(ls,rs);
			minStallTable[min(ls,rs)].push_back(j);
		}
		exit=false;
		for(int j=N;j>=0 && !exit;j--){
			if (minStallTable[j].size()>0){
				exit=true;
				if (minStallTable[j].size()==1){
					stalls[minStallTable[j][0]]=true;
					y = maxStallNum[minStallTable[j][0]];
					z = minStallNum[minStallTable[j][0]];
					exit=true;
				}
				else{
					for(int a=0;a<=N;a++) maxStallTable[a].clear();
					for(int a=0;a<minStallTable[j].size();a++){
						maxStallTable[maxStallNum[minStallTable[j][a]]].push_back(minStallTable[j][a]);
					}
					for(int a=N;a>=0;a--){
						if (maxStallTable[a].size()>0){
							if (maxStallTable[a].size()==1) {stalls[maxStallTable[a][0]]=true;
								y = maxStallNum[maxStallTable[a][0]];
								z = minStallNum[maxStallTable[a][0]];
							}
							else{
								sort(maxStallTable[a].begin(), maxStallTable[a].end());
								stalls[maxStallTable[a][0]]=true;
								y = maxStallNum[maxStallTable[a][0]];
								z = minStallNum[maxStallTable[a][0]];
							}
							break;
						}
					}
				}
			}
		}
	}
}


int main(){
	int T;
	int N, K;
	cin >> T;
	for(int CC=1;CC<=T;CC++){
		cin >> N >> K;
		solve(N,K);
		cout << "Case #" << CC << ": " << y << " " << z << endl;
	}
}