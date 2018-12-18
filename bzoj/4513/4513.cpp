#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=500010;

int n,m,park[MAXN];
struct node
{
	int l,r,sum;
	int lm,rm,mx;
}tree[MAXN*4];

void update(int root)
{
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
	tree[root].lm=max(tree[root*2].lm,tree[root*2].sum+tree[root*2+1].lm);
	tree[root].rm=max(tree[root*2+1].rm,tree[root*2+1].sum+tree[root*2].rm);
	tree[root].mx=max(tree[root*2].rm+tree[root*2+1].lm,max(tree[root*2].mx,tree[root*2+1].mx));
}

void build(int root,int lt,int rt)
{
	if(lt>rt) return;
	tree[root].l=lt,tree[root].r=rt;
	if(lt==rt) 
	{
		tree[root].sum=tree[root].mx=tree[root].lm=tree[root].rm=park[lt];
		return;
	}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
	update(root);
}

void change(int root,int s,int val)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(lt>rt||lt>s||rt<s) return;
	if(s==lt&&s==rt) 
	{
		tree[root].sum=tree[root].mx=tree[root].lm=tree[root].rm=val;
		return;
	}
	int mid=(lt+rt)>>1;
	if(s<=mid) change(root*2,s,val);
	else change(root*2+1,s,val);
	update(root);
}

node search(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(lt>rt||lt>e||rt<s) return (node){0,0,-0x3f3f3f3f,0,0,0};
	if(s<=lt&&rt<=e) return tree[root];
	int mid=(lt+rt)>>1;
	if(e<=mid) return search(root*2,s,e);
	else if(s>mid) return search(root*2+1,s,e);
	else
	{
		node ls,rs,ans;
		ls=search(root*2,s,mid);
		rs=search(root*2+1,mid+1,e);
		ans.sum=ls.sum+rs.sum;
		ans.lm=max(ls.lm,ls.sum+rs.lm);
		ans.rm=max(rs.rm,rs.sum+ls.rm);
		ans.mx=max(ls.rm+rs.lm,max(ls.mx,rs.mx));
		return ans;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&park[i]);
	build(1,1,n);
	int opt,a,b;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&opt,&a,&b);
		if(opt==1)
		{
			if(a>b) swap(a,b);
			node ans=search(1,a,b);
			printf("%d\n",ans.mx);
		}
		else
		{
			park[a]=b;
			change(1,a,b);
		}
	}
	return 0;
}