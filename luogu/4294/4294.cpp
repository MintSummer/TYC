#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=13;
	const int M=N*N;
	const int MX=1<<10|5;
	const int inf=0x3f3f3f3f;
	const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

	int n,m,k,bin[N],val[M],num[N][N],dp[M][MX];
	bool vis[M],mark[M];
	pa from[M][MX];
	queue<int> q;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline pa Position(int x)
	{
		return make_pair(x/m,x%m);
	}

	void spfa(int state)
	{
		while(!q.empty())
		{
			int u=q.front();q.pop();
			pa pos=Position(u);
			vis[u]=false;
			for(int i=0;i<4;i++)
			{
				int nx=pos.first+dx[i],ny=pos.second+dy[i];
				if(nx<0||nx>=n||ny<0||ny>=m) continue;
				int v=num[nx][ny];
				if(dp[u][state]+val[v]<dp[v][state])
				{
					dp[v][state]=dp[u][state]+val[v];
					from[v][state]=pa(u,state);	
					if(!vis[v]) 
						vis[v]=true,q.push(v);

				}
			}
		}
	}

	void dfs(int root,int state)
	{
		mark[root]=true;
		int node=from[root][state].first,s=from[root][state].second;
		if(!s) return;
		if(node==root) 
			dfs(root,s),dfs(root,s^state);
		else 
			dfs(node,s);
	}

	void work()
	{
		n=read(),m=read();
		bin[1]=1;
		for(int i=2;i<=11;i++) bin[i]=bin[i-1]<<1;
		memset(dp,inf,sizeof(dp));
		int k=0,tot=0,root;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				num[i][j]=tot;
				val[tot]=read();
				if(!val[tot]) 
					dp[tot][bin[++k]]=0,root=tot;
				tot++;
			}
		for(int s=1;s<bin[k+1];s++)
		{
			for(int i=0;i<tot;i++)
			{
				for(int sub=s&(s-1);sub;sub=s&(sub-1))
					if(dp[i][s]>dp[i][sub]+dp[i][s^sub]-val[i])
					{
						dp[i][s]=dp[i][sub]+dp[i][s^sub]-val[i];
						from[i][s]=pa(i,sub);
					}
				if(!vis[i]&&dp[i][s]<inf)
					vis[i]=true,q.push(i);
			}
			spfa(s);
		}
		printf("%d\n",dp[root][bin[k+1]-1]);
		dfs(root,bin[k+1]-1);
		for(int i=0,t=n*m;i<t;i++)
		{
			if(!val[i]) putchar('x');
			else if(!mark[i]) putchar('_');
			else putchar('o');
			if((i+1)%m==0) putchar('\n');
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
