#include<bits/stdc++.h>
using namespace std;
const double eps=1e-7;
int n;
double a[15][15];

double ABS(double x)
{
    return x<0?-x:x;
}

void gauss()
{
    for(int i=1;i<=n;i++)
    {
	int k=i;
	for(int j=i+1;j<=n;j++) 
	    if(ABS(a[j][i]) - ABS(a[k][i]) > eps) k=j;
	if(i!=k)
	    for(int j=i;j<=n+1;j++) swap(a[k][j],a[i][j]);

	for(int j=i+1;j<=n;j++) 
	{
	    double tmp=a[j][i]/a[i][i];
	    for(k=i;k<=n+1;k++) a[j][k]-=a[i][k]*tmp;
	}
    }
    for(int i=n;i>=1;i--)
    {
	for(int j=i+1;j<=n;j++) a[i][n+1]-=a[j][n+1]*a[i][j];
	a[i][n+1]/=a[i][i];
    }
}

int main()
{
    scanf("%d",&n);
    n++;
    for(int i=1;i<=n;i++)
    {
	for(int j=1;j<n;j++)
	{
	    scanf("%lf",&a[i][j]);
	    a[i][n+1]+=a[i][j]*a[i][j];
	    a[i][j]*=-2.0;
	}
	a[i][n]=1;
	a[i][n+1]*=-1.0;
    }
    gauss();
    for(int i=1;i<n-1;i++)
	printf("%.3lf ",a[i][n+1]);
    printf("%.3lf",a[n-1][n+1]);
    return 0;
}
