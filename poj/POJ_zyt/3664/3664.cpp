#include<cstdio>
#include<algorithm>
using namespace std;
struct cow
{
	int id;
	int a;
	int b;
};
cow a[50010];
int n,k;
bool cmp1(cow a,cow b)
{
	return a.a>b.a;
}
bool cmp2(cow a,cow b)
{
	return a.b>b.b;
}
int main(void)
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d%d",&a[i].a,&a[i].b),a[i].id=i+1;
	sort(a,a+n,cmp1);
	sort(a,a+k,cmp2);
	printf("%d",a[0].id);
	return 0;
}
