#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
typedef long long ll;
int n,m,d[MAXN],w[MAXN],nxt[MAXN],last[MAXN];
/*
nxt[i]记录第i天的电影下次播放时间
枚举区间左端点，线段树维护每个位置作为右端点的答案
考虑l-r的左端点变为l+1
发现l到nxt[l]-1的答案减少w[f[l]]
而nxt[l]到nxt[nxt[l]]-1增加w[f[l]]
线段树维护，支持区间修改以及查询最大值
*/

struct node
{
	int l,r;
	ll mx,tag;
}tree[MAXN*4];

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	if(lt==rt) return;
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
}

void pushdown(int root)
{
	ll tag=tree[root].tag;
	int lt=tree[root].l,rt=tree[root].r,mid=(lt+rt)>>1;
	if(tag==0||lt==rt) return;
	node &ll=tree[root*2],&rr=tree[root*2+1];
	ll.mx+=tag,rr.mx+=tag;
	ll.tag+=tag,rr.tag+=tag;
	tree[root].tag=0;
}

void add(int root,int s,int e,ll val)
{
	pushdown(root);
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) 
	{
		tree[root].mx+=val;
		tree[root].tag=val;
		return;
	}
	int mid=(lt+rt)>>1;
	if(e<=mid) add(root*2,s,e,val);
	else if(s>mid) add(root*2+1,s,e,val);
	else add(root*2,s,mid,val),add(root*2+1,mid+1,e,val);
	tree[root].mx=max(tree[root*2].mx,tree[root*2+1].mx);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&d[i]);
	for(int i=1;i<=m;i++) scanf("%d",&w[i]);
	for(int i=n;i>=1;i--)
	{
		nxt[i]=last[d[i]];
		last[d[i]]=i;
	}
	build(1,1,n);
	for(int i=1;i<=m;i++)
		if(last[i]) 
		{
			if(!nxt[last[i]]) add(1,last[i],n,w[i]);
			else add(1,last[i],nxt[last[i]]-1,w[i]);
		}
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,tree[1].mx);
		int tmp=nxt[i];
		if(tmp)
		{
			add(1,i,tmp-1,-w[d[i]]);
			if(nxt[tmp]) add(1,tmp,nxt[tmp]-1,w[d[i]]);
			else add(1,tmp,n,w[d[i]]);
		}
		else add(1,i,n,-w[d[i]]);
	}
	printf("%lld",ans);
	return 0;
}
