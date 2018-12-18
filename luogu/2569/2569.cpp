#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
    const int N=2010,inf=0x3f3f3f3f;
    int T,MaxP,D,ap[N],bp[N],as[N],bs[N],q[N];
    ll ans,dp[N][N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;;
    }

    void work()
    {
        T=read(),MaxP=read(),D=read();
        for(int i=1;i<=T;i++) 
            ap[i]=read(),bp[i]=read(),as[i]=read(),bs[i]=read();
		for(int i=0;i<=T;i++)
			for(int j=0;j<=MaxP;j++) 
				dp[i][j]=-inf;
        int h,t;
        for(int i=1;i<=T;i++)
        {
            for(int j=0;j<=as[i];j++) 
                dp[i][j]=-j*ap[i];
            for(int j=0;j<=MaxP;j++)
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
            if(i-D-1<0) continue; 
            h=1,t=0;
            for(int j=0;j<=MaxP;j++)
            {
                while(h<=t&&q[h]<j-as[i]) h++;
                if(h<=t) dp[i][j]=max(dp[i][j],dp[i-D-1][q[h]]-(j-q[h])*ap[i]);
                while(h<=t&&dp[i-D-1][q[t]]+q[t]*ap[i]<=dp[i-D-1][j]+j*ap[i]) t--;
                q[++t]=j;
            }
            h=1,t=0;
            for(int j=MaxP;j>=0;j--)
            {
                while(h<=t&&q[h]>j+bs[i]) h++;
                if(h<=t) dp[i][j]=max(dp[i][j],dp[i-D-1][q[h]]+(q[h]-j)*bp[i]);
                while(h<=t&&dp[i-D-1][q[t]]+q[t]*bp[i]<=dp[i-D-1][j]+j*bp[i]) t--;
                q[++t]=j;
            }
        }
        for(int i=0;i<=MaxP;i++) ans=max(ans,dp[T][i]);
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
