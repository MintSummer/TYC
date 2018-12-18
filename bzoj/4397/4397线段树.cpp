//这是某个名叫TYC的菜鸡生生地把前缀和写成了线段书……
#include<bits/stdc++.h>
using namespace std;
int num[100010],ans[4];

struct node 
{
	int l,r,sum[4];
}tree[100010*4];

inline void update(int root)
{
	for(int i=1;i<=3;i++)
 		tree[root].sum[i]=tree[root*2].sum[i]+tree[root*2+1].sum[i];
}

void build(int root,int lt,int rt)
{
	tree[root].l=lt,tree[root].r=rt;
	if(lt==rt) {tree[root].sum[num[lt]]=1;return;}
	int mid=(lt+rt)>>1;
	build(root*2,lt,mid);
	build(root*2+1,mid+1,rt);
	update(root);
}

void ask(int root,int s,int e)
{
	int lt=tree[root].l,rt=tree[root].r;
	if(s<=lt&&rt<=e)
	{
		for(int i=1;i<=3;i++) ans[i]+=tree[root].sum[i];
		return;
	}
	int mid=(lt+rt)>>1;
	if(e<=mid) ask(root*2,s,e);
	else
	{
		if(s>mid) ask(root*2+1,s,e);
		else
		{
			ask(root*2,s,mid);
			ask(root*2+1,mid+1,e);
		}
	}
}

int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	build(1,1,n);
	int a,b;
	while(q--)
	{
		scanf("%d%d",&a,&b);
		ans[1]=0,ans[2]=0,ans[3]=0;
		ask(1,a,b);
		printf("%d %d %d\n",ans[1],ans[2],ans[3]);
	}
	return 0;
}
