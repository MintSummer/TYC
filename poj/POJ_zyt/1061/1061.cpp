#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
ll x,y,m,n,L;
ll exgcd(ll a,ll b,ll &x,ll &y)
{
	ll xx,yy;
	if(b==0)
	{
		x=1,y=0;
		return a;
	}
	ll gcd=exgcd(b,a%b,xx,yy);
	x=yy;
	y=xx-a/b*yy;
	return gcd;
}
int main(void)
{
	cin>>x>>y>>m>>n>>L;
	if(m<n)swap(m,n),swap(x,y);
	ll ans,ans2;
	ll a=m-n,b=(y-x+L)%L;
	ll gcd=exgcd(a,L,ans,ans2);
	if(b%gcd)
		cout<<"Impossible";
	else
	{
		for(ans*=b/gcd;ans<0;ans+=L/gcd);
		cout<<ans%(L/gcd);
	}
	return 0;
}
