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
    const int N=2e5+10,inf=1e9;
    int n,m,ans[N],c[N];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct node
    {
		int x,pos;
		bool operator < (const node &a) const
		{
			return x<a.x;
		}
    }a[N];

    struct ques
    {
		int id,l,r,k;
    }q[N],ql[N],qr[N];

    void add(int x,int val)
    {
		for(int i=x;i<=n;i+=lowbit(i)) c[i]+=val;
    }

    int ask(int x)
    {
		int sum=0;
		for(int i=x;i;i-=lowbit(i)) sum+=c[i];
		return sum;
    }

    int query(int l,int r)
    {
		return ask(r)-ask(l-1);
    }

    void solve(int l,int r,int L,int R)
    {
		if(l>r) return;
		if(L==R)
		{
			for(int i=l;i<=r;i++) ans[q[i].id]=a[L].x;
			return;
		}
		int Mid=(L+R)>>1,cntl=0,cntr=0;
		for(int i=L;i<=Mid;i++) add(a[i].pos,1);
		for(int i=l;i<=r;i++)
		{
			int num=query(q[i].l,q[i].r);
			if(q[i].k<=num) ql[++cntl]=q[i];
			else q[i].k-=num,qr[++cntr]=q[i];
		}
		for(int i=L;i<=Mid;i++) add(a[i].pos,-1);
		for(int i=1;i<=cntl;i++) q[l+i-1]=ql[i];
		for(int i=1;i<=cntr;i++) q[l+cntl+i-1]=qr[i];
		solve(l,l+cntl-1,L,Mid);
		solve(l+cntl,r,Mid+1,R);
    }	

    void work()
    {
		n=read(),m=read();
		for(int i=1;i<=n;i++)
			a[i]=(node){read(),i};
		sort(a+1,a+1+n);
		for(int i=1;i<=m;i++)
			q[i]=(ques){i,read(),read(),read()};
		solve(1,m,1,n);
		for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
