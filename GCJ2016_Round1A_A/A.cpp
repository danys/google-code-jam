#include <iostream>
#include <string>
#include <algorithm>

#define maxi 2000

using namespace std;

bool eliminated[maxi];
string input,result;
vector<int> num;

string convCharToStr(char val)
{
  string str;
  if (val=='Z') str = "ZERO";
  else if (val=='O') str = "ONE";
  else if (val=='W') str = "TWO";
else if (val=='T') str = "THREE";
else if (val=='U') str = "FOUR";
else if (val=='V') str = "FIVE";
else if (val=='X') str = "SIX";
else if (val=='S') str = "SEVEN";
else if (val=='G') str = "EIGHT";
else if (val=='N') str = "NINE";
  return str;
}

int convCharToInt(char val)
{
  int x;
  if (val=='Z') x = 0;
  else if (val=='O') x = 1;
  else if (val=='W') x = 2;
else if (val=='T') x = 3;
else if (val=='U') x = 4;
else if (val=='V') x = 5;
else if (val=='X') x = 6;
else if (val=='S') x = 7;
else if (val=='G') x = 8;
else if (val=='N') x = 9;
  return x;
}

int lookFor(char c)
{
 int count=0;
 bool found=false;
 for(int i=0;i<input.size();i++)
 {
   if ((input[i]==c) && (!eliminated[i]))
   {
     found=true;
     break;
   }
 }
 if (found)
 {
  string str = convCharToStr(c);
  for(int i=0;i<str.size();i++)
  {
    for(int j=0;j<input.size();j++)
    {
      if ((!eliminated[j]) && (input[j]==str[i])) {eliminated[j]=true;break;}
    }
  }
  int x = convCharToInt(c);
  num.push_back(x);
  return str.size();
 }
 else return 0;
}

string solve()
{
  result.clear();
  num.clear();
  int len = input.size();
  int cc=0,count;
  int curVal=0;
  string result;
  for(int i=0;i<maxi;i++) eliminated[i]=false;
  vector<char> v;
  v.push_back('U');
  v.push_back('Z');
  v.push_back('G');
  v.push_back('X');
  v.push_back('S');
  v.push_back('V');
  v.push_back('W');
  v.push_back('T');
  v.push_back('O');
  v.push_back('N');
  while(cc<len)
  {
    count=lookFor(v[curVal]);
    if (count==0) curVal++;
    else
    {
     cc += count;
    }
  }
  sort(num.begin(),num.end());
  for(int i=0;i<num.size();i++) result.push_back(num[i]+'0');
 return result;
}

int main()
{
   int T;
   cin >> T;
   for(int z=0;z<T;z++)
   {
      cin >> input;
      cout << "Case #" << z+1 << ": " << solve() << endl;
   }
}
