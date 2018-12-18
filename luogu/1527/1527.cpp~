#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    #define lowbit(x) x&(-x)
    const int N=510,M=60010,inf=1e9;
    int n,m,ans[M],c[N][N];//二维树状数组c表示当前<=Matrix[Mid].val的数的个数
    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct node
    {
		int x,y,val;
		bool operator < (const node &a) const
		{
			return val<a.val;
		}
    }Matrix[N*N];

    struct question
    {
		int id,x1,y1,x2,y2,k;
    }a[M],ql[M],qr[M];

    inline void add(int x,int y,int val)
    {
		for(int i=x;i<=n;i+=lowbit(i))
			for(int j=y;j<=n;j+=lowbit(j))
				c[i][j]+=val;
    }

    inline int ask(int x,int y)
    {
		int sum=0;
		for(int i=x;i;i-=lowbit(i))
			for(int j=y;j;j-=lowbit(j))
				sum+=c[i][j];
		return sum;
    }

    inline int query(question d)
    {
		int x1=d.x1,y1=d.y1,x2=d.x2,y2=d.y2;
		return ask(x2,y2)-ask(x1-1,y2)-ask(x2,y1-1)+ask(x1-1,y1-1);
    }

    void solve(int l,int r,int L,int R)//LR表示按点值排序后第L到第R个点,代表答案的范围
    {
		if(l>r||L>R) return;
		if(L==R)
		{
			for(int i=l;i<=r;i++) ans[a[i].id]=Matrix[L].val;
			return;
		}
		int Mid=(L+R)>>1,cntl=0,cntr=0;
		for(int i=L;i<=Mid;i++)
			add(Matrix[i].x,Matrix[i].y,1);
		for(int i=l;i<=r;i++)
		{
			int num=query(a[i]);
			if(a[i].k<=num) ql[++cntl]=a[i];
			else a[i].k-=num,qr[++cntr]=a[i];
		}
		for(int i=L;i<=Mid;i++)
			add(Matrix[i].x,Matrix[i].y,-1);
		for(int i=1;i<=cntl;i++) a[l+i-1]=ql[i];
		for(int i=1;i<=cntr;i++) a[l+cntl+i-1]=qr[i];
		solve(l,l+cntl-1,L,Mid);
		solve(l+cntl,r,Mid+1,R);
    }

    void work()
    {
		n=read(),m=read();
		int tot=0;
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=n;j++) 
			{
				int x=read();
				Matrix[++tot]=(node){i,j,x};
			}
		sort(Matrix+1,Matrix+1+tot);
		for(int i=1;i<=m;i++)
			a[i]=(question){i,read(),read(),read(),read(),read()};
		solve(1,m,1,tot);//值域太大,考虑用点值代替
		for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
