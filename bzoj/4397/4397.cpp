//from:TYC
#include<bits/stdc++.h>
using namespace std;
int n,q,sum[100010][4];

int main()
{
	scanf("%d%d",&n,&q);
	int a,b;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		for(int j=1;j<=3;j++) sum[i][j]=sum[i-1][j];
		sum[i][a]++;
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		printf("%d %d %d\n",sum[b][1]-sum[a-1][1],sum[b][2]-sum[a-1][2],sum[b][3]-sum[a-1][3]);
	}
	return 0;
}
