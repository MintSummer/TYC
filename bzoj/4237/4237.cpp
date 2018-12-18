#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=2e5+10;
    int n,stack_up[MAXN],stack_down[MAXN];//维护一个递增一个递减的单调栈
    ll ans;
    struct node
    {
		int x,y;
    }a[MAXN];

    bool cmpx(const node &p,const node &q)
    {
		return p.x<q.x;
    }

    bool cmpy(const node &p,const node &q)
    {
		return p.y<q.y;
    }

    void cdq(int l,int r)
    {
		if(l==r) return;
		sort(a+l,a+r+1,cmpy);
		int mid=(l+r)>>1;//刚好将纵坐标分成两部分,保证l到mid的y都小于mid+1到r的y
		cdq(l,mid),cdq(mid+1,r);
		sort(a+l,a+mid+1,cmpx);
		sort(a+mid+1,a+r+1,cmpx);
		int top_up=0,top_down=0;
		for(int i=l,j=mid+1;j<=r;j++)
		{
			while(top_up>0 && a[j].y<=a[stack_up[top_up]].y) top_up--;//不包括边界
			stack_up[++top_up]=j;
			while(i<=mid && a[i].x<a[j].x)
			{
				while(top_down>0 && a[i].y>=a[stack_down[top_down]].y) top_down--;
				stack_down[++top_down]=i;
				i++;
			}
			int L=1,R=top_down,pos=-1,limit=a[stack_up[top_up-1]].x;
			while(L<=R)
			{
				int Mid=(L+R)>>1;
				if(a[stack_down[Mid]].x>limit) pos=Mid,R=Mid-1;
				else L=Mid+1;
			}
			if(pos!=-1) ans+=top_down-pos+1;
		}
    }

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void work()
    {
		n=read();
		for(int i=1;i<=n;i++) 
			a[i].x=read(),a[i].y=read();
		a[0].x=-1,a[0].y=-1;
		cdq(1,n);
		printf("%lld",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
