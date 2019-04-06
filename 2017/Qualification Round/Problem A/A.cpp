#include <iostream>
#include <string>

using namespace std;

bool isDone(string s, bool minus){
	for(int i=0;i<s.length();i++) {
		if ((!minus) && (s[i]!='+')) return false;
		else if ((minus) && (s[i]!='-')) return false;
	}
	return true;
}

int searchMove(string s, int K){
	for(int i=0;i<s.length();i++){
		if (s[i]=='-'){
			if (i+K-1>=s.length()) return s.length()-K;
			else return i;
		}
	}
	return -1;
}

int flip(string &s, int pos, int n){
	for(int i=pos;i<pos+n;i++){
		if (s[i]=='-') s[i]='+';
		else s[i]='-';
	}
}

int solve(string S, int K){
	if (isDone(S,false)) return 0;
	int len = S.length();
	if (len==K){
		if (isDone(S,true)) return 1;
		else return -1;
	}
	int maxMovesN = len-K+1;
	int movesCount = 0;
	int index;
	while(movesCount<=maxMovesN){
		if (isDone(S,false)) return movesCount;
		index = searchMove(S,K);
		flip(S,index,K);
		movesCount++;
	}	
	return -1;
}

int main(){
	int T, K, res;
	cin >> T;
	string s;
	for(int z=1;z<=T;z++){
		cin >> s >> K;
		res = solve(s,K);
		if (res==-1) cout << "Case #" << z << ": IMPOSSIBLE" << endl;
		else cout << "Case #" << z << ": " << res << endl;
	}
}