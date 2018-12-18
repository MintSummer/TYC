//把删除变成倒着插入,考虑对于(tim,pos,val)的(t0>t1&&p0<pos1&&v0>v1)的数量->三维偏序
//开longlong 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	typedef long long ll;
    #define lowbit(x) x&(-x)
    const int N=200010;
    int n,m,pos[N],del[N];
    ll ans[N],c[N];

    struct ques
    {
		int tim,pos,val,ans;
    }q[N];

    bool cmptim(const ques &a,const ques &b)
    {
		return a.tim<b.tim;
    }

    bool cmp1(const ques &a,const ques &b)
    {
		return a.pos<b.pos;
    }

    bool cmp2(const ques &a,const ques &b)
    {
		return a.pos>b.pos;
    }

    void add(int x,int val)
    {
		for(;x<=n;x+=lowbit(x)) c[x]+=val;
    }

    ll query(int x)
    {
		ll sum=0;
		for(;x;x-=lowbit(x)) sum+=c[x];
		return sum;
    }

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void cdq(int l,int r)
    {
		if(l==r) return;
		int mid=(l+r)>>1;
		cdq(l,mid),cdq(mid+1,r);
		
		sort(q+l,q+mid+1,cmp1);
		sort(q+mid+1,q+r+1,cmp1);
		int i=l;
		for(int j=mid+1;j<=r;j++)
		{
			while(i<=mid&&q[i].pos<q[j].pos)
				add(q[i].val,1),i++;
			ans[q[j].tim]+=i-l-query(q[j].val);
		}
		for(i--;i>=l;i--) add(q[i].val,-1);
		
		sort(q+l,q+mid+1,cmp2);
		sort(q+mid+1,q+r+1,cmp2);
		i=l;
		for(int j=mid+1;j<=r;j++)
		{
			while(i<=mid&&q[i].pos>q[j].pos)
				add(q[i].val,1),i++;
			ans[q[j].tim]+=query(q[j].val);
		}
		for(i--;i>=l;i--) add(q[i].val,-1);
    }

    void work()
    {	
		n=read(),m=read();
		for(int i=1;i<=n;i++) pos[read()]=i;
		int tot=0,tmp=n;
		for(int i=1;i<=m;i++)
		{
			int x=read();
			q[++tot]=(ques){tmp--,pos[x],x,0};
			del[x]=1;
		}
		tmp=n-m;
		for(int i=1;i<=n;i++)
			if(!del[i]) q[++tot]=(ques){tmp--,pos[i],i,0};
		sort(q+1,q+tot+1,cmptim);
		cdq(1,n);
		for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
		for(int i=n;i>n-m;i--) printf("%lld\n",ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
