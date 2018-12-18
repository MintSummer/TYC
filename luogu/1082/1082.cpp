#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;

    void exgcd(ll a,ll b,ll &x,ll &y)
    {
        if(!b) {x=1,y=0;return;}
        exgcd(b,a%b,x,y);
        ll tmp=x;
        x=y;
        y=tmp-a/b*y;
    }

    void work()
    {
        ll a,b,x,y;
        scanf("%lld%lld",&a,&b);
        exgcd(a,b,x,y);
        while(x<0) x+=b;
        while(x-b>0) x-=b;
        printf("%lld\n",x);
    }
}

int main()
{
    TYC::work();
    return 0;
}
