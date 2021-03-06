#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=210,inf=0x3f3f3f3f;
    int n,m,s,t,cnt=1,Head[N],pre[N],dis[N],vis[N];
    string name[N];
    map<string,int> id;
    typedef pair<int,int> pa;
    vector<int> path;

    struct edge	
    {
		int from,to,next,w,c;
    }E[N*N*2];

    void insert(int u,int v,int w,int c)
    {
		E[++cnt]=(edge){u,v,Head[u],w,c};
		Head[u]=cnt;
		E[++cnt]=(edge){v,u,Head[v],0,-c};
		Head[v]=cnt;
    }

    bool spfa()
    {
		memset(pre,0,sizeof(pre));
		for(int i=1;i<=t;i++) dis[i]=-inf;
		queue<int> q;
		q.push(s);
		dis[s]=0,vis[s]=1;
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
		return dis[t]!=-inf;
    }

    pa mcmf()
    {
		int ans=0,flow=0;
		while(spfa())
		{
			int mn=inf;
			for(int i=pre[t];i;i=pre[E[i].from])
				mn=min(mn,E[i].w);
			for(int i=pre[t];i;i=pre[E[i].from])
				E[i].w-=mn,E[i^1].w+=mn;
			flow+=mn;
			ans+=mn*dis[t];
		}
		return make_pair(flow,ans);
    }

    void get_path(int u)
    {
		while(1)
		{
			if(u<=n) path.push_back(u);
			if(u==n) return;
			for(int i=Head[u];i;i=E[i].next)
				if((!E[i].w&&!(i&1))||E[i].to==u+n||(u==n+1&&E[i].to==n&&E[i].w!=2)) 
					{u=E[i].to;E[i].w++;break;}
		}
    }

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>n>>m;
		s=1,t=n*2;
		for(int i=1;i<=n;i++)
		{
			cin>>name[i];
			id[name[i]]=i;
		}
		insert(1,1+n,2,0),insert(n,n+n,2,0);
		for(int i=2;i<n;i++) 
			insert(i,i+n,1,0);//把每个点拆成入点和出点,i入i+n出
		string x,y;
		for(int i=1;i<=m;i++)
		{
			cin>>x>>y;
			int u=id[x],v=id[y];
			if(u>v) swap(u,v);
			if(u==1&&v==n) insert(n+1,n,2,1);
			else insert(u+n,v,1,1);
		}
		pa ans=mcmf();
		if(ans.first!=2) {cout<<"No Solution!";return;}
		cout<<ans.second<<endl;
		get_path(1);
		for(int i=0;i<path.size();i++) cout<<name[path[i]]<<endl;
		path.clear();
		get_path(1);
		for(int i=path.size()-2;i>=0;i--) cout<<name[path[i]]<<endl;
    }
}

int main()
{
    TYC::work();
    return 0;
}
