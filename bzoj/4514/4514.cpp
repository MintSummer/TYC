#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cctype>
using namespace std;

namespace TYC
{
	typedef long long ll;
    const int N=210;
	const ll inf=(1LL<<60);
    int n,s,t,cnt=1,a[N],b[N],c[N],num[N],Head[N],pre[N],vis[N];
	ll dis[N];

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
		ll w,c;
    }E[N*N*4];

    void insert(int u,int v,ll w,ll c)
    {
        E[++cnt]=(edge){v,Head[u],w,c};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v],0LL,-c};
        Head[v]=cnt;
    }

    bool spfa()
    {
        memset(pre,0,sizeof(pre));
		for(int i=1;i<=t;i++) dis[i]=-inf;
        queue<int> q;
		dis[s]=0;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            vis[u]=0;
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(E[i].w&&dis[v]<dis[u]+E[i].c)
                {
                    dis[v]=dis[u]+E[i].c;
                    pre[v]=i;
                    if(!vis[v]) vis[v]=1,q.push(v);
                }
            }
        }
        return dis[t]!=-inf;
    }

    ll mcmf()
    {
        ll sum=0,ans=0;
        while(spfa())
        {
            ll mn=inf;
            for(int i=pre[t];i;i=pre[E[i^1].to])
                mn=min(mn,E[i].w);
            for(int i=pre[t];i;i=pre[E[i^1].to])
                E[i].w-=mn,E[i^1].w+=mn;
            if(sum+dis[t]*mn<0) return ans+=sum/(-dis[t]);
			ans+=mn,sum+=dis[t]*mn;
        }
		return ans;
    }

    void work()
    {
        n=read();
        s=n+1,t=s+1;
        for(int i=1;i<=n;i++) a[i]=read();
        for(int i=1;i<=n;i++) b[i]=read();
        for(int i=1;i<=n;i++) c[i]=read();
        for(int i=1;i<=n;i++)
        {
			int tmp=a[i];
            for(int p=2,limit=sqrt(a[i]);p<=limit;p++)
                while(!(tmp%p)) num[i]++,tmp/=p;
			if(tmp>1) num[i]++;
            if(num[i]&1) insert(s,i,b[i],0);
            else insert(i,t,b[i],0);
        }
        for(int i=1;i<=n;i++) if(num[i]&1)
            for(int j=1;j<=n;j++)
                if((!(a[j]%a[i])&&num[i]+1==num[j])||
				   (!(a[i]%a[j])&&num[j]+1==num[i]))
                    insert(i,j,inf,1LL*c[i]*c[j]);
        printf("%lld\n",mcmf());
     }
}

int main()
{
    TYC::work();
    return 0;
}
