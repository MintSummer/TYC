#include<bits/stdc++.h>
using namespace std;
int n;

long long f(int x)
{
    return x==1?1:f(x/2)+1;
}

int main()
{
    while(~scanf("%d",&n))
	printf("%lld\n",f(n));
    return 0;
}
