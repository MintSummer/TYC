//详见http://hzwer.com/1457.html
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll r,d,ans;

ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}

bool check(ll a,double b)
{
    if(b-floor(b)>1e-8) return false;
    ll c=(ll)floor(b);
    if(gcd(a*a,c*c)==1 && a*a!=c*c) return true;
}

int main()
{
    scanf("%lld",&r);
    for(d=1;d*d<=2*r;d++)
    {
	if(2*r%d==0)
	{
	    for(ll a=1;a<=(ll)sqrt(r/d);a++)
	    {
		double b=sqrt((2*r/d)-a*a);
		if(check(a,b)) ans++;
	    }
	    if((2*r)/d != d)
		for(ll a=1;a<=(ll)sqrt(d/2);a++)
		{
		    double b=sqrt(d-a*a);
		    if(check(a,b)) ans++;
		}
	}
    }
    printf("%lld",ans*4+4);
    return 0;
}
