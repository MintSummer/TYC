#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=3e5+10;

namespace Tree
{
    int cnt,ls[N*20],rs[N*20];
    ll val[N*20];//点的权值为 子树大小-1

    void insert(int &root,int last,int l,int r,int v,int dep)
    {
		root=++cnt;
		val[root]=val[last]+v;
		ls[root]=ls[last],rs[root]=rs[last];
		if(l==r) return;
		int mid=(l+r)>>1;
		if(dep<=mid) insert(ls[root],ls[last],l,mid,v,dep);
		else insert(rs[root],rs[root],mid+1,r,v,dep);
    }

    ll query(int x,int y,int l,int r,int s,int e)//查找在s到e区间的点的val和
    {
		if(l==s&&r==e) return val[y]-val[x];
		int mid=(l+r)>>1;
		if(e<=mid) return query(ls[x],ls[y],l,mid,s,e);
		else if(s>mid) return query(rs[x],rs[y],mid+1,r,s,e);
		else return 
			query(ls[x],ls[y],l,mid,s,mid)+query(rs[x],rs[y],mid+1,r,mid+1,e);
    }
}

namespace TYC
{
    using namespace Tree;
    int n,m,cnt,maxdep,tot;
    int Head[N],dep[N],size[N],dfn[N],root[N];//root[i]表示以dfn值为i的点为根

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
    }E[N*2];

    void add(int u,int v)
    {
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
    }

    void dfs1(int u,int f)
    {
		dep[u]=dep[f]+1;
		maxdep=max(maxdep,dep[u]);
		size[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs1(v,u);
			size[u]+=size[v];
		}
    }

    void dfs2(int u,int f)
    {
		dfn[u]=++tot;
		insert(root[tot],root[tot-1],1,maxdep,size[u]-1,dep[u]);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs2(v,u);
		}
    }

    void work()
    {
		n=read(),m=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		dfs1(1,0);
		dfs2(1,0);
		while(m--)
		{
			int a=read(),k=read();
			if(dep[a]==maxdep) {puts("0");continue;}//a为叶子节点
			ll ans=(ll)(size[a]-1)*(min(k,dep[a]-1));//考虑a上方的点为b,则c可为a子树任意点
			int l=dfn[a],r=dfn[a]+size[a]-1;//a的子树范围
			ans+=query(root[l-1],root[r],1,maxdep,dep[a]+1,min(maxdep,dep[a]+k));
			printf("%lld\n",ans);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
