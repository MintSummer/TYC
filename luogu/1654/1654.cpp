#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=100010;
	int n;
	double p,f[N][3],dp[N];
	
	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
        {
            scanf("%lf",&p);
            f[i][0]=p*(f[i-1][0]+1);
            f[i][1]=p*(f[i-1][1]+2*f[i-1][0]+1);
            f[i][2]=p*(f[i-1][2]+3*f[i-1][1]+3*f[i-1][0]+1);
            dp[i]=dp[i-1]+f[i][2]-f[i-1][2]*p;
        }
		printf("%.1lf\n",dp[n]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
