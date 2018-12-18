#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
bool out[26][300];
string s;
int letter[26],maxx;
int main(void)
{
	for(int a=0;a<4;a++)
	{
		getline(cin,s);
		for(int i=0;i<s.size();i++)
			if('A'<=s[i]&&s[i]<='Z')
				letter[s[i]-'A']++;
	}
	for(int i=0;i<26;i++)
	{
		int j;
		for(j=0;j<letter[i];j++)
			out[i][j]=true;
		if(maxx<j)maxx=j;
	}
	while(maxx--)
	{
		for(int i=0;i<25;i++)
			if(out[i][maxx])cout<<"*"<<" ";
			else cout<<"  ";
		if(out[25][maxx])cout<<"*";
		cout<<endl;
	}
	cout<<"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";
	return 0;
} 
