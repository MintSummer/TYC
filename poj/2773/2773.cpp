#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int m,k,cnt,s[1000010];

int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}

int main()
{
    while(~scanf("%d%d",&m,&k))
    {
	cnt=0;
	memset(s,0,sizeof(s));
	for(int i=1;i<=m;i++)
	    if(gcd(i,m)==1) s[++cnt]=i;
	if(k%cnt==0) printf("%lld\n",(long long)(k/cnt-1)*m+s[cnt]);
	else printf("%lld\n",(long long)(k/cnt)*m+s[k%cnt]);
    }
    return 0;
}
