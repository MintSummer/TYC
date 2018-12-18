#include<bits/stdc++.h>
using namespace std;
int ans,x,n;

int abss(int a) 
{
    return a<0?-a:a;
}

int gcd(int a,int b)
{
    return !b?a:gcd(b,a%b);
}

int main()
{
    scanf("%d",&n);
    scanf("%d",&ans);
    ans=abss(ans);
    for(int i=2;i<=n;i++) 
    {
	scanf("%d",&x);
	ans=gcd(ans,abss(x));
    }
    printf("%d",ans);
    return 0;
}
