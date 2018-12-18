#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;

ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}

struct node
{
    ll d,a,b;
    node(ll d=0,ll a=0,ll b=0):d(d),a(a),b(b) {}
    void clear()
    {
		ll k=a/b;
		d+=k,a-=k*b;
		ll g=gcd(a,b);
		a/=g,b/=g;
    }
    node operator + (const node &x) const
    {
		node now;
		now.d=d+x.d;
		ll g=gcd(b,x.b);
		ll k=now.b=b*x.b/g;
		now.a=a*(k/b)+x.a*(k/x.b);
		now.clear();
		return now;
    }
    void print()
    {
		if(a==0) {printf("%lld",d);return;}
		for(ll k=d;k;k/=10) printf(" ");
		printf("%lld\n%lld",a,d);
		for(ll k=b;k;k/=10) printf("-");
		printf("\n");
		for(ll k=d;k;k/=10) printf(" ");
		printf("%lld",b);
    }
}ans;
int main()
{
    scanf("%d",&n);
    ans=node(0,0,1);
    for(int i=1;i<=n;i++) ans=ans+node(0,n,i);
    ans.clear();
    ans.print();
    return 0;
}
