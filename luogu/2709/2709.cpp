#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=50010;
int n,m,k,bask,belong[MAXN],a[MAXN],cnt[MAXN];
ll ans;

int read()
{
	int x=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}

struct query 
{
	int id,l,r;
	ll ans;
}q[MAXN];

bool cmp1(query x,query y) 
{
	return belong[x.l]==belong[y.l]?x.r<y.r:x.l<y.l;
}

bool cmp2(query x,query y)
{
	return x.id<y.id;
}

void add(int x,int val)
{
	ans-=cnt[a[x]]*cnt[a[x]];
	cnt[a[x]]+=val;
	ans+=cnt[a[x]]*cnt[a[x]];
}

int main()
{
	n=read(),m=read(),k=read();
	bask=sqrt(n);
	for(int i=1;i<=n;i++) 
		a[i]=read(),belong[i]=i/bask+1;
	for(int i=1;i<=m;i++)
		q[i].id=i,q[i].l=read(),q[i].r=read();
	sort(q+1,q+1+m,cmp1);
	int lt=1,rt=0;
	for(int i=1;i<=m;i++)
	{
		while(lt<q[i].l) add(lt,-1),lt++;
		while(lt>q[i].l) add(lt-1,1),lt--;
		while(rt<q[i].r) add(rt+1,1),rt++;
		while(rt>q[i].r) add(rt,-1),rt--;
		q[i].ans=ans;
	}
	sort(q+1,q+1+m,cmp2);
	for(int i=1;i<=m;i++) printf("%d\n",q[i].ans);
	return 0;
}
