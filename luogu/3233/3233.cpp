#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=300010;
    int n,m,cnt,num,dfstim,res[N],list[N],a[N<<1],Head[N],dep[N],fa[N][21],size[N],dfnin[N],dfnout[N],mark[N],dp[N],st[N],vis[N];
    #define Abs(x) x<0?-x:x

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next;
    }E[N<<1];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    void dfs(int u,int f)
    {
        size[u]=1;
        dep[u]=dep[f]+1;
        dfnin[u]=++dfstim;
        fa[u][0]=f;
        for(int i=1;i<=19;i++)
            fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u);
            size[u]+=size[v];
        }
        dfnout[u]=dfstim;
    }

    int LCA(int u,int v)
    {
        if(dep[u]<dep[v]) swap(u,v);
        for(int d=dep[u]-dep[v],t=0;d;d>>=1,t++)
            if(d&1) u=fa[u][t];
        if(u==v) return u;
        for(int i=19;i>=0;i--)
            if(fa[u][i]!=fa[v][i])
                u=fa[u][i],v=fa[v][i];
        return fa[u][0];
    }

    bool cmp(int x,int y)
    {
        int t1=(x>0?dfnin[x]:dfnout[-x]);
        int t2=(y>0?dfnin[y]:dfnout[-y]);
        return t1==t2?dep[Abs(x)]>dep[Abs(y)]:t1<t2;
    }

    int find(int u,int tim)
    {
		if(tim<0) return u;
        for(int i=0;tim;tim>>=1,i++)
            u=fa[u][i];
        return u;
    }

    void work()
    {
        n=read();
		int Node=num;
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        dfs(1,0);
        m=read();
        while(m--)
        {
            num=read();
			int Node=num;
            for(int i=1;i<=num;i++) 
                list[i]=a[i]=read(),mark[a[i]]=vis[a[i]]=1;
            sort(a+1,a+1+num,cmp);
            for(int i=1;i<num;i++)
            {
                int lca=LCA(a[i],a[i+1]);
                if(!mark[lca])
                    mark[lca]=1,a[++num]=lca;
            }
            for(int i=1,tmp=num;i<=tmp;i++) 
				a[++num]=-a[i],res[a[i]]=size[a[i]];
            sort(a+1,a+1+num,cmp);
            int top=0;
            for(int i=1;i<=num;i++)
            {
                if(a[i]>0) st[++top]=a[i];
                else
                {
                    int now=st[top--],f=st[top];
					if(!f) continue;
                    int dis=dep[now]-dep[f],mid=find(now,dis>>1);
					int nxt=find(now,dis-1);
					res[f]-=size[nxt];
                    dp[f]+=size[nxt]-size[mid],dp[now]+=size[mid]-size[now];
                }
            }
			for(int i=1;i<=Node;i++)
				printf("%d ",dp[list[i]]+res[list[i]]);
            for(int i=1;i<=num;i++)
			{
				if(a[i]<0) continue;
				dp[a[i]]=res[a[i]]=mark[a[i]]=vis[a[i]]=0;
			}
			puts("");
        }
    }
}

int main()
{
    freopen("a.in","r",stdin);
    TYC::work();
    return 0;
}
