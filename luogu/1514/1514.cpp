#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int dx[5]={0,0,0,1,-1},dy[5]={0,1,-1,0,0};
	const int N=510,inf=0x3f3f3f3f;
	int n,m,cnt,G[N][N],vis[N][N],l[N][N],r[N][N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void dfs(int x,int y)
	{
		vis[x][y]=1;
		for(int i=1;i<=4;i++)
		{
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<1||xx>n||yy<1||yy>m||G[xx][yy]>=G[x][y]) continue;
			if(!vis[xx][yy]) dfs(xx,yy);
			l[x][y]=min(l[x][y],l[xx][yy]);
			r[x][y]=max(r[x][y],r[xx][yy]);
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				G[i][j]=read();
		memset(l,inf,sizeof(l));
		for(int i=1;i<=m;i++)
			l[n][i]=r[n][i]=i;
		for(int i=1;i<=m;i++) 
			if(!vis[1][i]) dfs(1,i);
		int tot=0,ans=0;
		for(int i=1;i<=m;i++)
			if(!vis[n][i]) tot++;
		if(tot) {printf("0\n%d\n",tot);return;}
		int left=1;
		while(left<=m)
		{
			ans++;
			int maxr=0;
			for(int i=1;i<=m;i++)
				if(l[1][i]<=left)
					maxr=max(maxr,r[1][i]);
			left=maxr+1;
		}
		printf("1\n%d\n",ans);
	}
}	

int main()
{
	TYC::work();
	return 0;
}
