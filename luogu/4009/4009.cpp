#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int N=110,inf=0x3f3f3f3f;
    const int dx[5]={0,0,1,0,-1},dy[5]={0,1,0,-1,0};
    int n,K,A,B,C,G[N][N],dis[N][N][15],vis[N][N][15];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct node
    {
		int x,y,rest;
		node(int _x,int _y,int _r):x(_x),y(_y),rest(_r){}
    };

    void spfa()//分层图spfa
    {
		memset(dis,inf,sizeof(dis));
		queue<node> q;
		q.push(node(1,1,K));
		dis[1][1][K]=0,vis[1][1][K]=1;
		while(!q.empty())
		{
			int x=q.front().x,y=q.front().y,r=q.front().rest;
			q.pop();
			vis[x][y][r]=0;
			if(G[x][y]&&r!=K)//有站强制加油
			{
				if(dis[x][y][K]>dis[x][y][r]+A)
				{
					dis[x][y][K]=dis[x][y][r]+A;
					if(!vis[x][y][K]) vis[x][y][K]=1,q.push(node(x,y,K));
				}
				continue;//这个点有加油站就必须要加油,不能直接走,要用加满油的点再走
			}
			if(!G[x][y]&&r!=K)//建站
			{
				if(dis[x][y][K]>dis[x][y][r]+A+C)
				{
					dis[x][y][K]=dis[x][y][r]+A+C;
					if(!vis[x][y][K]) vis[x][y][K]=1,q.push(node(x,y,K));
				}
			}
			if(r>0)//继续开
			{
				for(int i=1;i<=4;i++)
				{
					int xx=x+dx[i],yy=y+dy[i];
					if(xx<0||xx>n||yy<0||yy>n) continue;
					if(i!=3&&i!=4)
					{if(dis[xx][yy][r-1]>dis[x][y][r]) dis[xx][yy][r-1]=dis[x][y][r];}
					else
					{if(dis[xx][yy][r-1]>dis[x][y][r]+B) dis[xx][yy][r-1]=dis[x][y][r]+B;}
					if(!vis[xx][yy][r-1]) vis[xx][yy][r-1]=1,q.push(node(xx,yy,r-1));
				}
			}
		}
    }

    void work()
    {
		n=read(),K=read(),A=read(),B=read(),C=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				G[i][j]=read();
		spfa();
		int ans=inf+10;
		for(int i=0;i<=K;i++) ans=min(ans,dis[n][n][i]);
		printf("%d",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
