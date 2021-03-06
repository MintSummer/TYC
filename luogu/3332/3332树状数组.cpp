//Time:1128ms 
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    #define int long long
    #define lowbit(x) x&(-x)
    const int MAXN=50010;
    int n,m,ans[MAXN],ques[MAXN],s1[MAXN],s2[MAXN];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct question
    {
		int opt,l,r,id;
		int val;
    }a[MAXN],ql[MAXN],qr[MAXN];

    void add(int *x,int pos,int val)
    {
	    for(int i=pos;i<=n;i+=lowbit(i)) x[i]+=val;
    }

    void add_both(int l,int r,int val)
    {
	    add(s1,l,val),add(s1,r+1,-val);
	    add(s2,l,val*l),add(s2,r+1,-val*(r+1));
    }

    int ask(int pos)
    {
		if(pos==0) return 0;
		int sum1=0,sum2=0;
		for(int i=pos;i;i-=lowbit(i)) sum1+=s1[i],sum2+=s2[i];
		return sum1*(pos+1)-sum2;
    }

    int query(int l,int r)
    {
	    return ask(r)-ask(l-1);
    }

    void solve(int l,int r,int L,int R)//lr是询问,LR是值
    {
		if(l>r||L>R) return;
		if(L==R) 
		{
			for(int i=l;i<=r;i++)
			    if(a[i].opt==2) ans[a[i].id]=n-L+1;
			return;
		}
		int Mid=(L+R)>>1;
		int lt=0,rt=0;
		for(int i=l;i<=r;i++)
		{
			if(a[i].opt==1)
			{
				if(a[i].val>Mid) qr[++rt]=a[i];
				else ql[++lt]=a[i],add_both(a[i].l,a[i].r,1);
			}
			else
			{
				int num=query(a[i].l,a[i].r);
				if(a[i].val<=num) ql[++lt]=a[i];
				else a[i].val-=num,qr[++rt]=a[i];
			}
		}
		for(int i=1;i<=lt;i++)
			if(ql[i].opt==1) add_both(ql[i].l,ql[i].r,-1);
		for(int i=1;i<=lt;i++) a[l+i-1]=ql[i];
		for(int i=1;i<=rt;i++) a[l+lt+i-1]=qr[i];
		solve(l,l+lt-1,L,Mid);
		solve(l+lt,r,Mid+1,R);
    }

    void work()
    {
		n=read(),m=read();	
		for(int i=1;i<=m;i++)
		{
			int opt=read(),l=read(),r=read();
			int val=read();
			a[i]=(question){opt,l,r,i,val};
			if(opt==1) a[i].val=n-val+1;//防止数组越界
			ques[i]=(opt==2);
		}
		solve(1,m,1,n<<1);
		for(int i=1;i<=m;i++) 
			if(ques[i]) printf("%lld\n",ans[i]);
    }
}

signed main()
{
    TYC::work();
    return 0;
}
