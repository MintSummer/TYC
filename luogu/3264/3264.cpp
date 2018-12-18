#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=1010;
	const int M=3010;
	const int MX=1<<10|5;
	const int inf=0x3f3f3f3f;

	int n,m,k,num[15],bin[15],Head[N],dp[N][MX],vis[N];
	queue<int> q;
	pa pos[15];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct edge
	{
		int to,next,w;
	}E[M<<1];

	inline void add(const int &u,const int &v,const int &w)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}
	
	void spfa(int state)
	{
		while(!q.empty())
		{
			int u=q.front();q.pop();
			vis[u]=true;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(dp[v][state]>dp[u][state]+E[i].w)
				{
					dp[v][state]=dp[u][state]+E[i].w;
					if(!vis[v]) vis[v]=true,q.push(v);
				}
			}
		}
	}

	void Tree()
	{
		memset(dp,inf,sizeof(dp));
		for(int i=1;i<=k;i++) 
			dp[pos[i].first][bin[i]]=0;
		for(int s=1;s<bin[k+1];s++)
		{
			for(int i=1;i<=n;i++)
			{
				for(int sub=s&(s-1);sub;sub=s&(sub-1))
					dp[i][s]=min(dp[i][s],dp[i][sub]+dp[i][s^sub]);
				if(dp[i][s]!=inf) vis[i]=true,q.push(i);
			}
			spfa(s);
		}
	}

	bool check(int s)
	{
		static int cnt[15];
		for(int i=1;i<=k;i++)
			if(s&bin[i]) cnt[pos[i].first]++;
		for(int i=1;i<=10;i++)
			if(cnt[i]&&cnt[i]!=num[i]) return false;
		return true;
	}

	void work()
	{
		n=read(),m=read(),k=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w),add(v,u,w);
		}
		for(int i=1;i<=k;i++)
		{
			pos[i]=pa(read(),read());
			num[pos[i].first]++;
		}
		bin[1]=1;
		for(int i=2;i<=k+1;i++) bin[i]=bin[i-1]<<1;
		Tree();
		static int ans[MX],flag[MX];
		memset(ans,inf,sizeof(ans));
		for(int i=1;i<bin[k+1];i++)
			for(int j=1;j<=n;j++)
				ans[i]=min(ans[i],dp[j][i]);
		for(int i=1;i<bin[k+1];i++) flag[i]=check(i);
		for(int s=1;s<bin[k+1];s++) if(flag[s])
			for(int sub=s&(s-1);sub;sub=s&(sub-1)) if(flag[sub])
				ans[s]=min(ans[s],ans[sub]+ans[sub^s]);
		printf("%d\n",ans[bin[k+1]-1]);

	}
}

int main()
{
	freopen("a.in","r",stdin);
	TYC::work();
	return 0;
}
