#include<iostream>
#include<map>
#include<string>
using namespace std;
map <char,char> m;
int main(void)
{
	string s;
	for(int i=0;i<26;i++)
	{
		char a;
		cin>>a;
		m.insert(make_pair(i+'a',a));
		m.insert(make_pair(i+'A',a-'a'+'A'));
	}
	cin.get();
	m.insert(make_pair(' ',' '));
	getline(cin,s);
	for(int i=0;i<s.size();i++)
		cout<<m[s[i]];
	return 0;
}

