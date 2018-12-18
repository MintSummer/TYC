#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1000010; 
	char ch[N];
	int len,nxt[N];

	void work()
	{
		scanf("%d%s",&len,ch);
		nxt[0]=nxt[1]=0;
		for(int i=1;i<len;i++)
		{
			int tmp=nxt[i];
			while(tmp&&ch[tmp]!=ch[i]) tmp=nxt[tmp];
			nxt[i+1]=(ch[tmp]==ch[i]?tmp+1:0);
		}
		printf("%d\n",len-nxt[len]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
