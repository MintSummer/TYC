#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100010;
int n,a[N];
ll ans,mid,sum,c[N];

namespace TYC
{
    void work()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) 
            scanf("%d",&a[i]),sum+=a[i];
        int ave=sum/n;
        for(int i=2;i<=n;i++) 
            c[i]=c[i-1]+a[i]-ave;
        sort(c+1,c+1+n);
        mid=c[(n+1)>>1];
        for(int i=1;i<=n;i++)
            ans+=abs(mid-c[i]);
        printf("%lld",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}