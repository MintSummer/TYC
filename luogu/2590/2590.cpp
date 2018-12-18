#include<bits/stdc++.h>
using namespace std;
const int MAXN=30010;
int n,q,cnt=0,num=0;
int a[MAXN],Head[MAXN],w[MAXN];
int top[MAXN],son[MAXN],size[MAXN],dfn[MAXN],dep[MAXN],fa[MAXN];

struct edge
{
	int to,next;
}E[MAXN*2];

struct node
{
	int l,r,sum,mx;
}tree[MAXN*4];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
} 

int read()
{
	char ch;
	do{ch=getchar();}while(ch<='Z'&&ch>='A');
	if(ch=='E') return 1;
	if(ch=='X') return 2;
	return 3;
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
	dfn[u]=++num;
	w[num]=a[u];
	top[u]=t;
	if(son[u]) dfs2(son[u],t);
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
	if(lt==rt)
		{tree[root].sum=tree[root].mx=w[lt];return;}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
	tree[root].mx=max(tree[root*2].mx,tree[root*2+1].mx);
}

void change(int root,int s,int val)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(lt==s&&rt==s) 
		{tree[root].sum=tree[root].mx=val;return;}
	int mid=(lt+rt)>>1;
	if(s<=mid) change(root*2,s,val);
	else change(root*2+1,s,val);
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
	tree[root].mx=max(tree[root*2].mx,tree[root*2+1].mx); 
}

int getmax(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) return tree[root].mx;
	int mid=(lt+rt)>>1;
	if(e<=mid) return getmax(root*2,s,e);
	if(s>mid) return getmax(root*2+1,s,e);
	return max(getmax(root*2,s,mid),getmax(root*2+1,mid+1,e));
}
int ask(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) return tree[root].sum;
	int mid=(lt+rt)>>1;
	if(e<=mid) return ask(root*2,s,e);
	if(s>mid) return ask(root*2+1,s,e);
	return ask(root*2,s,mid)+ask(root*2+1,mid+1,e);
}

int main()
{
	scanf("%d",&n);
	int u,v;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	scanf("%d",&q);
	int a,b;
	char opt[10];
	while(q--)
	{
		scanf("%s%d%d",opt,&a,&b);
		if(opt[1]=='H') 
			{change(1,dfn[a],b);continue;}
		if(opt[1]=='M') 
		{
			int MX=-0x3f3f3f3f;
			while(top[a]!=top[b])
			{
				if(dep[top[a]]<dep[top[b]]) swap(a,b);
				MX=max(getmax(1,dfn[top[a]],dfn[a]),MX);
				a=fa[top[a]];
			}
			if(dep[a]>dep[b]) swap(a,b);
			MX=max(getmax(1,dfn[a],dfn[b]),MX);
			printf("%d\n",MX);
			continue;
		}
		int ans=0;
		while(top[a]!=top[b])
		{
			if(dep[top[a]]<dep[top[b]]) swap(a,b);
			ans+=ask(1,dfn[top[a]],dfn[a]);
			a=fa[top[a]];
		}
		if(dep[a]>dep[b]) swap(a,b);
		ans+=ask(1,dfn[a],dfn[b]);
		printf("%d\n",ans);
	}
	return 0;
}
