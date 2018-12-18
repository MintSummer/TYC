#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long double LD;
    const int N=300010;
    int n;
    string str;
    LD p[N],g1[N],g2[N],f[N];

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>n>>str;
        for(int i=1;i<=n;i++)
            switch(str[i-1])
            {
                case 'o': p[i]=1.0;break;
                case 'x': p[i]=0.0;break;
                case '?': p[i]=0.5;break;
            }
        for(int i=1;i<=n;i++)
        {
            g1[i]=p[i]*(g1[i-1]+1);
            g2[i]=p[i]*(g2[i-1]+2*g1[i-1]+1);
            f[i]=f[i-1]+g2[i]-p[i]*g2[i-1];
        }
        cout<<fixed<<setprecision(4)<<f[n]<<"\n";
    }
}

int main()
{
    TYC::work();
    return 0;
}