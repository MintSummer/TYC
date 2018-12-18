#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,q,a[50010],amx,amn;
struct edge
{
	int ro,l,r,mx,mn;
}tree[50010*10];

void build(int root,int lt,int rt)
{
	tree[root].l=lt;
	tree[root].r=rt;
	if(lt==rt)
	  {
	  	tree[root].mx=a[lt];
	  	tree[root].mn=a[lt];
	  }
	else
	  {
	  	int mid=(lt+rt)/2;
	  	build(2*root,lt,mid);
	  	build(2*root+1,mid+1,rt);
	  	tree[root].mx=max(tree[root*2].mx,tree[root*2+1].mx);
	  	tree[root].mn=min(tree[root*2].mn,tree[root*2+1].mn);
	  }
}

void find(int now,int s,int e)
{
	if(s==tree[now].l&&e==tree[now].r)
	  {
	  	amn=min(tree[now].mn,amn);
	  	amx=max(tree[now].mx,amx);
	  	return;
	  }
	int mid=(tree[now].l+tree[now].r)/2;
	if(e<=mid) find(2*now,s,e);
	else
	  {
	  	if(s>mid) find(2*now+1,s,e);
	  	else
	  	  {
	  	  	find(2*now,s,mid);
	  	  	find(2*now+1,mid+1,e);
	  	  }
	  }
	return;
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build(1,1,n);
	int x,y;
	while(q)
	  {
	  	q--;
	  	scanf("%d%d",&x,&y);
	  	amx=0,amn=0x3f3f3f3f;
	  	find(1,x,y);
	  	printf("%d\n",amx-amn);
	  }
	return 0;
}