#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int p=201314,N=50010;
    int n,m,cnt,dfs_clock,Head[N],dep[N],size[N],fa[N],son[N],dfn[N],top[N],ans[N];

    struct query
    {
		int id,node,tag;
    };
    vector<query> q[N];

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

    void dfs1(int u)
    {
		int heavyson=0;
		size[u]=1;
		dep[u]=dep[fa[u]]+1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]) continue;
			fa[v]=u;
			dfs1(v);
			size[u]+=size[v];
			if(size[v]>size[heavyson]) heavyson=v;
		}
		son[u]=heavyson;
    }

    void dfs2(int u,int ance)
    {
		dfn[u]=++dfs_clock;
		top[u]=ance;
		if(son[u]) dfs2(son[u],ance);
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u]||v==son[u]) continue;
			dfs2(v,v);
		}
    }

    struct node
    {
		int l,r,sum,tag;
    }tree[N*4];

    void build(int root,int lt,int rt)
    {
		tree[root].l=lt,tree[root].r=rt;
		if(lt==rt) return;
		int mid=(lt+rt)>>1;
		build(root*2,lt,mid);
		build(root*2+1,mid+1,rt);
    }

    void update(int root)
    {
		tree[root].sum=(tree[root*2].sum+tree[root*2+1].sum)%p;
    }

    void pushdown(int root)
    {
		int lt=tree[root].l,rt=tree[root].r,mid=(lt+rt)>>1;
		int tag=tree[root].tag;
		if(!tag) return;
		node &ll=tree[root*2],&rr=tree[root*2+1];
		ll.sum=(ll.sum+tag*(mid-lt+1))%p;
		rr.sum=(rr.sum+tag*(rt-mid))%p;
		ll.tag=(ll.tag+tag)%p,rr.tag=(rr.tag+tag)%p;
		tree[root].tag=0;
    }

    void add(int root,int s,int e,int val)
    {
		int lt=tree[root].l,rt=tree[root].r;
		if(s<=lt&&rt<=e)
		{
			tree[root].sum=(tree[root].sum+val*(rt-lt+1))%p;
			tree[root].tag=(tree[root].tag+val)%p;
			return;
		}
		pushdown(root);
		int mid=(lt+rt)>>1;
		if(e<=mid) add(root*2,s,e,val);
		else if(mid<s) add(root*2+1,s,e,val);
		else add(root*2,s,mid,val),add(root*2+1,mid+1,e,val);
		update(root);
    }

    int ask(int root,int s,int e)
    {
		int lt=tree[root].l,rt=tree[root].r;
		if(s<=lt&&rt<=e) return tree[root].sum%p;
		pushdown(root);
		int mid=(lt+rt)>>1;
		if(e<=mid) return ask(root*2,s,e)%p;
		else if(s>mid) return ask(root*2+1,s,e)%p;
		else return (ask(root*2,s,mid)+ask(root*2+1,mid+1,e))%p;
    }

    void work()
    {
		n=read(),m=read();
		for(int i=2;i<=n;i++)
		{
			int x=read();
			add(x+1,i),add(i,x+1);
		}
		dfs1(1);
		dfs2(1,1);
		build(1,1,n);
		for(int i=1;i<=m;i++)
		{
			int l=read(),r=read(),z=read();
			z++;//全部都要+1
			q[l].push_back((query){i,z,-1});
			q[r+1].push_back((query){i,z,1});
		}
		int x,y;
		for(int i=1;i<=n;i++)
		{
			x=i,y=1;
			while(top[x]!=top[y])
			{
				if(dep[top[x]]<dep[top[y]]) swap(x,y);
				add(1,dfn[top[x]],dfn[x],1);
				x=fa[top[x]];
			}
			if(dep[x]>dep[y]) swap(x,y);
			add(1,dfn[x],dfn[y],1);
			for(int j=0;j<q[i].size();j++)
			{
				query ques=q[i][j];
				x=ques.node,y=1;
				int sum=0;
				while(top[x]!=top[y])
				{
					if(dep[top[x]]<dep[top[y]]) swap(x,y);
					sum=(sum+ask(1,dfn[top[x]],dfn[x]))%p;
					x=fa[top[x]];
				}
				if(dep[x]>dep[y]) swap(x,y);
				sum=(sum+ask(1,dfn[x],dfn[y]))%p;
				ans[ques.id]=(ans[ques.id]+ques.tag*sum+p)%p;
			}
		}
		for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
