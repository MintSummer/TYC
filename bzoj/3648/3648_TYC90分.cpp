//纯TYC自写版->只有90分...... 点分治(树)的点WA了......
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
const int N=100010,inf=0x3f3f3f3f;
int n,m,k,num,tot,cx,cy,Head[N],mark[N];
ll ans;

struct edge
{
	int to,next;
}E[N*2];

namespace Tree
{
    int root,sum,cnt;
    int f[N],size[N],len[N],vis[N];
    
    void find_root(int u,int fa)
    {
		size[u]=1,f[u]=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa||vis[v]||mark[v]) continue;
			find_root(v,u);
			size[u]+=size[v];
			f[u]=max(f[u],size[v]);
		}
		f[u]=max(f[u],sum-size[u]);
		if(f[u]<f[root]) root=u;
    }
    
    void dfs(int u,int fa,int d)
    {
    	len[++cnt]=d;
    	for(int i=Head[u];i;i=E[i].next)
    	{
    		int v=E[i].to;
    		if(vis[v]||mark[v]||v==fa) continue;
    		dfs(v,u,d+1);
    	}
    }

	int cal(int u,int c)
	{
		cnt=0;
		dfs(u,0,c);
		sort(len+1,len+1+cnt);
		int tmp=0;
		for(int l=1,r=cnt;l<r;)
		{
			if(len[l]+len[r]>=k) tmp+=r-l,r--;
			else l++;
		}
		return tmp;
	}

    void solve(int u)
    {
    	ans+=cal(u,0);
		vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]||mark[v]) continue;
			ans-=cal(v,1);
			sum=size[v];
			root=0;
			find_root(v,root);
			solve(root);
		}
    }

    void work(int rot,int node)
    {
		f[0]=inf,root=0,sum=node;
		find_root(rot,0);
		solve(root);
    }
}

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

namespace Circle
{
    using namespace Bit;
    int cir[N*2],dep[N];
    vector<int> tree[N];

    void find_circle(int u,int fa)
    {
		if(u==cy) {cir[++tot]=u;return;}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa) continue;
			find_circle(v,u);
			if(mark[v]) cir[++tot]=u,mark[u]=1;
		}
    }
    
    void dfs(int u,int fa,int root)
    {
    	dep[u]=dep[fa]+1;
    	tree[root].push_back(u);
    	for(int i=Head[u];i;i=E[i].next)
    	{
    		int v=E[i].to;
    		if(v==fa||mark[v]) continue;
    		dfs(v,u,root);
    	}
    }

    void work()
    {
    	mark[cx]=mark[cy]=1;
		find_circle(cx,0);
		for(int i=1;i<=tot;i++) cir[i+tot]=cir[i];
		for(int i=1;i<=tot;i++)
		{
			dfs(cir[i],0,cir[i]);
			mark[cir[i]]=0;
			Tree::work(cir[i],tree[cir[i]].size());
			mark[cir[i]]=1;
		}
		k++;
		int delta=2*tot,root;
		for(int i=1;i<=tot*2;i++)
		{
			if(i>tot)
			{
				root=cir[i-tot];
				for(int j=0;j<tree[root].size();j++)
				{
					int x=tree[root][j];
					add(dep[x]+delta+tot,-1);
				}
				for(int j=0;j<tree[root].size();j++)
				{
					int x=tree[root][j];
					ans+=num-query(k+delta-dep[x]);
				}
			}
			root=cir[i];
			for(int j=0;j<tree[root].size();j++)
			{
				int x=tree[root][j];
				add(dep[x]+delta,1);
			} 
			delta--;
		}	    
    }
}

namespace TYC
{
    int cnt,fa[N];
	
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
    
    int find(int a)
    {
    	return a==fa[a]?a:fa[a]=find(fa[a]);
    }

    void work()
    {
		n=read(),m=read(),k=read();
		k--;
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			int fu=find(u),fv=find(v);
			if(fu==fv)
				cx=u,cy=v;
			else
			{
				add(u,v),add(v,u);
				fa[fu]=fv;
			}
		}
		if(m==n) Circle::work();
		else Tree::work(1,n);
		printf("%lld\n",ans);
    }
}

int main()
{
	freopen("3648.in","r",stdin);
	freopen("3648.out","w",stdout);
    TYC::work();
    return 0;
}
