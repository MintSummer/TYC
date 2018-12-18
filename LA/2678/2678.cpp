#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=100010;
    int N;
    ll S,a[MAXN],sum[MAXN];

    void work()
    {
		while(~scanf("%d%lld",&N,&S))
		{
			for(int i=1;i<=N;i++) 
			scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i]; 
			int ans=N+1;
			for(int lt=1,rt=1;rt<=N;rt++)
			{
				if(sum[rt]-sum[lt-1]<S) continue;
				while(lt<=rt&&sum[rt]-sum[lt]>=S) lt++;
				ans=min(ans,rt-lt+1);
			}
			cout<<(ans==N+1?0:ans)<<endl;
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
