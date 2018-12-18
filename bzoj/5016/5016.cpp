#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=50010;
int n,m,tot,block,a[MAXN],cnt1[MAXN],cnt2[MAXN],belong[MAXN];
ll Ans[MAXN],ans;

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct query
{
    int l,r,id,val;
}q[MAXN*4];

bool cmp(query x,query y)
{
    return belong[x.l]==belong[y.l]?x.r<y.r:x.l<y.l;
}

int main()
{
    n=read();
    block=sqrt(n);
    for(int i=1;i<=n;i++) 
	a[i]=read(),belong[i]=(i-1)/block+1;
    m=read();
    for(int i=1;i<=m;i++)
    {
		int l1=read(),r1=read(),l2=read(),r2=read();
		l1--,l2--;
		q[++tot]=(query){r1,r2,i,1};
		q[++tot]=(query){l1,r2,i,-1};
		q[++tot]=(query){r1,l2,i,-1};
		q[++tot]=(query){l1,l2,i,1};
    }
    sort(q+1,q+1+tot,cmp);
    int lt=0,rt=0;
    for(int i=1;i<=tot;i++)
    {
		while(lt<q[i].l) lt++,ans+=cnt1[a[lt]],cnt2[a[lt]]++;
		while(lt>q[i].l) ans-=cnt1[a[lt]],cnt2[a[lt]]--,lt--;
		while(rt<q[i].r) rt++,ans+=cnt2[a[rt]],cnt1[a[rt]]++;
		while(rt>q[i].r) ans-=cnt2[a[rt]],cnt1[a[rt]]--,rt--;
		Ans[q[i].id]+=ans*q[i].val;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",Ans[i]);
    return 0;
}
