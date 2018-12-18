#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
#define lowbit(x) x&(-x)
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=2000010;
    int n;
    ll c[N],ans[10010];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct ques
    {
		int id,opt,x,y,val;
		bool operator < (const ques &a) const
		{
			return x<a.x;
		}
    }q[N],tmp[N];

    void add(int x,int val)
    {
		for(;x<=n;x+=lowbit(x)) c[x]+=val;
    }

    int query(int x)
    {
		int sum=0;
		for(;x;x-=lowbit(x)) sum+=c[x];
		return sum;
    }

    void cdq(int l,int r)
    {
		if(l==r) return;
		int mid=(l+r)>>1;
		cdq(l,mid),cdq(mid+1,r);
		sort(q+l,q+mid+1);
		sort(q+mid+1,q+r+1);
		int i=l;
		for(int j=mid+1;j<=r;j++)
		{
			while(i<=mid&&q[i].x<=q[j].x)
			{
				if(!q[i].opt) add(q[i].y,q[i].val);
				i++;
			}
			if(q[j].opt) q[j].val+=query(q[j].y);
		}
		for(i--;i>=l;i--) 
			if(!q[i].opt) add(q[i].y,-q[i].val);
    }

    void work()
    {
		int opt=read(),tot=0,num=0;
		n=read();
		for(int i=1;;i++)
		{
			opt=read();
			if(opt==3) break;
			else if(opt==1)
			{
				q[++tot].x=read(),q[tot].y=read(),q[tot].val=read();
				q[tot].id=tot,q[tot].opt=0;
			}
			else 
			{
				int x1=read(),y1=read(),x2=read(),y2=read();
				++num;
				q[++tot]=(ques){num,1,x2,y2,0};
				q[++tot]=(ques){num,-1,x1-1,y2,0};
				q[++tot]=(ques){num,-1,x2,y1-1,0};
				q[++tot]=(ques){num,1,x1-1,y1-1,0};
			}
		}
		cdq(1,tot);
		for(int i=1;i<=tot;i++)
			if(q[i].opt) ans[q[i].id]+=q[i].val*q[i].opt;
		for(int i=1;i<=num;i++) printf("%lld\n",ans[i]);
    }
}

int main()
{
    //freopen("4390.in","r",stdin);
    TYC::work();
    return 0;
}
