#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int p=9999991;
    int n;
    long long ans=1;

    void work()
    {
        scanf("%d",&n);
		for(int i=1;i<=n-2;i++) ans=ans*n%p;
        for(int i=1;i<n;i++) ans=ans*i%p;
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
