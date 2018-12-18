#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=100010;
int n,cnt=0,apple[MAXN],Head[MAXN];
int dfn[MAXN],out[MAXN],num=0,ans=0,duiying[MAXN];

struct edge
{
	int to,next;
}E[MAXN*2];

struct T
{
	int l,r,sum;
}tree[MAXN*4];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

inline void update(int root)
{
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

void dfs(int u,int fa)
{
	dfn[u]=++num;
	duiying[num]=u;
	int v;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(v==fa) continue;
		dfs(v,u);
	}
	out[u]=num;
}

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	if(lt==rt) {tree[root].sum=1;return;}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
	update(root);
}

void change(int root,int pos,int x)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(lt==pos&&rt==pos) {tree[root].sum=x;return;}
	int mid=(lt+rt)>>1;
	if(pos<=mid) change(root*2,pos,x);
	else if(pos>mid) change(root*2+1,pos,x);
	update(root);
}

void search(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) {ans+=tree[root].sum;return;}
	int mid=(lt+rt)>>1;
	if(e<=mid) search(root*2,s,e);
	else
	{
		if(s>mid) search(root*2+1,s,e);
		else
		{
			search(root*2,s,mid);
			search(root*2+1,mid+1,e);
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) apple[i]=1;
	int a,b;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs(1,0);
	int m,x;
	char ch[15];
	build(1,1,n);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%s%d",ch,&x);
		if(ch[0]=='C') 
		{
			apple[x]=apple[x]^1;
			change(1,dfn[x],apple[x]);
		}
		else
		{
			ans=0;
			search(1,dfn[x],out[x]);
			printf("%d\n",ans);
		}
	}
	return 0;
}
