#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
const int inf=0x3f3f3f3f;
int n,m;
int a[MAXN],sg[MAXN],vis[MAXN],nxt[MAXN],last[MAXN],ans[MAXN];

struct ques
{
	int lt,rt,id;
}q[MAXN];

struct node
{
	int l,r,mn;
}tree[MAXN*4];//线段树进行区间修改

bool cmp(ques A,ques B)
{
	return A.lt<B.lt;
}

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	tree[root].mn=inf;
	if(lt==rt) {tree[root].mn=sg[lt];return;}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
}

void pushdown(int root)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(lt==rt) return;
	tree[root*2].mn=min(tree[root*2].mn,tree[root].mn);
	tree[root*2+1].mn=min(tree[root*2+1].mn,tree[root].mn);
}

void change(int root,int s,int e,int val)
{
	if(tree[root].mn!=inf) pushdown(root);
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) {tree[root].mn=min(tree[root].mn,val);return;}
	int mid=(lt+rt)>>1;
	if(e<=mid) change(root*2,s,e,val);
	else if(s>mid) change(root*2+1,s,e,val);
	else change(root*2,s,mid,val),change(root*2+1,mid+1,e,val);
}

int ask(int root,int s)
{
	if(tree[root].mn!=inf) pushdown(root);
	int lt=tree[root].l,rt=tree[root].r;
	if(s==lt&&rt==s) return tree[root].mn;
	int mid=(lt+rt)>>1;
	if(s<=mid) return ask(root*2,s);
	return ask(root*2+1,s);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int tmp=0;
	for(int i=1;i<=n;i++)
	{
		vis[a[i]]=1;
		if(a[i]==tmp)
			while(vis[tmp]) tmp++;
		sg[i]=tmp;
	}//预处理1到各个数的mex
	build(1,1,n);
	for(int i=n;i>0;i--)
	{
		nxt[i]=last[a[i]];
		last[a[i]]=i;
	}//记录下一个a[i]出现的位置
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].lt,&q[i].rt);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	//问题离散化，将ans集中在右节点上，处理左节点的递增
	int now=1;
	for(int i=1;i<=m;i++)
	{
		while(now<q[i].lt)
		{
			if(!nxt[now]) nxt[now]=n+1;
			change(1,now,nxt[now]-1,a[now]);
			now++; 
		}
		ans[q[i].id]=ask(1,q[i].rt);
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
