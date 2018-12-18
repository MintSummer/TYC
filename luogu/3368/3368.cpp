//线段树，T了一个点 
#include<bits/stdc++.h>
using namespace std;
const int MAXN=500010;
int n,m,a[MAXN];

struct node
{
	int l,r,sum,tag;
}tree[MAXN*4];

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	if(lt==rt) {tree[root].sum=a[lt];return;}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid),build(root*2+1,mid+1,rt);
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

void pushdown(int root)
{
	if(!tree[root].tag) return;
	int tag=tree[root].tag;
	int lt=tree[root].l,rt=tree[root].r,mid=(lt+rt)>>1;
	node &ll=tree[root*2],&rr=tree[root*2+1];
	ll.tag+=tag,rr.tag+=tag;
	ll.sum+=tag*(mid-lt+1),rr.sum+=tag*(rt-mid);
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

int ask(int root,int x)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(lt==x&&rt==x) return tree[root].sum;
	pushdown(root);
	int mid=(lt+rt)>>1;
	if(x<=mid) return ask(root*2,x);
	else return ask(root*2+1,x);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	int opt,x,y,k;
	while(m--)
	{
		scanf("%d",&opt);
		if(opt==1) scanf("%d%d%d",&x,&y,&k),add(1,x,y,k);
		else scanf("%d",&x),printf("%d\n",ask(1,x));
	}
	return 0;
}
