#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f,MAXN=60;
    int N,M,K,S,T,cnt=1,ans;
    int a[MAXN],l[MAXN],p[MAXN],d[MAXN],q[MAXN],Head[MAXN*4],pre[MAXN*4],dis[MAXN*4],vis[MAXN*4];

    struct edge
    {
		int from,to,w,c,next;
    }E[60010];

    void add(int u,int v,int w,int c)
    {
		E[++cnt]=(edge){u,v,w,c,Head[u]};
		Head[u]=cnt;
    }

    void insert(int u,int v,int w,int c)
    {
		add(u,v,w,c);
		add(v,u,0,-c);
    }

    bool spfa()
    {
		memset(dis,inf,sizeof(dis));
		memset(pre,0,sizeof(pre));
		queue<int> q;
		q.push(S);
		dis[S]=0,vis[S]=1;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			vis[u]=0;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w>0&&dis[v]>dis[u]+E[i].c)
				{
					dis[v]=dis[u]+E[i].c;
					pre[v]=i;
					if(!vis[v]) vis[v]=1,q.push(v);
				}
			}
		}
		return dis[T]!=inf;
    }

    int mcmf()
    {
		int flow=0;
		while(spfa())
		{
			int mn=inf;
			for(int i=pre[T];i;i=pre[E[i].from])
				mn=min(mn,E[i].w);
			for(int i=pre[T];i;i=pre[E[i].from])
				E[i].w-=mn,E[i^1].w+=mn;
			ans+=mn*dis[T];
			flow+=mn;
		}
		return flow;
    }

    void work()
    {
		int tim;
		cin>>tim;
		for(int kase=1;kase<=tim;kase++)
		{
			ans=0,cnt=1;
			memset(Head,0,sizeof(Head));
			cin>>N>>M>>K;
			S=0,T=2*N+M+1;
			int sum=0;
			for(int i=1;i<=N;i++) 
				cin>>a[i],sum+=a[i];
			for(int i=1;i<=M;i++) 
				cin>>l[i]>>p[i],insert(S,i,l[i],0);
			for(int i=1;i<=K;i++) 
				cin>>d[i]>>q[i];

			for(int i=1;i<=N;i++)
			{
				for(int j=1;j<=M;j++) insert(j,M+i,inf,p[j]);
				insert(M+i,T,a[i],0);

				insert(S,N+M+i,a[i],0);
				if(i!=N) insert(N+M+i,N+M+i+1,inf,0);
				for(int j=1;j<=K;j++)
					if(i+d[j]<N) insert(N+M+i,M+i+d[j]+1,inf,q[j]);
			}
			cout<<"Case "<<kase<<": ";
			if(mcmf()!=sum) cout<<"impossible";
			else cout<<ans;
			cout<<endl;
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
