#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,a[MAXN],id[MAXN],d[MAXN],cnt=1,dp[MAXN];

int main()
{
	scanf("%d",&n);
	int x;
	for(int i=1;i<=n;i++) scanf("%d",&x),id[x]=i;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]=id[a[i]];

	d[1]=a[1];
	int lt,rt,mid;
	for(int i=2;i<=n;i++)
	{
		if(a[i]>d[cnt]) d[++cnt]=a[i];
		else 
		{
			lt=0,rt=cnt;
			while(lt<rt)
			{
				mid=(lt+rt)>>1;
				if(d[mid]>a[i]) rt=mid;
				else lt=mid+1;
			}
			d[lt]=min(a[i],d[lt]);
		}
	}
	printf("%d",cnt);
	return 0;
}
