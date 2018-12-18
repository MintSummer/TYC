#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1000010,inf=0x3f3f3f3f;
    int n,m,cnt,dfstim,top,num,fir,size[N],Head[N],fa[N][22],dep[N],dfnin[N],dfnout[N],a[N],mark[N],st[N],real[N],mx[N],mn[N];
    ll sum[N];
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
        dfnin[u]=++dfstim;
        dep[u]=dep[f]+1;
        fa[u][0]=f;
        for(int i=1;i<=20;i++)
            fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u);
        }
        dfnout[u]=dfstim;
    }

    int LCA(int u,int v)
    {
        if(dep[u]<dep[v]) swap(u,v);
        for(int d=dep[u]-dep[v],t=0;d;d>>=1,t++)
            if(d&1) u=fa[u][t];
        if(u==v) return u;
        for(int i=20;i>=0;i--)
            if(fa[u][i]!=fa[v][i])
                u=fa[u][i],v=fa[v][i];
        return fa[u][0];
    }

    bool cmp(int x,int y)
    {
		if(x==-y) return x>y;
        int t1= x>0?dfnin[x]:dfnout[-x];
        int t2= y>0?dfnin[y]:dfnout[-y];
        return (t1<t2)||(t1==t2&&dep[Abs(x)]>dep[Abs(y)]);
    }
    
    void search()
    {
        top=0;
		int ans1=inf,ans2=0;
        for(int i=1;i<=num;i++)
        {
            if(a[i]>=0) 
            {
                int now=a[i];
                size[now]=real[now],st[++top]=now;
                sum[now]=mx[now]=0,mn[now]=inf;
            }
            else 
            {
                int now=st[top--],f=st[top];
                int d=dep[now]-dep[f];
				if(real[now])
				{
					ans1=min(ans1,mn[now]),ans2=max(ans2,mx[now]);
					mn[now]=0;
				}
				if(f)
				{
					sum[f]+=sum[now]+1LL*size[now]*(fir-size[now])*d;
					ans1=min(ans1,mn[f]+mn[now]+d);
					mn[f]=min(mn[f],mn[now]+d);
					ans2=max(ans2,mx[f]+mx[now]+d);
					mx[f]=max(mx[f],mx[now]+d);
				}
                size[f]+=size[now];
                size[now]=mark[now]=real[now]=0;
            }
        }
        printf("%lld %d %d\n",sum[st[1]],ans1,ans2);
    }

    void work()
    {
        n=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        dfs(1,0);
        m=read();
        while(m--)
        {
            fir=num=read();
            for(int i=1;i<=num;i++) 
                a[i]=read(),mark[a[i]]=real[a[i]]=1;
            sort(a+1,a+1+num,cmp);
            for(int i=1;i<num;i++)
            {
                int lca=LCA(a[i],a[i+1]);
                if(!mark[lca]) 
                    a[++num]=lca,mark[lca]=1;
            }
            for(int i=1,tmp=num;i<=tmp;i++)
                a[++num]=-a[i];
            sort(a+1,a+1+num,cmp);
            search();
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
