#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll p=19940417;

void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b) {x=1,y=0;return;}
    exgcd(b,a%b,y,x);
    y-=a/b*x;
}

ll inv(ll a)
{
    ll x,y;
    exgcd(a,p,x,y);
    return (x%p+p)%p;
}

int main()
{
    printf("%lld %lld\n",inv(2),inv(6));
}