#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
long long N,m,k,maxx,tot;
long long a[550];
bool b[550];
void gree(long long x)
{
	memset(b,true,sizeof(b));
	long long sum=0,cur=1;
	for(int i=m;i>0;i--)
	{
		if(k-cur==i)break;
		if(sum+a[i]>x)
		{
			cur++;
			sum=a[i];
		}
		else sum+=a[i],b[i]=false;
	}
	for(int i=1;i<m;i++)
	{
		printf("%lld ",a[i]);
		if(b[i])printf("/ ");
	}
	printf("%lld",a[m]);
}
int main(void)
{
	scanf("%d",&N);
	while(N--)
	{
		maxx=-1,tot=0;
		scanf("%d%d",&m,&k);
		for(int i=1;i<=m;i++)
			scanf("%lld",a+i),
			tot+=a[i],
			maxx=max(a[i],maxx);
		long long s=maxx,e=tot,mid,ans;
		while(s<=e)
		{
			long long sum=0,cur=1;
			bool flag=false;
			mid=(s+e)/2;
			for(int i=1;i<=m;i++)
			{
				if(sum+a[i]>mid)
				{
					cur++;
					sum=a[i];
					if(cur>k)
					{
						flag=true;
						break;
					}
				}
				else sum+=a[i];
			}
			if(!flag)
				ans=mid,e=mid-1;
			else
				s=mid+1;
		}
		gree(ans);
		printf("\n");
	}
	return 0;
}
