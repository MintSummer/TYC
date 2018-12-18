#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int K=12;
	const int N=510;
	const int MX=500*500;
	const int M=500*500+10;
	const int inf=0x3f3f3f3f;
	const int dx[]={-1,0,1,0};
	const int dy[]={0,1,0,-1};

	int n,m,k,num,f[K][K][N][N],val[M];
	char mp[N][N];
	pa pos[K],to[N][N][4],list[M];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	#define Mod(x,mod) (x)>=(mod)?(x)-(mod):(x)

	pa dfs(const int x,const int y,const int dir,const int tim)
	{
		static int vis[N][N][4];
		if(vis[x][y][dir]==tim) return pa(-1,-1);
		vis[x][y][dir]=tim;
		pa &now=to[x][y][dir];
		if(now.second) return now;
		int d=dir;
		if(mp[x][y]=='A') d=Mod(d-1+4,4);
		else if(mp[x][y]=='C') d=Mod(d+1,4);
		int nx=x+dx[d],ny=y+dy[d];
		if(nx<1||nx>n||ny<1||ny>m||mp[nx][ny]=='#') 
			return now=pa(x,y);
		else return now=dfs(nx,ny,d,tim);
	}

	void spfa(int dp[N][N])
	{
		static bool vis[N][N];
		static int bask[M];
		static pa tmp[M],q[M];
		memset(bask,0,sizeof(bask));
		memset(vis,false,sizeof(vis));

		int mn=inf,mx=-inf;
		for(int i=1;i<=num;i++)
		{
			bask[val[i]]++;
			mn=min(mn,val[i]),mx=max(mx,val[i]);
			vis[list[i].first][list[i].second]=true;
		}
		for(int i=mn;i<=mx;i++) bask[i]+=bask[i-1];
		for(int i=1;i<=num;i++) tmp[bask[val[i]]--]=list[i];
		for(int i=1;i<=num;i++) list[i]=tmp[i];
		
		int head=0,tail=0;	
		while(num||head!=tail)
		{
			int now=Mod(head,MX)+1,x,y;
			if(head==tail||(num&&dp[list[num].first][list[num].second]<dp[q[now].first][q[now].second]))
			{
				x=list[num].first;
				y=list[num].second;
				num--;
			}
			else
			{
				head=now;
				x=q[head].first;
				y=q[head].second;
			}
			vis[x][y]=false;
			for(int i=0;i<4;i++)
			{
				int nx=to[x][y][i].first,ny=to[x][y][i].second;
				if(nx!=-1&&dp[nx][ny]>dp[x][y]+1)
				{
					dp[nx][ny]=dp[x][y]+1;
					if(!vis[nx][ny])
						vis[nx][ny]=true,q[tail=Mod(tail,M)+1]=to[x][y][i];
				}
			}
		}
	}

	void work()
	{
		k=read(),m=read(),n=read();
		char ch=getchar();
		memset(f,inf,sizeof(f));
		for(int i=1;i<=n;i++)
		{
			while(!isdigit(ch)&&!isalpha(ch)&&ch!='.') ch=getchar();
			for(int j=1;j<=m;j++,ch=getchar())
			{
				mp[i][j]=ch;
				if(isdigit(ch))
				{
					int c=ch-'0';
					pos[c]=pa(i,j);
					f[c][c][i][j]=0;
				}
			}
		}
		int tim=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				for(int k=0;k<4;k++)
					to[i][j][k]=dfs(i,j,k,++tim);
		for(int i=1;i<=k;i++)
		{
			list[num=1]=pos[i];
			val[1]=0;
			spfa(f[i][i]);
		}
		for(int l=k-1;l;l--)
			for(int r=l+1;r<=k;r++)
			{
				num=0;
				for(int i=1;i<=n;i++)
					for(int j=1;j<=m;j++)
					{
						for(int d=l;d<r;d++)
							f[l][r][i][j]=min(f[l][r][i][j],f[l][d][i][j]+f[d+1][r][i][j]);
						if(f[l][r][i][j]!=inf) 
						{
							list[++num]=pa(i,j);
							val[num]=f[l][r][i][j];
						}
					}
				spfa(f[l][r]);
			}
		int ans=inf;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				ans=min(ans,f[1][k][i][j]);
		printf("%d\n",ans==inf?-1:ans);
	}
}

int main()
{
	freopen("a.in","r",stdin);
	TYC::work();
	return 0;
}
