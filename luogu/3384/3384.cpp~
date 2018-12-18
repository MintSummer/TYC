#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN=1e5+10;
int cnt=0,Head[MAXN],num=0;
int size[MAXN],fa[MAXN],dep[MAXN],son[MAXN],top[MAXN],dfn[MAXN];
LL n,m,r,P;
LL a[MAXN],w[MAXN];

struct edge
{
	int to,next;
}E[MAXN*2];

struct node
{
	int l,r;
	LL sum,tag;
}tree[MAXN*4];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

void dfs1(int u)
{
	int heavyson=0,v;
	dep[u]=dep[fa[u]]+1;
	size[u]=1;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
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
	dfn[u]=++num;
	top[u]=ance;
	w[num]=a[u];
	if(son[u]) dfs2(son[u],ance);
	int v;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	if(lt==rt) {tree[root].sum=w[lt]%P;return;}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
	tree[root].sum=(tree[root*2].sum+tree[root*2+1].sum)%P;
}

void pushdown(int root)
{
	int lt=tree[root].l,rt=tree[root].r,mid=(lt+rt)>>1;
	int tag=tree[root].tag;
	node &ls=tree[root*2],&rs=tree[root*2+1];
	ls.sum=(ls.sum+tag*(mid-lt+1))%P;
	rs.sum=(rs.sum+tag*(rt-mid))%P;
	ls.tag=(ls.tag+tag)%P;
	rs.tag=(rs.tag+tag)%P;
	tree[root].tag=0;
}

void add(int root,int s,int e,int val)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e)
	{
		tree[root].sum=(tree[root].sum+(rt-lt+1)*val)%P;
		tree[root].tag=(tree[root].tag+val)%P;
		return;
	}
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(e<=mid) add(root*2,s,e,val);
	else
	{
		if(mid<s) add(root*2+1,s,e,val);
		else
		{
			add(root*2,s,mid,val);
			add(root*2+1,mid+1,e,val);
		}
	}
	tree[root].sum=(tree[root*2].sum+tree[root*2+1].sum)%P;
}

int ask(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) return tree[root].sum%P;
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(e<=mid) return ask(root*2,s,e)%P;
	else
	{
		if(s>mid) return ask(root*2+1,s,e)%P;
		else return (ask(root*2,s,mid)+ask(root*2+1,mid+1,e))%P;
	}
}

int main()
{
	//freopen("3384.in","r",stdin);
	//freopen("3384.out","w",stdout);
	scanf("%lld%lld%lld%lld",&n,&m,&r,&P);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	int u,v;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs1(r);
	dfs2(r,r);
	build(1,1,n);
	int opt,x,y,z;
	while(m--)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&x,&y,&z);
			while(top[x]!=top[y])
			{
				if(dep[top[x]]<dep[top[y]]) swap(x,y);
				add(1,dfn[top[x]],dfn[x],z);
				x=fa[top[x]];
			}
			if(dep[x]>dep[y]) swap(x,y);
			add(1,dfn[x],dfn[y],z);
			continue;
		}
		if(opt==2)
		{
			LL ans=0;
			scanf("%d%d",&x,&y);
			while(top[x]!=top[y])
			{
				if(dep[top[x]]<dep[top[y]]) swap(x,y);
				ans=(ans+ask(1,dfn[top[x]],dfn[x]))%P;
				x=fa[top[x]];
			}
			if(dep[x]>dep[y]) swap(x,y);
			ans=(ans+ask(1,dfn[x],dfn[y]))%P;
			printf("%lld\n",ans);
			continue;
		}
		if(opt==3) 
		{
			scanf("%d%d",&x,&z);
			add(1,dfn[x],dfn[x]+size[x]-1,z);
			continue;
		}
		scanf("%d",&x);
		printf("%lld\n",(ask(1,dfn[x],dfn[x]+size[x]-1))%P);
	}
	return 0;
}
