#include<bits/stdc++.h>
using namespace std;

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

int n;
struct node
{
	int b,j;
	bool operator < (const node &a) const
	{
		return j>a.j;
	}
}task[1010];

int main()
{
	int cas=0;
	while(1)
	{
		n=read();cas++;
		if(n==0) break;
		for(int i=1;i<=n;i++)
			task[i].b=read(),task[i].j=read();
		sort(task+1,task+1+n);
		int ans=0,sum=0;
		for(int i=1;i<=n;i++)
		{
			sum+=task[i].b;
			ans=max(ans,sum+task[i].j);
		}
		printf("Case %d: %d\n",cas,ans);
	}
	return 0;
}
