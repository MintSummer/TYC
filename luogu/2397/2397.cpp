#include<bits/stdc++.h>
using namespace std;

int main()
{
    int ans,cnt=0,n,x;
    scanf("%d",&n);
    scanf("%d",&ans);
    cnt++;
    for(int i=2;i<=n;i++)
    {
		scanf("%d",&x);
		if(ans!=x) cnt--;
		else cnt++;
		if(cnt<=0) ans=x,cnt=1;
    }
    printf("%d",ans);
}
