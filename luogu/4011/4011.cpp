#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f;
    const int dx[5]={0,1,0,-1,0},dy[5]={0,0,1,0,-1};
    int n,m,G[15][15][15][15],key[15][15][15],num[15][15],vis[15][15][1030];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct node
    {
		int x,y,situ,tim;
		node(int _x,int _y,int _si,int _t):x(_x),y(_y),situ(_si),tim(_t){}
    };

    int bfs()
    {
		queue<node> q;
		int situ=0;
		for(int i=1;i<=num[1][1];i++)
			situ|=(1<<(key[1][1][i]-1));
		q.push(node(1,1,situ,0));
		vis[1][1][situ]=1;
		while(!q.empty())
		{
			node now=q.front();
			q.pop();
			int x=now.x,y=now.y;
			if(x==n&&y==m) return now.tim;
			for(int i=1;i<=4;i++)
			{
				int xx=x+dx[i],yy=y+dy[i];
				if(G[x][y][xx][yy]==-1||xx<1||xx>n||yy<1||yy>m) continue;
				int situ=now.situ,t=G[x][y][xx][yy];
				if(t!=0&&(situ&(1<<(t-1)))==0) continue;
				for(int j=1;j<=num[xx][yy];j++)
					situ|=(1<<(key[xx][yy][j]-1));
				if(!vis[xx][yy][situ])
				{
					vis[xx][yy][situ]=1;
					q.push(node(xx,yy,situ,now.tim+1));
				}
			}
		}
		return -1;
	}
		
	void work()
	{
		n=read(),m=read();
		int p=read(),k=read();
		for(int i=1;i<=k;i++)
		{
			int x1=read(),y1=read(),x2=read(),y2=read(),g=read();
			if(!g) G[x1][y1][x2][y2]=G[x2][y2][x1][y1]=-1;
			else G[x1][y1][x2][y2]=G[x2][y2][x1][y1]=g;
		}
		int s=read();
		for(int i=1;i<=s;i++)
		{
			int x=read(),y=read(),q=read();
			key[x][y][++num[x][y]]=q;//一个点不一定只有一个钥匙
		}
		printf("%d\n",bfs());
    }
}

int main()
{
    TYC::work();
    return 0;
}
