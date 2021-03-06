#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1010,inf=0x3f3f3f3f;
    int n,k,s,t,cnt=1,l[N],r[N],a[N],Head[N],pre[N],vis[N];
    ll len[N],dis[N];
    
    ll sqr(int x)
    {
    	return 1LL*x*x;
    }

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct edge
    {
		int from,to,next,w,c;
    }E[N*N*4];

    void insert(int u,int v,int w,int c)
    {
		E[++cnt]=(edge){u,v,Head[u],w,c};
		Head[u]=cnt;
		E[++cnt]=(edge){v,u,Head[v],0,-c};
		Head[v]=cnt;
    }

    bool spfa()
    {
		memset(vis,0,sizeof(vis));
		memset(pre,0,sizeof(pre));
		for(int i=1;i<=t;i++) dis[i]=-1e14;
		queue<int> q;
		q.push(s);
		dis[s]=0;vis[s]=1;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			vis[u]=0;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w>0&&dis[v]<dis[u]+E[i].c)
				{
					dis[v]=dis[u]+E[i].c;
					pre[v]=i;
					if(!vis[v]) vis[v]=1,q.push(v);
				}
			}
		}
		return dis[t]!=-1e14;
    }

    ll mcmf()
    {
		ll ans=0;
		while(spfa())
		{
			int mn=inf;
			for(int i=pre[t];i;i=pre[E[i].from])
			mn=min(mn,E[i].w);
			for(int i=pre[t];i;i=pre[E[i].from])
			E[i].w-=mn,E[i^1].w+=mn;
			ans+=1LL*mn*dis[t];
		}
		return ans;
    }

    void work()
    {
		n=read(),k=read();
		int tot=0;
		for(int i=1;i<=n;i++)
		{
		    int y1,y2;
		    l[i]=read(),y1=read(),r[i]=read(),y2=read();
		    len[i]=sqrt(sqr(r[i]-l[i])+sqr(y2-y1));
		    l[i]*=2,r[i]*=2;//防止这条线是垂直于x轴连成自环
		    if(l[i]==r[i]) l[i]--;
		    else l[i]++;
		    a[++tot]=l[i],a[++tot]=r[i];
		}
		sort(a+1,a+1+tot);
		tot=unique(a+1,a+1+tot)-a-1;
		s=tot+1,t=tot+2;
		insert(s,1,k,0);
		insert(tot,t,k,0);
		for(int i=1;i<tot;i++) insert(i,i+1,inf,0);
		for(int i=1;i<=n;i++)
		{
			l[i]=lower_bound(a+1,a+1+tot,l[i])-a;
			r[i]=lower_bound(a+1,a+1+tot,r[i])-a;
			insert(l[i],r[i],1,len[i]);
		}
		printf("%lld",mcmf());
    }
}

int main()
{
    TYC::work();
    return 0;
}
