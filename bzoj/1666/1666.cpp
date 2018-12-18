//tyc
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int main()
{
    int n,ans=0;
    scanf("%d",&n);
    while(n!=1)
    {
	ans++;
	if(n%2) n=n*3+1;
	else n=n/2;
    }
    printf("%d",ans);
    return 0;
}
