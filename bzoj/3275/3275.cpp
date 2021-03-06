#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=3010,inf=0x3f3f3f3f;
    int N,S,T,cnt=1,dep[MAXN],Head[MAXN],cur[MAXN];
    ll ans=0,a[MAXN];

    struct edge
    {
		int to,next;
		ll w;
    }E[MAXN*8];

    void add(int u,int v,ll w)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    void insert(int u,int v,ll w)
    {
		add(u,v,w),add(v,u,0);
    }

    ll gcd(ll x,ll y)
    {
		return y==0?x:gcd(y,x%y);
    }

    bool check(ll x,ll y)
    {
		double q=sqrt(x*x+y*y);
		if(x%2==y%2) return false;
		if(abs((long long)q-q)>1e-6) return false;
		if(gcd(x,y)!=1) return false;
		return true;
    }

    bool bfs()
    {
		memset(dep,-1,sizeof(dep));
		memcpy(cur,Head,sizeof(cur));
		queue<int> q;
		q.push(S);
		dep[S]=0;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w>0&&dep[v]==-1) 
					dep[v]=dep[u]+1,q.push(v);
			}
		}
		return dep[T]!=-1;
    }

    ll dfs(int u,ll mn)
    {
		if(u==T) return mn;
		ll w,used=0;
		for(int &i=cur[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(E[i].w>0&&dep[v]==dep[u]+1)
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

    ll Dinic()
    {
		while(bfs()) ans-=dfs(S,inf);
		return ans;
    }

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>N;
		S=0,T=N+1;
		for(int i=1;i<=N;i++)
		{
			cin>>a[i];
			ans=ans+a[i];
			if(a[i]%2) insert(S,i,a[i]);
			else insert(i,T,a[i]);
		}
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
			{
				if(i==j) continue;
				if(check(a[i],a[j])) 
				{
					if(a[i]%2) insert(i,j,inf);
					else insert(j,i,inf);
				}
			}
		cout<<Dinic();
    }
}

int main()
{
    TYC::work();
    return 0;
}
