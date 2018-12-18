#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=40,inf=0x3f3f3f3f;
    const int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
    int n,m,question,Bx,By,Sx,Sy,Tx,Ty,cnt,dis[N][N],Head[5010],distance[5010];
    bool G[N][N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct stu
    {
        int x,y;
    }q[N];

    struct edge
    {
        int to,next,w;
    }E[200010];

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    inline int pos(int x,int y,int dir)
    {
        return x*120+y*4+dir;
    }

    void bfs(int sx,int sy,int bx,int by,int dir)
    {
        int h=1,t=0;
        memset(dis,-1,sizeof(dis));
        dis[bx][by]=0;
        q[++t]=(stu){bx,by};
        while(h<=t)
        {
            stu now=q[h++];
            for(int i=0;i<4;i++)
            {
                int x=now.x+dx[i],y=now.y+dy[i];
                if(G[x][y]&&dis[x][y]==-1&&(x!=sx||y!=sy))
                    dis[x][y]=dis[now.x][now.y]+1,q[++t]=(stu){x,y};
            }
        }
        if(dir==4) return;
        for(int i=0;i<4;i++)
        {
            int x=sx+dx[i],y=sy+dy[i];
            if((x!=bx||y!=by)&&~dis[x][y])
                add(pos(sx,sy,dir),pos(sx,sy,i),dis[x][y]);
        }
        add(pos(sx,sy,dir),pos(bx,by,dir^1),1);
    }

    void spfa(int sx,int sy)
    {
        static bool vis[5010];
        static int q[100010];
        memset(distance,inf,sizeof(distance));
        int h=1,t=0;
        for(int i=0;i<4;i++)
        {
            int x=sx+dx[i],y=sy+dy[i];
            if(G[x][y]&&dis[x][y]!=-1)
            {
                int tmp=pos(sx,sy,i);
                distance[tmp]=dis[x][y];
                vis[tmp]=1;
                q[++t]=tmp;
            }
        }
        while(h<=t)
        {
            int u=q[h++];
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(distance[v]>distance[u]+E[i].w)
                {
                    distance[v]=distance[u]+E[i].w;
                    if(!vis[v]) vis[v],q[++t]=v;
                }
            }
        }
    }

    void work()
    {
        n=read(),m=read(),question=read();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                G[i][j]=read();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                if(!G[i][j]) continue;
                if(G[i-1][j]) bfs(i,j,i-1,j,0);
                if(G[i+1][j]) bfs(i,j,i+1,j,1);
                if(G[i][j-1]) bfs(i,j,i,j-1,2);
                if(G[i][j+1]) bfs(i,j,i,j+1,3);
            }
        while(question--)
        {
            Bx=read(),By=read(),Sx=read(),Sy=read(),Tx=read(),Ty=read();
            if(Sx==Tx&&Sy==Ty) {puts("0");continue;}
            bfs(Sx,Sy,Bx,By,4);
            spfa(Bx,By);
            int ans=inf;
            for(int i=0;i<4;i++)   
                ans=min(ans,distance[pos(Tx,Ty,i)]); 
            if(ans==inf) puts("-1");
            else printf("%d\n",ans);
        }
    }
}

int main()
{
    freopen("a.in","r",stdin);
    TYC::work();
    return 0;
}