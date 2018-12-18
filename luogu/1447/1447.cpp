#include<cstdio>
using namespace std;
typedef long long ll;
ll n,m,ans,f[100010];

int main()
{
    scanf("%lld%lld",&n,&m);
    if(n<m) swap(n,m);
    for(ll i=n;i>=1;i--)
    {
        f[i]=(n/i)*(m/i);
        for(ll j=2*i;j<=n;j+=i) f[i]-=f[j];
        ans+=f[i]*(2*i-1);
    }
    printf("%lld",ans);
    return 0;
}
