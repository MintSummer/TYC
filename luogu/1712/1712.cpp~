#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=800010;
    int n,m,tmp[MAXN*2];

    inline int read()
    {
		int x=0;char ch=getchar();
		while(!isdigit(ch)) ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return x;
    }

    struct Interval
    {
		int lt,rt,len;
		bool operator < (const Interval &a) const
		{
			return len<a.len;
		}
    }interval[MAXN*2];

    struct node
    {
		int l,r,mx,tag;//mx表示区间l到r中的点最多被覆盖的次数
    }tree[MAXN*4];

    void build(int root,int lt,int rt)
    {
		tree[root].l=lt,tree[root].r=rt;
		tree[root].mx=tree[root].tag=0;
		if(lt==rt) return;
		int mid=(lt+rt)>>1;
		build(root*2,lt,mid);
		build(root*2+1,mid+1,rt);
    }

    void update(int root)
    {
		tree[root].mx=max(tree[root*2].mx,tree[root*2+1].mx);
    }

    void pushdown(int root)
    {
		int tag=tree[root].tag;
		if(!tag) return;
		node &ll=tree[root*2],&rr=tree[root*2+1];
		ll.mx+=tag,rr.mx+=tag;
		ll.tag+=tag,rr.tag+=tag;
		tree[root].tag=0;
    }

    void add(int root,int s,int e,int val)
    {
		int lt=tree[root].l,rt=tree[root].r;
		if(s<=lt&&rt<=e) 
		{
			tree[root].mx+=val;
			tree[root].tag+=val;
			return;
		}
		pushdown(root);
		int mid=(lt+rt)>>1;
		if(e<=mid) add(root*2,s,e,val);
		else if(s>mid) add(root*2+1,s,e,val);
		else add(root*2,s,mid,val),add(root*2+1,mid+1,e,val);
		update(root);
    }

    void work()
    {
		n=read(),m=read();
		for(int i=1;i<=n;i++)
		{
			int l=read(),r=read();
			tmp[i*2-1]=l,tmp[i*2]=r;
			interval[i]=(Interval){l,r,r-l};
		}
		sort(tmp+1,tmp+n*2+1);
		int tot=unique(tmp+1,tmp+n*2+1)-tmp-1;//离散化
		for(int i=1;i<=n;i++) 
		{
			interval[i].lt=lower_bound(tmp+1,tmp+tot+1,interval[i].lt)-tmp;
			interval[i].rt=lower_bound(tmp+1,tmp+tot+1,interval[i].rt)-tmp;
		}
		sort(interval+1,interval+n+1);
		build(1,1,tot);
		int last=1,ans=-1;
		for(int i=1;i<=n;i++)
		{
			add(1,interval[i].lt,interval[i].rt,1);
			while(tree[1].mx==m)
			{
				add(1,interval[last].lt,interval[last].rt,-1);
				if(ans==-1) ans=interval[i].len-interval[last].len;
				else ans=min(ans,interval[i].len-interval[last].len);//interval已经按照len排序了
				last++;
			}
		}
		printf("%d",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
