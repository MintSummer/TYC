#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;

namespace TYC
{
	const int N=1010;
	int n,a[N],b[N][N];

	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=n;j++) 
				scanf("%d",&b[i][j]);
		
	}
}

int main()
{
	TYC::work();
	return 0;
}
