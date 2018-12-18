#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1010;
	int n,arr[N][N],column[N],row[N];

	void work()
	{
		scanf("%d",&n);
		char ch;
		for(int i=1;i<=n;i++)
		{
			do ch=getchar(); while(!isdigit(ch));
			for(int j=1;j<=n;j++)
			{
				arr[i][j]=ch-'0';
				row[i]^=arr[i][j],column[j]^=arr[i][j];
				ch=getchar();
			}
		}
		int tot=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				tot+=row[i]^column[j]^arr[i][j];
		printf("%d\n",min(n*n-tot,tot));
	}
}

int main()
{
	TYC::work();
	return 0;
}
