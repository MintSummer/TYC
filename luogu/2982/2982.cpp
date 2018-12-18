#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,cnt=0,ans,Head[MAXN],reach[MAXN];
int dfn[MAXN],out[MAXN],num=0;

struct edge
{
	int to,next;
}E[MAXN*4];

struct 	T
{
	int l,r,sum,tag;
}tree[MAXN*4];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

void dfs(int u,int fa)
{
	dfn[u]=++num;
	int v;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(v==fa) continue;
		dfs(v,u);
	}
	out[u]=num;
}

inline void update(int root)
{
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	if(lt==rt)
	{
		tree[root].sum=0;
		tree[root].tag=0;
		return;
	}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
	update(root);
}

void pushdown(int root)
{
	int val=tree[root].tag;
	int lt=tree[root].l,rt=tree[root].r;
	int mid=(lt+rt)>>1; 
	if(val==0) return;
	tree[root*2].tag+=val;
	tree[root*2].sum+=(mid-lt+1)*val;
	tree[root*2+1].tag+=val;
	tree[root*2+1].sum+=(rt-mid)*val;
	tree[root].tag=0;
}

void change(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) 
	{
		tree[root].sum+=e-s+1;
		tree[root].tag++;
		return;
	}
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(e<=mid) change(root*2,s,e);
	else
	{
		if(s>mid) change(root*2+1,s,e);
		else
		{
			change(root*2,s,mid);
			change(root*2+1,mid+1,e);
		}
	}
	update(root);
}

void search(int root,int s)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(lt==s&&rt==s) {ans=tree[root].sum;return;}
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(s<=mid) search(root*2,s);
	else search(root*2+1,s);
}

int main()
{
	scanf("%d",&n);
	int a,b;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&reach[i]);
	dfs(1,0);
	build(1,1,n);
	int to;
	for(int i=1;i<=n;i++)
	{
		to=reach[i];
		search(1,dfn[to]);
		printf("%d\n",ans);
		change(1,dfn[to],out[to]);
	}
	return 0;
}
