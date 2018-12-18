#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN=100010;
int n,m;
LL a[MAXN];
//数据范围非负且小于10^9，下去整的话最多开到6次
//用flag记录这个区间是否已经为1或0（不用再开了），每个区间最多过六次,减少访问次数

struct node
{
	int l,r;
	LL sum;
	bool flag;
}tree[MAXN*4];

inline void update(int root)
{
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
	tree[root].flag=tree[root*2].flag&tree[root*2+1].flag;
}

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	if(lt==rt) 
	{
		tree[root].sum=a[lt];
		if(a[lt]<=1) tree[root].flag=1;		
		return;
	}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
	update(root);
}

LL ask(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e) return tree[root].sum;
	int mid=(lt+rt)>>1;
	if(e<=mid) return ask(root*2,s,e);
	else if(s>mid) return ask(root*2+1,s,e);
	else return ask(root*2,s,mid)+ask(root*2+1,mid+1,e);
}

void change(int root,int s,int e)
{
	if(tree[root].flag) return;
	int lt=tree[root].l,rt=tree[root].r;
	if(lt==s&&rt==s&&s==e)//访问次数少了就可以修改到点了
	{
		tree[root].sum=(LL)sqrt(tree[root].sum);
		if(tree[root].sum<=1) tree[root].flag=1;
		return;
	}
	int mid=(lt+rt)>>1;
	if(e<=mid) change(root*2,s,e);
	else if(s>mid) change(root*2+1,s,e);
	else change(root*2,s,mid),change(root*2+1,mid+1,e);
	update(root);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	build(1,1,n);
	scanf("%d",&m);
	int opt,x,y;
	while(m--)
	{
		scanf("%d%d%d",&opt,&x,&y);
		if(x>y) swap(x,y);
		if(opt==1) printf("%lld\n",ask(1,x,y));
		else change(1,x,y);
	}
	return 0;
}
