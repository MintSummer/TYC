#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
	const int N=1e6+10;
	string str;
	int tag[N];
	
	void work()
	{
		ios::sync_with_stdio(false);
		cin>>str;
		int n=str.size();
		int cnt=0,ans=0,num=0;
		for(int i=0;i<n;i++)
			if(!i||str[i]!=str[i-1]) tag[++cnt]=1;
			else tag[cnt]=0;
		if(str[0]==str[n-1]) tag[1]=0,cnt--;
		for(int i=1;i<=cnt;i++)
		{
			if(tag[i]) ++num;
			else ans+=(num>>1)+1,num=0;
		}
		printf("%d\n",ans+(num>>1));
	}
}

int main()
{
	TYC::work();
	return 0;
}
