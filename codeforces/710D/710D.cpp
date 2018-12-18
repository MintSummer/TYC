#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

namespace TYC
{
    typedef long long ll;
    ll a1,b1,a2,b2,L,R;

    ll exgcd(ll a,ll b,ll &x,ll &y)
    {
		if(b==0) {x=1,y=0;return a;}
		ll g=exgcd(b,a%b,x,y);
		ll tmp=x;
		x=y;
		y=tmp-a/b*y;
		return g;
    }

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>a1>>b1>>a2>>b2>>L>>R;
		ll x,y;
		ll g=exgcd(a1,a2,x,y),lcm=a1*a2/g;
		if((b2-b1)%g!=0) {puts("0");return;}
		x=x*(b2-b1)/g;
		ll dx=-a2/g,dy=a1/g;
		if(x<0)
		{
			ll tmp=ceil((double)x/dx);
			x-=tmp*dx;
		}
		else
		{
			ll tmp=floor((double)-x/dx);
			x+=dx*tmp;
		}
		y=(b2-b1-x*a1)/-a2;
		if(y<0)
		{
			ll tmp=ceil((double)-y/dy);
			x-=tmp*dx,y+=tmp*dy;
		}
		ll val=a1*x+b1;
		if(val>R) {puts("0");return;}
		ll l=max((double)val,val+lcm*ceil((double)(L-val)/lcm));
		ll r=max((double)val,val+lcm*floor((double)(R-val)/lcm));
		printf("%lld\n",(r-l)/lcm+1);
    }
}

int main()
{
    TYC::work();
    return 0;
}
