#include <iostream>
#include <string>

using namespace std;

int a[10];

unsigned long long solve(unsigned long long N)
{
	if (N==0) return -1;
	for(int i=0;i<10;i++) a[i]=false;
	bool finish=false;
	string numstr;
	unsigned long long number=N;
	int it=0;
	while(!finish)
	{
		if (N>=10000000000) return -1;
		numstr = to_string(number);
		for(int i=0;i<numstr.size();i++) a[numstr[i]-'0']=true;
		finish=true;
		for(int i=0;i<10;i++) if (!a[i]) finish=false;
		if (!finish) number += N;
		it++;
		if (it>90) return -1;
	}
	return number;
}

int main()
{
	int T, N;
	cin >> T;
	for(int z=0;z<T;z++)
	{
		cin >> N;
		unsigned long long res = solve(N);
		cout << "Case #" << z+1 << ": " ;
		if (res==-1) cout << "INSOMNIA" << endl;
		else cout << res << endl;
	}
}