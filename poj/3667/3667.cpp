#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
struct node
{
	int l,r,len,tag,lm,rm,mx;
}tree[50010*4];

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	tree[root].len=tree[root].lm=tree[root].rm=tree[root].mx=rt-lt+1;
	if(lt==rt) return;
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
}

void update(int root)
{
	if(tree[root*2].mx==tree[root*2].len)
		tree[root].lm=tree[root*2].len+tree[root*2+1].lm;
	else tree[root].lm=tree[root*2].lm;
	if(tree[root*2+1].mx==tree[root*2+1].len)
		tree[root].rm=tree[root*2+1].len+tree[root*2].rm;
	else tree[root].rm=tree[root*2+1].rm;
	tree[root].mx=max(tree[root*2].rm+tree[root*2+1].lm,max(tree[root*2].mx,tree[root*2+1].mx));
}

void pushdown(int root)
{
	int val=tree[root].tag;
	tree[root].tag=0;
	if(val==0||tree[root].l==tree[root].r) return;
	if(val==1)
	{
		tree[root*2].lm=tree[root*2].rm=tree[root*2].mx=tree[root*2].len;
		tree[root*2+1].lm=tree[root*2+1].rm=tree[root*2+1].mx=tree[root*2+1].len;
		tree[root*2].tag=tree[root*2+1].tag=val;
	}
	else
	{
		tree[root*2].lm=tree[root*2].rm=tree[root*2].mx=0;
		tree[root*2+1].lm=tree[root*2+1].rm=tree[root*2+1].mx=0;
		tree[root*2].tag=tree[root*2+1].tag=val;
	}
}

void change(int root,int s,int e,int val)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e)
	{
		if(val==1) tree[root].lm=tree[root].rm=tree[root].mx=tree[root].len;
		else tree[root].lm=tree[root].rm=tree[root].mx=0;
		tree[root].tag=val;
		return;
	}
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(e<=mid) change(root*2,s,e,val);
	else
	{
		if(s>mid) change(root*2+1,s,e,val);
		else
		{
			change(root*2,s,mid,val);
			change(root*2+1,mid+1,e,val);
		}
	}
	update(root);
}

int ask(int root,int num)
{
	int lt=tree[root].l,rt=tree[root].r,mid=(lt+rt)>>1;
	if(tree[root].mx<num) return -1;
	if(tree[root].lm>=num) return lt;
	pushdown(root);
	int ans=ask(root*2,num);
	if(ans==-1)
	{
		if(num<=tree[root*2].rm+tree[root*2+1].lm) return mid-tree[root*2].rm+1;
		else ans=ask(root*2+1,num);
	}
	return ans;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	int opt,x,y;
	while(m--)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d",&x);
			if(tree[1].mx<x) printf("0\n");
			else
			{
				int fir=ask(1,x);
				printf("%d\n",fir);
				change(1,fir,fir+x-1,2);
			}
		}
		else {scanf("%d%d",&x,&y);change(1,x,x+y-1,1);}
	}
	return 0;
}
