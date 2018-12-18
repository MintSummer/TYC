#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
const int N=100010,inf=0x3f3f3f3f;
int n,m,k,num,tot,tail,q[N],Head[N],vis[N];
ll ans;

struct edge
{
	int to,next;
}E[N*2];

namespace Bit
{
    #define lowbit(x) x&(-x)
    int c[N*3];

    void add(int x,int val)
    {
		num+=val;
		for(;x<=n+tot*2;x+=lowbit(x)) c[x]+=val;
    }

    int query(int x)
    {
		int sum=0;
		if(x<1)return 0;
		for(;x>0;x-=lowbit(x)) 
		    sum+=c[x];
		return sum;
    }
}

namespace Tree
{
	using namespace Bit;
    int root,sum,tot;
    int f[N],size[N],dis[N];
    
    void find_root(int u,int fa)
    {
		size[u]=1,f[u]=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa||vis[v]) continue;
			find_root(v,u);
			size[u]+=size[v];
			f[u]=max(f[u],size[v]);
		}
		f[u]=max(f[u],sum-size[u]);
		if(f[u]<f[root]) root=u;
    }

    void dfs(int u,int f)
    {
		q[++tail]=dis[u];
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]||v==f) continue;
			dis[v]=dis[u]+1;
			dfs(v,u);
		}
    }

    void solve(int u)
    {
		vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			dis[v]=1;
			dfs(v,u);
			for(int j=1;j<=tail;j++)
			{
				if(q[j]+1>=k) ans++;
				ans+=num-query(k-q[j]-2);
			}
			while(tail) add(q[tail--],1);
		}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			dfs(v,u);
			while(tail) add(q[tail--],-1);
		}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]||size[v]<k) continue;
			root=0; 
			sum=size[v];
			find_root(v,u);
			solve(root);
		}
    }

    void work(int rot)
    {
		f[0]=n+1,root=0,sum=n;
		find_root(rot,0);
		solve(root);
    }
}

namespace Circle
{
    using namespace Bit;
    int flag,top,in[N],st[N],cir[N*2];

    void find_circle(int u,int f)
    {
		if(flag) return;
		st[++top]=u;
		in[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			if(in[v])
			{
				while(st[top]!=v) cir[++tot]=st[top--];
				cir[++tot]=v;
				flag=1;
			}
			else find_circle(v,u);
		}
		top--;
		in[u]=0;
    }

    void work()
    {
		find_circle(1,0);
		for(int i=1;i<=tot;i++) 
			cir[i+tot]=cir[i],vis[cir[i]]=1;
		for(int i=1;i<=tot;i++)
		{
			vis[cir[i]]=0;
			Tree::work(cir[i]);
			vis[cir[i]]=1;
		}
		int delta=2*tot,root;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=tot;i++) vis[cir[i]]=1;
		tail=0;
		for(int i=1;i<=tot*2;i++)
		{
			if(i>tot)
			{
				root=cir[i-tot];
				vis[root]=0;
				Tree::dfs(root,0);
				vis[root]=1;
				for(int j=1;j<=tail;j++) 
					add(q[j]+delta+tot,-1); 
				for(int j=1;j<=tail;j++)
					ans+=num-query(k+delta-q[j]);
				tail=0;
			}
			root=cir[i];
			Tree::dis[root]=1;
			vis[root]=0;
			Tree::dfs(root,0);
			vis[root]=1;
			while(tail) add(q[tail--]+delta,1);
			delta--;
		}	    
    }
}

namespace TYC
{
    int cnt;
	
    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void add(int u,int v)
    {
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
    }

    void work()
    {
		n=read(),m=read(),k=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		if(m==n-1) Tree::work(1);
		else Circle::work();
		printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
