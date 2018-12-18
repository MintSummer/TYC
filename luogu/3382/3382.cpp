#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
int n;
double lt,rt,a[20];

double f(double x)
{
    double ans=0,tmp=1;
    for(int i=0;i<=n;i++,tmp*=x)
	ans+=tmp*a[i];
    return ans;
}

int main()
{
    scanf("%d%lf%lf",&n,&lt,&rt);
    for(int i=0;i<=n;i++)
	scanf("%lf",&a[n-i]);
    double ans;
    while(rt-lt>eps)
    {
	double mid=(lt+rt)/2;	
	if(f(mid)>f(mid+eps)&&f(mid)>f(mid-eps)) {ans=mid;break;}
	else if(f(mid-eps)>f(mid)) rt=mid;
	else lt=mid+eps;
    }
    printf("%.5lf",ans);
    return 0;
}
