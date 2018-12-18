#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
int n,a[10010],mid;

bool cmp(int a,int b)
{
	return a>b;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	sort(a+1,a+1+n,cmp);
	mid=n/2;
	if(n%2==1)
	  printf("%d",a[mid+1]);
	else printf("%d",(a[mid]+a[mid+1])>>1);
	return 0;
}