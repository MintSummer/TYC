//高斯消元处理全矩阵
#include<bits/stdc++.h>
using namespace std;
const double EPS=1e-6;
int n;
bool flag=false;
double C[110][110];

bool gauss()
{
	for(int i=1;i<=n;i++)
	{
		int pos=i;
		for(int j=i+1;j<=n;j++)
			if(abs(C[j][i]) - abs(C[pos][i]) > EPS) pos=j;
		if(i!=pos)
			for(int j=1;j<=n+1;j++) swap(C[i][j],C[pos][j]);

		if(abs(C[i][i])<EPS) return false;

		for(int j=1;j<=n;j++)
			if(j!=i)//没这句会WA完
			{
				double tmp=C[j][i]/C[i][i];
				for(int k=i+1;k<=n+1;k++) C[j][k]-=C[i][k]*tmp;
			}
	}
	for(int i=1;i<=n;i++)
		C[i][n+1]/=C[i][i];
	return true;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			scanf("%lf",&C[i][j]);
		scanf("%lf",&C[i][n+1]);
	}
	if(!gauss()) printf("No Solution");
	else
		for(int i=1;i<=n;i++)
			printf("%.2lf\n",C[i][n+1]);
	return 0;
}
