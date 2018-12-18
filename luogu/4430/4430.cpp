#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int p=9999991;
    int n,ans,fac[1000010];

    void work()
    {
        scanf("%d",&n);
		fac[0]=ans=1;
		for(int i=1;i<n;i++) fac[i]=(long long)fac[i-1]*i%p;
		for(int i=1;i<n-1;i++) ans=(long long) ans*n%p;
        printf("%d\n",fac[n-1]*ans%p);
    }
}

int main()
{
    TYC::work();
    return 0;
}
