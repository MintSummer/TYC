#include<cstdio>
#include<algorithm>
using namespace std;
int n,c;
long long ans;
long long a[100010];
int main(void)
{
	scanf("%d%d",&n,&c);
	for(int i=0;i<n;i++)
		scanf("%lld",a+i);
	sort(a,a+n);
	long long s=1,e=a[n-1]-a[0],mid;
	while(s<=e)
	{
		long long step=1,last=a[0];
		mid=(s+e)/2;
		for(int i=1;i<n;i++)
			if(a[i]-last>=mid)
				last=a[i],step++;
		if(step>=c)
			ans=mid,s=mid+1;
		else e=mid-1;
	}
	printf("%lld",ans);
	return 0;
}
