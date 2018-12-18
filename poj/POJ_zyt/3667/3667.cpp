#include<algorithm>
#include<cstdio>
using namespace std;
struct node
{
	int len;
	int lm;
	int rm;
	int mm;
	int tag;
}tree[200010];
const int INF=0x3f3f3f3f;
int n,m;
inline void clear(node &a)
{
	a.lm=a.rm=a.mm=a.len;
}
inline void fill(node &a)
{
	a.lm=a.rm=a.mm=0;
}
inline void pushup(node &root,const node &lt,const node &rt)
{
	root.lm=lt.lm,root.rm=rt.rm;
	if(lt.lm==lt.len)root.lm+=rt.lm;
	if(rt.rm==rt.len)root.rm+=lt.rm;
	root.mm=max(lt.rm+rt.lm,max(lt.mm,rt.mm));
}
inline void pushdown(node &root,node &lt,node &rt)
{
	if(root.tag==0)
	{
		clear(lt),clear(rt);
		lt.tag=rt.tag=0;
	}
	if(root.tag==1)
	{
		fill(lt),fill(rt);
		lt.tag=rt.tag=1;
	}
	root.tag=-1;
}
void build(int root,int l,int r)
{
	if(l>r)return;
	int mid=(l+r)/2;
	tree[root].len=r-l+1;
	tree[root].tag=-1;
	clear(tree[root]);
	if(l==r)return;
	build(root*2+1,l,mid);
	build(root*2+2,mid+1,r);
}
void empty(int root,int l,int r,int ls,int rs)
{
	int mid=(l+r)/2;
	if(l>r||l>rs||r<ls)return;
	if(ls<=l&&r<=rs)
	{
		clear(tree[root]);
		tree[root].tag=0;
		return;
	}
	pushdown(tree[root],tree[root*2+1],tree[root*2+2]);
	empty(root*2+1,l,mid,ls,rs);
	empty(root*2+2,mid+1,r,ls,rs);
	pushup(tree[root],tree[root*2+1],tree[root*2+2]);
}

void change(int root,int l,int r,int ls,int rs)
{
	int mid=(l+r)/2;
	if(l>r||l>rs||r<ls)return;
	if(ls<=l&&r<=rs)
	{
		fill(tree[root]);
		tree[root].tag=1;
		return;
	}
	pushdown(tree[root],tree[root*2+1],tree[root*2+2]);
	change(root*2+1,l,mid,ls,rs);
	change(root*2+2,mid+1,r,ls,rs);
	pushup(tree[root],tree[root*2+1],tree[root*2+2]);
}

int search(int root,int l,int r,int len)
{
	int mid=(l+r)/2,ans;
	if(l>r||tree[root].mm<len)return -1;
	if(tree[root].lm>=len)return l;
	pushdown(tree[root],tree[root*2+1],tree[root*2+2]);
	ans=search(root*2+1,l,mid,len);
	if(ans==-1)
		if(tree[root*2+1].rm+tree[root*2+2].lm>=len)
			ans=mid-tree[root*2+1].rm+1;
		else ans=search(root*2+2,mid+1,r,len);
	return ans;
}

int main(void)
{
	scanf("%d%d",&n,&m);
	build(0,1,n);
	while(m--)
	{
		int a,b,c;
		scanf("%d%d",&a,&b);
		if(a==1)
		{
			int ans=search(0,1,n,b);
			if(ans==-1)printf("0\n");
			else printf("%d\n",ans),change(0,1,n,ans,ans+b-1);
		}
		else
		{
			scanf("%d",&c);
			empty(0,1,n,b,b+c-1);
		}
	}
	return 0;
}
