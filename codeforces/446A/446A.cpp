#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;
int n,a[MAXN],f[MAXN],g[MAXN],ans;
//用f[i]表示以i结尾的最长的非降串的长度
//用g[i]表示以i开始的最长的非降串的长度

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
	scanf("%d",&a[i]);
	if(a[i]>a[i-1]) f[i]=f[i-1]+1;
	else f[i]=1;
    }
    int tmp;
    for(int i=n;i>=1;i-=tmp)
    {
	tmp=f[i];
	for(int j=tmp;j>=1;j--) g[i-j+1]=f[i+j-tmp]; 
    }
    if(n==1) {printf("1");return 0;}
    for(int i=1;i<=n;i++) //枚举修改的点，考虑修改后的情况
    {
	if(a[i+1]-a[i-1]>=2) ans=max(ans,f[i-1]+g[i+1]+1);
	else
	{
	    ans=max(ans,f[i-1]+1);
	    ans=max(ans,g[i+1]+1);
	}
    }
    printf("%d",ans);
    return 0;
}
