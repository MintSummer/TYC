#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2000010;
const ll p=20100403;//话说这是一个质数欸
ll n,m,f[MAXN];
/*
补集转换：总方案数-不满足条件的方案数
总方案数->总共n+m个字符，其中1要有n个，总共C(n,n+m)种
不满足条件的方案数->见图
故ans=C(n+m,n)-C(n+m,n+1)或C(n+m,n)-C(n+m,m-1)
*/

ll qpow(ll x,ll tim)
{
    ll ans=1;
    for(;tim;tim>>=1,x=x*x%p)
	if(tim&1) ans=ans*x%p;
    return ans;
}

ll C(ll x,ll y)
{
    return f[x]*qpow(f[y],p-2)%p*qpow(f[x-y],p-2)%p;
}

int main()
{
    scanf("%lld%lld",&n,&m);
    f[0]=1;
    for(int i=1;i<=n+m;i++) f[i]=(f[i-1]*i)%p;
    printf("%lld",(C(n+m,n)-C(n+m,n+1)+p)%p);
    return 0;
}
