#include<bits/stdc++.h>
using namespace std;

namespace TYC
{	
	typedef pair<int,int> pii;
	typedef pair<int,pii> pip;
	const int N=110;
	const int M=200*200+10;
	const int dx[]={-1,1,0,0};
	const int dy[]={0,0,1,-1};

	int n,numx,numy,Head[N],dis[M],G[M][4],id[N<<1][N<<1];

	struct square
	{
		int x,y,c;
	}squ[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void add(int a,int b,int type)
	{
		G[a][type]=G[b][type^1]=1;
	}

	void Dijkstra(int sx,int sy)
	{
		static priority_queue<pip,vector<pip>,greater<pip> > q;
		static bool vis[M];
		memset(dis,0x3f3f3f3f,sizeof(dis));
		dis[id[sx][sy]]=0;
		q.push(pip(0,pii(sx,sy)));
		while(!q.empty())
		{
			pip now=q.top();
			q.pop();
			int x=now.second.first,y=now.second.second;
			int u=id[x][y];
			if(vis[u]) continue;
			vis[u]=1;
			for(int i=0;i<4;i++)
			{
				int nx=x+dx[i],ny=y+dy[i];
				if(nx<1||nx>numx||ny<1||ny>numy) continue;
				int v=id[nx][ny];
				if(dis[v]>dis[u]+G[u][i])
				{
					dis[v]=dis[u]+G[u][i];
					if(!vis[v]) q.push(pip(dis[v],pii(nx,ny)));
				}
			}
		}
	}

	void work()
	{
		n=read();
		int tot=0;
		static int tx[N<<1],ty[N<<1];
		for(int i=1;i<=n;i++)
		{
			int x=read(),y=read(),c=read();
			squ[i]=(square){x,y,c};
			tx[++tot]=x,ty[tot]=y;
			tx[++tot]=x+c,ty[tot]=y+c;
		}
		int Sx=read(),Sy=read(),Tx=read(),Ty=read();
		tx[++tot]=Sx,ty[tot]=Sy;
		tx[++tot]=Tx,ty[tot]=Ty;
		sort(tx+1,tx+1+tot);
		sort(ty+1,ty+1+tot);
		numx=unique(tx+1,tx+1+tot)-tx-1;
		numy=unique(ty+1,ty+1+tot)-ty-1;
		tot=0;
		for(int i=1;i<=numx;i++)
			for(int j=1;j<=numx;j++)
				id[i][j]=++tot;
		for(int p=1;p<=n;p++)
		{
			int x1=lower_bound(tx+1,tx+1+numx,squ[p].x)-tx;
			int y1=lower_bound(ty+1,ty+1+numy,squ[p].y)-ty; 
			int x2=lower_bound(tx+1,tx+1+numx,squ[p].x+squ[p].c)-tx;
			int y2=lower_bound(ty+1,ty+1+numy,squ[p].y+squ[p].c)-ty;
			if(y1!=1) for(int i=x1;i<=x2;i++)
				add(id[i][y1-1],id[i][y1],2);
			if(y2!=n) for(int i=x1;i<=x2;i++)
				add(id[i][y2],id[i][y2+1],3);
			if(x1!=1) for(int i=y1;i<=y2;i++)
				add(id[x1-1][i],id[x1][i],1);
			if(x2!=n) for(int i=y1;i<=y2;i++)
				add(id[x2][i],id[x2+1][i],0);
		}
		Sx=lower_bound(tx+1,tx+1+numx,Sx)-tx;
		Sy=lower_bound(ty+1,ty+1+numy,Sy)-ty;
		Tx=lower_bound(tx+1,tx+1+numx,Tx)-tx;
		Ty=lower_bound(ty+1,ty+1+numy,Ty)-ty;
		Dijkstra(Sx,Sy);
		printf("%d\n",dis[id[Tx][Ty]]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
