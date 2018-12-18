#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    int k,m,n;
    double ans;

    double sqr(double x) {return x*x;}

    void work()
    {
        scanf("%d%d%d",&k,&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                double p=(sqr((i-1)*m)+sqr((n-i)*m)+sqr((j-1)*n)+sqr((m-j)*n)-sqr((i-1)*(j-1))-sqr((i-1)*(m-j))-sqr((n-i)*(j-1))-sqr((n-i)*(m-j)))/sqr(n*m);
                ans+=1.0-pow(p,k);
            }
        printf("%.0f",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}