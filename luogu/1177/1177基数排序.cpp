//基数排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,a[MAXN],basket[15],tmp[MAXN];

int main()
{
    scanf("%d",&n);
	int mx=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),mx=max(a[i],mx);
    for(int t=1,step=1;t<=10;t++,step*=10)
    {
		if(mx<step) break;
		for(int i=0;i<10;i++) basket[i]=0;
		for(int i=1;i<=n;i++) basket[a[i]/step%10]++;
		for(int i=1;i<10;i++) basket[i]+=basket[i-1];
		for(int i=n;i>=1;i--) tmp[basket[a[i]/step%10]--]=a[i];
		for(int i=1;i<=n;i++) a[i]=tmp[i];
    }
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    return 0;
}
