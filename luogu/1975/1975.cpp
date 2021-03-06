//分块+树状数组(建立cnt个块的树状数组)
#include<cstdio>
#include<cmath>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=20010;
    int n,m,ans,block,tot,h[MAXN],tmp[MAXN],belong[MAXN],lt[MAXN],rt[MAXN];

    inline int read()
    {
		int x=0;char ch=getchar();
		while(!isdigit(ch)) ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return x;
    }

    struct bit_tree
    {
		int c[MAXN];
		int lowbit(int x) {return x&(-x);}
		void add(int x,int val) {for(;x<=n;x+=lowbit(x)) c[x]+=val;}
		int ask(int x)
		{
			int sum=0;
			for(;x;x-=lowbit(x)) sum+=c[x];
			return sum;
		}
    }all,b[200];

    void solve(int x,int y)//交换x,y只会对x+1到y-1的区间产生影响,分块处理
    {
		if(belong[x]==belong[y])
		{
			for(int i=x+1;i<y;i++)
			{
			    if(h[x]>h[i]) ans--;
			    else if(h[x]<h[i]) ans++;
			    if(h[y]>h[i]) ans++;
			    else if(h[y]<h[i]) ans--;
			}
		}
		else 
		{
			for(int i=belong[x]+1;i<=belong[y]-1;i++)
			{
				int num=rt[i]-lt[i]+1;
				ans-=b[i].ask(h[x]-1);//一定是要小于它的
				ans+=b[i].ask(h[y]-1);
				ans+=num-b[i].ask(h[x]);//要大于,所以要减掉等于的
				ans-=num-b[i].ask(h[y]);
			}
			for(int i=x+1;i<=rt[belong[x]];i++)
			{
			    if(h[x]>h[i]) ans--;
			    else if(h[x]<h[i]) ans++;
			    if(h[y]>h[i]) ans++;
			    else if(h[y]<h[i]) ans--;
			}	
			for(int i=lt[belong[y]];i<y;i++)
			{
			    if(h[x]>h[i]) ans--;
			    else if(h[x]<h[i]) ans++;
			    if(h[y]>h[i]) ans++;
			    else if(h[y]<h[i]) ans--;
			}
		}
		ans-=(h[x]>h[y]);
		ans+=(h[y]>h[x]);
    }

    void update(int x,int y)
    {
		b[belong[x]].add(h[x],-1);
		b[belong[y]].add(h[y],-1);
		swap(h[x],h[y]);
		b[belong[x]].add(h[x],1);
		b[belong[y]].add(h[y],1);
    }

    void work()
    {
		n=read();
		for(int i=1;i<=n;i++) h[i]=tmp[i]=read();
		sort(tmp+1,tmp+1+n);
		int num=unique(tmp+1,tmp+1+n)-tmp-1;
		for(int i=1;i<=n;i++) 
			h[i]=lower_bound(tmp+1,tmp+1+num,h[i])-tmp;//离散化

		block=(int)sqrt(n);//分块
		tot=n/block+(n%block!=0);
		for(int i=1;i<=tot;i++) 
			lt[i]=rt[i-1]+1,rt[i]=i*block;
		rt[tot]=n;
		for(int i=1;i<=n;i++)
		{
			belong[i]=(i-1)/block+1;
			b[belong[i]].add(h[i],1);
		}

		for(int i=n;i;i--)
		{
			ans+=all.ask(h[i]-1);
			all.add(h[i],1);
		}
		printf("%d\n",ans);//树状数组求逆序对
	
		int m=read();
		while(m--)
		{
			int x=read(),y=read();
			if(x>y) swap(x,y);
			solve(x,y);
			update(x,y);
			printf("%d\n",ans);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
