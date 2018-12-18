#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100010;
int n,m;
ll sum[MAXN],s[MAXN],a[MAXN];
//sum为前缀和,s为i*S[i]-SS[i]的值 (均是树状数组) 
/*
找规律~
S:  1*a[1] 1*a[1]+1*a[2] 1*a[1]+1*a[2]+1*a[3] ……
SS: 1*a[1] 2*a[1]+1*a[2] 3*a[1]+2*a[2]+1*a[3] …… 
将S[i]*i以后，得到： 
	1*a[1] 2*a[1]+2*a[2] 3*a[1]+3*a[2]+3*a[3] ……
将S[i]*i-SS[i]，得到：
	0*a[1] 0*a[1]+1*a[2] 0*a[1]+1*a[2]+2*a[3] ……
	即∑(k=1~i) (k-1)*a[k] 符合前缀和
	那么就用树状数组差分解决 
*/ 

int lowbit(int x) {return x&(-x);}

void insert(ll c[],int x,ll val)
{
	for(;x<=n;x+=lowbit(x)) c[x]+=val;
}

ll ask(ll c[],int x)
{
	ll ans=0;
	for(;x;x-=lowbit(x)) ans+=c[x];
	return ans;
}

ll SS(int x)
{
	return ask(sum,x)*x-ask(s,x);
}

int main()
{
	scanf("%d%d",&n,&m);
	char ch[10];
	int x,val;
	for(int i=1;i<=n;i++) 
	{
		scanf("%lld",&a[i]);
		insert(sum,i,a[i]);
		insert(s,i,(i-1)*a[i]);
	}
	while(m--)
	{
		scanf("%s",ch);
		if(ch[0]=='Q') 
			{scanf("%d",&x);printf("%lld\n",SS(x));}
		else 
		{
			scanf("%d%d",&x,&val);
			ll d=val-a[x];a[x]=val;
			insert(sum,x,d),insert(s,x,(ll)d*(x-1));//开ll 
		}
	}
	return 0;
}
