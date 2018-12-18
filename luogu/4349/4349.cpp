#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=300010;
    const int mod=1e9+7;
    int n,m,ans,t;
    char ch[N];
    
    void work()
    {
        scanf("%d%d%s",&n,&m,ch+1);
        for(int i=1;i<=n;i++)
        {
            t=(t*10+ch[i]-'0')%m;
            if(!t) ans=(ans==0?1:(ll)ans*2%mod);
        }
        if(t) puts("0");
        else printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
