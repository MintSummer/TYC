#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int n,mx[110][110],mn[110][110],a[110],sum[110];
    void work()
    {
		ios::sync_with_stdio(false);
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
		for(int i=1;i<=n*2;i++) sum[i]=sum[i-1]+a[i];	
		for(int p=1;p<n;p++)
			for(int i=1,j=i+p;j<=n*2&&i<=n*2;i++,j=i+p)
			{
				mn[i][j]=0x3f3f3f3f;
				for(int k=i;k<j;k++)
				{
					mx[i][j]=max(mx[i][j],mx[i][k]+mx[k+1][j]+sum[j]-sum[i-1]);
					mn[i][j]=min(mn[i][j],mn[i][k]+mn[k+1][j]+sum[j]-sum[i-1]);
				}
			}
		int ans1=0x3f3f3f3f,ans2=0;
		for(int i=1;i<=n;i++)
		{
			ans2=max(ans2,mx[i][i+n-1]);
			ans1=min(ans1,mn[i][i+n-1]);
		}
		cout<<ans1<<endl<<ans2;
    }
}

int main()
{
    TYC::work();
    return 0;
}
