#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100010;
int n,m,cnt=0,num=0,Head[MAXN];
int w[MAXN],a[MAXN];
int son[MAXN],fa[MAXN],size[MAXN],dep[MAXN],top[MAXN],dfn[MAXN];

struct edge
{
	int to,next;
}E[MAXN*2];


struct node
{
	int l,r;
	ll sum,tag;
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
	int hs=0,v;
	size[u]=1;
	dep[u]=dep[fa[u]]+1;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs1(v);
		if(size[v]>size[hs]) hs=v;
		size[u]+=size[v];
	}
	son[u]=hs;
}

void dfs2(int u,int t)
{
	int v;
	top[u]=t;
	dfn[u]=++num;
	w[num]=a[u];
	if(son[u]) dfs2(son[u],t);
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
	if(lt==rt) {tree[root].sum=w[lt];return;}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

void pushdown(int root)
{
	int lt=tree[root].l,rt=tree[root].r,mid=(lt+rt)>>1;
	int tag=tree[root].tag;
	if(tag==0) return;
	node &ll=tree[root*2],&rr=tree[root*2+1];
	ll.sum+=tag*(mid-lt+1);
	rr.sum+=tag*(rt-mid);
	ll.tag+=tag,rr.tag+=tag;
	tree[root].tag=0;
}

void add(int root,int s,int e,int val)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) 
	{
		tree[root].sum+=val*(rt-lt+1);
		tree[root].tag+=val;
		return;
	}
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(e<=mid) add(root*2,s,e,val);
	else if(s>mid) add(root*2+1,s,e,val);
	else add(root*2,s,mid,val),add(root*2+1,mid+1,e,val);
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

ll ask(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) return tree[root].sum;
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(e<=mid) return ask(root*2,s,e);
	else if(s>mid) return ask(root*2+1,s,e);
	else return ask(root*2,s,mid)+ask(root*2+1,mid+1,e);
}

int main()
{
	//freopen("4034.in","r",stdin);
	//freopen("4034.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int u,v;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	int opt,x,z,y;
	while(m--)
	{
		y=1;
		scanf("%d%d",&opt,&x);
		if(opt==1)
		{
			scanf("%d",&z);
			add(1,dfn[x],dfn[x],z);
		}
		else if(opt==2)
		{
			scanf("%d",&z);
			add(1,dfn[x],dfn[x]+size[x]-1,z);
		}
		else 	
		{
			ll ans=0;
			while(top[x]!=top[y])
			{
				if(dep[top[x]]<dep[top[y]]) swap(x,y);
				ans+=ask(1,dfn[top[x]],dfn[x]);
				x=fa[top[x]];
			}
			if(dep[x]>dep[y]) swap(x,y);
			ans+=ask(1,dfn[x],dfn[y]);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
