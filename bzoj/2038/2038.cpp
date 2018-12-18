#include<bits/stdc++.h>
using namespace std;
const int MAXN=50010;
typedef long long ll;
int n,m,bask,col[MAXN],belong[MAXN];
ll ans,sum[MAXN];

struct Query
{
	int lt,rt,id;
	ll a,b;
}q[MAXN];

bool cmp1(Query a,Query b)
{
	return belong[a.lt]==belong[b.lt]?a.rt<b.rt:a.lt<b.lt;
}

bool cmp2(Query a,Query b)
{
	return a.id<b.id;
}

void add(int x,int val)
{
	ans-=sum[col[x]]*sum[col[x]];
	sum[col[x]]+=val;
	ans+=sum[col[x]]*sum[col[x]];
}

ll gcd(ll a,ll b)
{
	return b==0?a:gcd(b,a%b);
}

int main()
{
	scanf("%d%d",&n,&m);
	bask=sqrt(n);
	for(int i=1;i<=n;i++) 
		scanf("%d",&col[i]),belong[i]=i/bask+1;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&q[i].lt,&q[i].rt),q[i].id=i;
		
	sort(q+1,q+1+m,cmp1);
	int l=1,r=0;//×ó±ÕÓÒ¿ªÇø¼ä 
	for(int i=1;i<=m;i++)
	{
		while(l<q[i].lt) add(l,-1),l++;
		while(l>q[i].lt) add(l-1,1),l--;
		while(r<q[i].rt) add(r+1,1),r++;
		while(r>q[i].rt) add(r,-1),r--;
		
		if(q[i].lt==q[i].rt) {q[i].a=0,q[i].b=1;continue;}
		q[i].a=ans-(q[i].rt-q[i].lt+1);
		q[i].b=1LL*(q[i].rt-q[i].lt+1)*(q[i].rt-q[i].lt);
		ll g=gcd(q[i].a,q[i].b);
		q[i].a/=g,q[i].b/=g;
	}
	
	sort(q+1,q+1+m,cmp2);
	for(int i=1;i<=m;i++) 
		printf("%lld/%lld\n",q[i].a,q[i].b);
	return 0;
}
