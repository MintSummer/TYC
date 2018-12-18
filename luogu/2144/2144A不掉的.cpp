//其实这道题是个高精度……这个Matrix_tree它……它A不掉啊……
//仅供推式子
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
int n,G[110][110];
double a[110][110],d[110][110];

double judge()
{
    double ans=1;
    int tim=0;
    for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	    d[i][j]=a[i][j];
    for(int i=1;i<=n;i++)
    {
	if(d[i][i]<=eps) 
	{
	    int k=i+1;
	    while(d[k][i]<=eps) k++;
	    if(k==n+1) return 0;
	    else for(int j=i;j<=n;j++)
		swap(d[i][j],d[k][j]);
	    tim++;
	}
	else 
	{
	    ans*=d[i][i];
	    for(int j=i+1;j<=n;j++)
	    {
		double res=d[j][i]/d[i][i];
		for(int k=i+1;k<=n;k++)
		    d[j][k]-=d[i][k]*res;
	    }
	}
    }
    return tim&1?-ans:ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
	G[i][n+1]=G[n+1][i]=1;
    for(int i=1;i<n;i++) G[i][i+1]=G[i+1][i]=1;
    G[n][1]=G[1][n]=1;
    for(int i=1;i<=n+1;i++)
	for(int j=i+1;j<=n+1;j++)
	    if(G[i][j])
	    {
		a[i][i]++,a[j][j]++;
		a[i][j]=a[j][i]=-1;
	    }
    printf("%.0lf",judge());
    return 0;
}
