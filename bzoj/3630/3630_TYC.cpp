//TYC自制判相交法
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=610,inf=0x3f3f3f3f;
    int S,T,cnt=1,Head[N],dep[N],cur[N];

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
    }E[N*N*4];

    struct Circle
    {
        int id,x,y,r,tags,tagt;
    }c[210];

    struct Square
    {
        int id,x1,y1,x2,y2,tags,tagt;
    }s[210];

    inline void insert(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v],0};
        Head[v]=cnt;
    }

    inline ll sqr(int x)
    {
        return (ll)x*x;
    }

    inline ll dis(int x1,int y1,int x2,int y2)
    {
        return sqr(x1-x2)+sqr(y1-y2);
    }

    inline bool CheckSquares(int a,int b)
    {
        int x1=max(s[a].x1,s[b].x1),x2=min(s[a].x2,s[b].x2);
        if(x1>x2) return false;
        int y1=max(s[a].y1,s[b].y1),y2=min(s[a].y2,s[b].y2);
        if(y1>y2) return false;
        return true;
    }

    inline bool CheckCircleAndSquare(int a,int b)
    {
        int x=c[a].x,y=c[a].y,r=c[a].r,x1=s[b].x1,y1=s[b].y1,x2=s[b].x2,y2=s[b].y2;
        if(x1<=x&&x<=x2&&y1<=y&&y<=y2) 
            return true;
        else if(x1<=x&&x<=x2)
            return (y<y1&&y+r>=y1)||(y>y2&&y-r<=y2);
        else if(y1<=y&&y<=y2)
            return (x<x1&&x+r>=x1)||(x>x2&&x-r<=x2);
        else if(x<x1&&y>y2)
            return dis(x,y,x1,y2)<=sqr(r);
        else if(x<x1&&y<y1)
            return dis(x,y,x1,y1)<=sqr(r);
        else if(x>x2&&y>y2)
            return dis(x,y,x2,y2)<=sqr(r);
        else if(x>x2&&y<y1)
            return dis(x,y,x2,y1)<=sqr(r);
    }
    
    bool bfs()
    {
        memset(dep,-1,sizeof(dep));
        memcpy(cur,Head,sizeof(cur));
        queue<int> q;
        dep[S]=0;
        q.push(S);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(E[i].w&&dep[v]==-1)
                    dep[v]=dep[u]+1,q.push(v);
            }
        }
        return dep[T]!=-1;
    }

    int dfs(int u,int mn)
    {
        if(u==T) return mn;
        int v,w,used=0;
        for(int &i=cur[u];i;i=E[i].next)
        {
            v=E[i].to;
            if(E[i].w&&dep[v]==dep[u]+1)
            {
                w=dfs(v,min(mn-used,E[i].w));
                used+=w;
                E[i].w-=w,E[i^1].w+=w;
                if(used==mn) return used;
            }
        }
        if(!used) dep[u]=-1;
        return used;
    }

    int Dinic()
    {
        int ans=0;
        while(bfs()) ans+=dfs(S,inf);
        return ans;
    }

    void work()
    {
        int X=read(),Y=read(),n=read();
        S=(n<<1)+1,T=S+1;
        int totc=0,tots=0;
        for(int i=1;i<=n;i++)
            insert(i,i+n,1);
        for(int i=1;i<=n;i++)
        {
            int opt=read();
            if(opt==1)
            {
                int x=read(),y=read(),r=read();
                c[++totc]=(Circle){i,x,y,r};
                if(y-r<=0) insert(S,i,1),c[totc].tags=1;
                if(r+y>=Y) insert(i+n,T,1),c[totc].tagt=1;
            }
            else
            {
                int x1=read(),y1=read(),x2=read(),y2=read();
                s[++tots]=(Square){i,x1,y1,x2,y2};
                if(y2>0&&y1<=0&&x2>0&&x1<=X) insert(S,i,1),s[tots].tags=1;
                if(y2>=Y&&y1<Y&&x2>0&&x1<=X) insert(i+n,T,1),s[tots].tagt=1;
            }
        }
        for(int i=1;i<=totc;i++)
        {
            for(int j=1;j<=totc;j++)
                if(i!=j&&dis(c[i].x,c[i].y,c[j].x,c[j].y)<=sqr(c[i].r+c[j].r))
                {
                    int a=c[i].id,b=c[j].id;
                    insert(a+n,b,1),insert(b+n,a,1);
                }
            for(int j=1;j<=tots;j++)
                if(CheckCircleAndSquare(i,j))
                {
                    int a=c[i].id,b=s[j].id;
                    insert(a+n,b,1),insert(b+n,a,1);
                }
        }
        for(int i=1;i<=tots;i++)
            for(int j=1;j<=tots;j++)
                if(i!=j&&CheckSquares(i,j))
                {
                    int a=s[i].id,b=s[j].id;
                    insert(a+n,b,1),insert(b+n,a,1);
                }
        printf("%d\n",Dinic());
    }
}

int main()
{
    TYC::work();
    return 0;
}
