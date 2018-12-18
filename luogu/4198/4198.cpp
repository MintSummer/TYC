#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

namespace  TYC
{
    const int MAXN=100010*4;
    int n,m,cnt[MAXN];//cnt记区间内高度严格递增的个数
    double mx[MAXN];

    inline int read()
    {
		int x=0;char ch=getchar();
		while(!isdigit(ch)) ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return x;
    }

    int count(int root,int l,int r,double k)//在l到r区间中,高度大于k的才能看见
    {
		if(l>=r) return mx[root]>k;
		int mid=(l+r)>>1;
		if(mx[root<<1]<=k) return count(root<<1|1,mid+1,r,k);//左边都看不见,只算右边>k的
		else return cnt[root]-cnt[root<<1]+count(root<<1,l,mid,k);
		//cnt[x]中原本就算了右边比左边最高的还高的建筑的个数,就可以不算右边的,只算左边>k的
    }

    void change(int root,int l,int r,int pos,double k)
    {
		if(l>=r)
		{
			mx[root]=k,cnt[root]=1;
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid)  change(root<<1,l,mid,pos,k);
		else change(root<<1|1,mid+1,r,pos,k);
		mx[root]=max(mx[root<<1],mx[root<<1|1]);
		cnt[root]=cnt[root<<1]+count(root<<1|1,mid+1,r,mx[root<<1]);//左边的不影响,只算右边被左边影响了的
    }

    void work()
    {
		n=read(),m=read();
		while(m--)
		{
			int x=read(),y=read();
			double k=(double)y/x;//比较斜率
			change(1,1,n,x,k);
			printf("%d\n",cnt[1]);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
