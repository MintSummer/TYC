#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
double x[210],y[210],K[2000005];

bool cmp(double a,double b)
{
    return a<b;
}

int main()
{
    scanf("%d",&n);
    int cnt=0;
    for(int i=1;i<=n;i++)
      {
      	scanf("%lf%lf",&x[i],&y[i]);
      	for(int j=1;j<i;j++)
      	  {
      	  	if(x[i]==x[j]) K[cnt]=0,cnt++;
      	  	else
      	  	  {
      	  	  	if(y[i]==y[j]) K[cnt]=10000,cnt++;
      	  	  	else
      	  	  	  K[cnt]=(y[j]-y[i])/(x[j]-x[i]),cnt++;
      	  	  }
      	  }
      }
    sort(K,K+cnt,cmp);
    for(int i=1;i<cnt;i++)
      if(abs(K[i]-K[i-1])>1e-8) ans++;
    printf("%d",ans+1);
    return 0;
}
