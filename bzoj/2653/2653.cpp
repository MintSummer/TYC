//https://blog.csdn.net/clove_unique/article/details/53587455
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=20010;

namespace Tree
{
    int cnt,ls[N*20],rs[N*20],sum[N*20],lmax[N*20],rmax[N*20];

    void update(int root)
    {
		int l=ls[root],r=rs[root];
		sum[root]=sum[l]+sum[r];
		lmax[root]=max(lmax[l],sum[l]+lmax[r]);
		rmax[root]=max(rmax[r],sum[r]+rmax[l]);
    }

    void build(int &root,int l,int r)
    {
		root=++cnt;
		if(l==r)
		{
			sum[root]=lmax[root]=rmax[root]=1;
			return;
		}
		int mid=(l+r)>>1;
		build(ls[root],l,mid);
		build(rs[root],mid+1,r);
		update(root);
    }

    void change(int &root,int last,int l,int r,int x)
    {
		root=++cnt;
		sum[root]=sum[last],ls[root]=ls[last],rs[root]=rs[last];
		if(l==r)
		{
			sum[root]=-1,lmax[root]=0,rmax[root]=0;//可以不选
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) change(ls[root],ls[last],l,mid,x);
		else change(rs[root],rs[last],mid+1,r,x);
		update(root);
    }

    int Sum(int root,int l,int r,int s,int e)
    {
		if(s<=l&&r<=e) return sum[root];
		int mid=(l+r)>>1;
		if(e<=mid) return Sum(ls[root],l,mid,s,e);
		else if(s>mid) return Sum(rs[root],mid+1,r,s,e);
		return Sum(ls[root],l,mid,s,e)+Sum(rs[root],mid+1,r,s,e);
    }

    int Left(int root,int l,int r,int s,int e)
    {
		if(s<=l&&r<=e) return lmax[root];
		int mid=(l+r)>>1;
		if(e<=mid) return Left(ls[root],l,mid,s,e);
		else if(s>mid) return Left(rs[root],mid+1,r,s,e);
		return max(Left(ls[root],l,mid,s,e),
			Sum(ls[root],l,mid,s,mid)+Left(rs[root],mid+1,r,s,e));
    }

    int Right(int root,int l,int r,int s,int e)
    {
		if(s<=l&&r<=e) return rmax[root];
		int mid=(l+r)>>1;
		if(e<=mid) return Right(ls[root],l,mid,s,e);
		else if(s>mid) return Right(rs[root],mid+1,r,s,e);
		return max(Right(rs[root],mid+1,r,s,e),
			Sum(rs[root],mid+1,r,mid+1,e)+Right(ls[root],l,mid,s,e));//不能直接用sum[rs],还有e的边界
    }
}

namespace TYC
{
    using namespace Tree;
    int n,a,b,c,d,root[N],tmp[10];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct node
    {
		int val,id;
		bool operator < (const node &g) const
		{
			return val<g.val;
		}
    }x[N];

    bool check(int x)//x为中位数
    {
		if(( a==b ? 0 : Right(root[x],1,n,a,b-1) ) + 
			        Sum(root[x],1,n,b,c) + 
		   ( c==d ? 0 : Left(root[x],1,n,c+1,d) ) >= 0 ) return true;//值最大的区间
		return false;
    }

    int find()
    {
		int l=1,r=n,mid,ans;
		while(l<=r) 
		{
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		return ans;
    }

    void work()
    {
		n=read();
		for(int i=1;i<=n;i++) x[i]=(node){read(),i};
		sort(x+1,x+1+n);
		build(root[1],1,n);
		for(int i=2;i<=n;i++)
			change(root[i],root[i-1],1,n,x[i-1].id);
		int m=read(),ans=0;
		while(m--)
		{
			a=read(),b=read(),c=read(),d=read();
			tmp[0]=(a+ans)%n,tmp[1]=(b+ans)%n,tmp[2]=(c+ans)%n,tmp[3]=(d+ans)%n;
			sort(tmp,tmp+4);
			a=tmp[0]+1,b=tmp[1]+1,c=tmp[2]+1,d=tmp[3]+1;
			ans=x[find()].val;
			printf("%d\n",ans);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
