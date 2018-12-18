#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const double eps=1e-7;
    int n,k;
    double a[10010];

    bool check(double mid)
    {
        int cnt=0;
        for(int i=1;i<=n;i++) cnt+=a[i]/mid;
        return cnt>=k;        
    }

    void work()
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) scanf("%lf",&a[i]);
        double l=0.0,r=100000.00,mid,ans;
        while(r-l>=eps)
        {
            mid=(l+r)/2;
            if(check(mid)) ans=mid,l=mid+eps;
            else r=mid-eps;
        }
        ans=floor(ans*10000+0.5)/10000;
        printf("%.2f",floor(ans*100)/100);
    }
}

int main()
{
    TYC::work();
    return 0;
}