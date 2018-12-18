#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=5e4+10;
    int n,Q,block,ans,a[MAXN],belong[MAXN],Ans[MAXN],c[MAXN],tmp[MAXN];
    map<int,int> id;

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct query
    {
		int id,l,r;
		bool operator < (const query &a) const
		{
			return belong[l]==belong[a.l]?r<a.r:l<a.l;
		}
    }q[MAXN];

    int lowbit(int x){return x&(-x);}

    void add(int x,int d)
    {
		for(;x<=n;x+=lowbit(x)) c[x]+=d;
    }

    int ques(int x)
    {
		int sum=0;
		for(;x;x-=lowbit(x)) sum+=c[x];
		return sum;
    }

    void change(int x,int d,int tag)
    {
		x=a[x];
		if(!tag) ans+=d*ques(x-1);
		else ans+=d*(ques(n)-ques(x));
		add(x,d);
    }

    void work()
    {
		n=read();
		block=sqrt(n);
		for(int i=1;i<=n;i++) 
		{
			a[i]=tmp[i]=read();
			belong[i]=(i-1)/block+1;
		}
		sort(tmp+1,tmp+1+n);
		for(int i=1;i<=n;i++)
			a[i]=lower_bound(tmp+1,tmp+1+n,a[i])-tmp;
		Q=read();
		for(int i=1;i<=Q;i++)
		{
			q[i].id=i;
			q[i].l=read(),q[i].r=read();
		}
		sort(q+1,q+1+Q);
		int lt=1,rt=0;
		for(int i=1;i<=Q;i++)
		{
			while(lt<q[i].l) change(lt,-1,0),lt++;
			while(lt>q[i].l) change(lt-1,1,0),lt--;
			while(rt<q[i].r) change(rt+1,1,1),rt++;
			while(rt>q[i].r) change(rt,-1,1),rt--;
			Ans[q[i].id]=ans;
		}
		for(int i=1;i<=Q;i++) printf("%d\n",Ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
