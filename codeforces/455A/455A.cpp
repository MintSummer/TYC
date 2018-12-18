#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e5+10;
int n,cnt,a[MAXN],tim[MAXN];
ll dp[MAXN];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
	scanf("%d",&a[i]),tim[a[i]]++; 
    sort(a+1,a+1+n);
    dp[1]=a[1];
    for(int i=1;i<=a[n];i++)//选前一个数，或不选前一个数
	dp[i]=max(dp[i-1],dp[i-2]+(ll)tim[i]*i);
    printf("%lld",dp[a[n]]);
    return 0;
}
