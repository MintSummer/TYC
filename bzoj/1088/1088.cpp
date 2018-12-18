#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int n,ans=0;
int a[10010],now[10010];
 
int search(int s)
{
    memset(now,0,sizeof(now));
    now[1]=s;
    now[2]=a[1]-now[1];
    if(now[2]<0||now[1]>2||now[2]>2) return 0;
    for(int i=3;i<=n;i++)
      {
        now[i]=a[i-1]-now[i-1]-now[i-2];
        if(now[i]<0||now[i]>2) return 0;
      }
    if(now[n-1]+now[n]!=a[n]) return 0;
    return 1;
}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
      scanf("%d",&a[i]);
    for(int s=0;s<=a[1];s++)
      ans+=search(s);
    printf("%d",ans);
    return 0;
}
