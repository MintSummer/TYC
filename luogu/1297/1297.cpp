#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=10000010;
    typedef long long ll;
    int n,A,B,C,a[N];

    void work()
    {
        scanf("%d%d%d%d%d",&n,&A,&B,&C,a+1);
        for (int i=2;i<=n;i++)
            a[i]=((ll)a[i-1]*A+B)%100000001;
        for (int i=1;i<=n;i++)
            a[i]=a[i]%C+1;
        a[n+1]=a[1];
        double ans=0;
        for(int i=1;i<=n;i++)
            ans+=(double)min(a[i],a[i+1])/a[i]/a[i+1];
        printf("%.3lf",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
