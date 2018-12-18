#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=(1<<9)+10;
int n,k,king[MAXN],OK[MAXN];
ll dp[12][MAXN][90],ans;

inline bool check1(int x)
{
    return (x&(x>>1))==0;
}

inline int count(int x)
{
    int ans=0;
    for(;x;x>>=1) ans+=(x&1);
    return ans;
}

inline bool check2(int x,int y)
{
    return ((x&y)==0) && ((x&(y>>1))==0) && (((x>>1)&y)==0);
}

int main()
{
    scanf("%d%d",&n,&k);
    if(k==0) {printf("1");return 0;}
    int all=(1<<n)-1;
    for(int i=0;i<=all;i++)
	if(check1(i)) 
	{
	    OK[i]=1;
	    king[i]=count(i);
	    dp[1][i][king[i]]=1;
	}

    for(int i=1;i<n;i++)
	for(int j=0;j<=all;j++) if(OK[j])
	    for(int g=0;g<=all;g++) if(OK[g])
		if(check2(j,g))
		    for(int p=king[j];p+king[g]<=k;p++)
			dp[i+1][g][p+king[g]]+=dp[i][j][p];

    for(int i=0;i<=all;i++) ans+=dp[n][i][k];
    printf("%lld",ans);
    return 0;
}
