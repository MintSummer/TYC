#include<bits/stdc++.h>
using namespace std;
const int MAXN=80010;
int n,top=0,st[MAXN],a[MAXN];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
	while(top&&st[top]<=a[i]) top--;
	ans+=top;
	st[++top]=a[i];
    }
    printf("%lld",ans);
    return 0;
}
