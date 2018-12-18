#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=500010;
int n,m,bask,ans,a[MAXN],belong[MAXN],cnt[1000010];

int read()
{
	int x=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}

struct Query
{
	int l,r,id,ans;
}q[200010];

bool cmp1(Query x,Query y)
{
	return belong[x.l]==belong[y.l]?x.r<y.r:x.l<y.l;
}

bool cmp2(Query x,Query y)
{
	return x.id<y.id;
}

void add(int x,int val)
{
	if(cnt[a[x]]==1&&val==-1) ans--;
	if(cnt[a[x]]==0&&val==1) ans++;
	cnt[a[x]]+=val;
}

int main()
{
	n=read();
	bask=sqrt(n);
	for(int i=1;i<=n;i++) 
		a[i]=read(),belong[i]=i/bask+1;
	m=read();
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
