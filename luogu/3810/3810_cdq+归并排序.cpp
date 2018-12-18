#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int MAXN=100010;
    int n,k,c[200010],ans[MAXN];

    struct node
    {
        int a,b,c,num,cnt;
        bool operator != (const node &x) const
        {
            return (a!=x.a)||(b!=x.b)||(c!=x.c);
        }
    }a[MAXN],b[MAXN];

    bool cmp1(const node &x,const node &y)
    {
        if(x.a!=y.a) return x.a<y.a;
        if(x.b!=y.b) return x.b<y.b;
        return x.c<y.c;
    }

    int lowbit(int x) {return x&(-x);}

    void add(int x,int d)
    {
        for(;x<=k;x+=lowbit(x)) c[x]+=d;
    }

    int ask(int x)
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
        int i=l,j=mid+1,k=l-1;
        while(i<=mid&&j<=r)
        {
            if(i<=mid&&a[i].b<=a[j].b)
            {
                add(a[i].c,a[i].cnt);
                b[++k]=a[i++];
            }
            else 
            {
                a[j].num+=ask(a[j].c);
                b[++k]=a[j++];
            }
        }
		if(i<=mid) 
		{
			int tmp=i;
			while(tmp<=mid) b[++k]=a[tmp++];
		}
        while(j<=r) a[j].num+=ask(a[j].c),b[++k]=a[j++];
        for(i--;i>=l;i--) add(a[i].c,-a[i].cnt);
		for(j=l;j<=r;j++) a[j]=b[j];
    }

    void work()
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&a[i].a,&a[i].b,&a[i].c);
        sort(a+1,a+1+n,cmp1);
        int tot=0;
        for(int i=1;i<=n;i++)
        {
            if(i==1||a[i]!=a[tot]) a[++tot]=a[i];
            a[tot].cnt++;
        }
        cdq(1,tot);
        for(int i=1;i<=tot;i++)
            ans[a[i].cnt+a[i].num]+=a[i].cnt;
        for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
