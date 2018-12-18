#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const double delta=0.99;
    int n,m,a[30],sum[30];
    double ave,ans=1e18,dp[30][10];
	
	inline double sqr(double x)
	{
		return x*x;
	}

    inline double calc()
    {
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
        memset(dp,127,sizeof(dp));
        dp[0][0]=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=min(m,i);j++)
                for(int s=0;s<i;s++)
                    dp[i][j]=min(dp[i][j],dp[s][j-1]+sqr(sum[i]-sum[s]-ave));
        ans=min(ans,dp[n][m]);
        return dp[n][m];
    }
    
    inline double Rand()
    {
        return rand()%100000/100000.00;
    }

    inline void SA(double T)
    {
        double now=ans;
        while(T>1e-3)
        {
            int x=rand()%n+1,y=rand()%n+1;
            if(x==y) continue;
            swap(a[x],a[y]);
            double new_ans=calc();
            if(new_ans<now||Rand()<exp(now-new_ans)/T) now=new_ans;
            else swap(a[x],a[y]);
            T*=delta;
        }
        for(int i=1;i<=10000;i++)
        {
            int x=rand()%n+1,y=rand()%n+1;
            if(x==y) continue;
            swap(a[x],a[y]);
            calc();
            swap(a[x],a[y]);
        }
    }

    void work()
    {
        srand(19260817);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) 
            scanf("%d",&a[i]),ave+=a[i];
        ave=1.0*ave/m; 
        calc();
        int tim=3;
        while(tim--) SA(10000.0);
        printf("%.2lf\n",sqrt(ans/m));
    }
}
int main()
{
    freopen("2428.in","r",stdin);
    freopen("2428.out","w",stdout);
    TYC::work();
    return 0;
}
