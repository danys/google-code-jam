#include <iostream>
#include <string>

using namespace std;

int isTidy(string s){
	int lastChar, nextChar;
	lastChar = -1;
	for(int i=0;i<s.length();i++){
		nextChar = s[i]-'0';
		if (nextChar<lastChar) return i;
		lastChar = nextChar;
	}
	return -1;
}

string solve(string s){
	if (s.length()==1) return s;
	int index = isTidy(s);
	if (index==-1) return s;
	int curChar, nextChar;
	while(index!=-1){
		curChar = s[index-1]-'0';
		curChar--;
		s[index-1]=(char)curChar+'0';
		for (int i=index;i<s.length();i++) s[i]='9';
		index = isTidy(s);
	}
	if (s[0]=='0') s = s.substr(1);
	return s;
}

int main(){
	int T;
	cin >> T;
	string s;
	for(int z=1;z<=T;z++){
		cin >> s;
		cout << "Case #" << z << ": " << solve(s) << endl;
	}
}