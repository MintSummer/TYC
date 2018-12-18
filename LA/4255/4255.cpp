#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=15;
	int T,n,G[15][15],de[15],sum[15],q[15];
	char ch[110];

	void init()
	{
		memset(de,0,sizeof(de));
		memset(G,0,sizeof(G));
		memset(sum,0,sizeof(sum));
	}

	void search()
	{
		int now=-10,h=1,t=0;
		for(int i=0;i<=n;i++)
			if(!de[i]) 
				sum[i]=-10,q[++t]=i;
		while(h<=t)
		{
			now++;
			int u=q[h++];
			for(int v=0;v<=n;v++)
				if(G[u][v])
				{
					de[v]--;
					if(!de[v]) sum[v]=now,q[++t]=v;
				}
		}
	}

	void work()
	{
		scanf("%d",&T);
		while(T--)
		{
			init();
			scanf("%d%s",&n,ch);
			int now=0;
			for(int i=1;i<=n;i++)
				for(int j=i;j<=n;j++)
				{
					if(ch[now]=='+')
						de[j]++,G[i-1][j]=1;
					else if(ch[now]=='-')
						de[i-1]++,G[j][i-1]=1;
					now++;
				}
			search();
			for(int i=1;i<=n;i++)
				printf("%d ",sum[i]-sum[i-1]);
			printf("\n");
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
