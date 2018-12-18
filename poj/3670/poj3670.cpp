#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[30010],d[30010],cnt;

int find_no_down()
{
    int l,r,mid,ans;
    cnt=0;
    memset(d,0,sizeof(d));
    for(int i=1;i<=n;i++)
      {
      	if(d[cnt]<=a[i]) d[++cnt]=a[i];
      	else
      	  {
      	  	l=0,r=cnt;
            while(l<=r)
              {
              	mid=(l+r)/2;
              	if(d[mid]>a[i])
                  r=mid-1;
                else l=mid+1,ans=mid;
              } 
            d[ans+1]=a[i];
      	  }
      }
    return cnt; 
}

int find_no_up()
{
    int l,r,mid,ans;
    cnt=0;
    memset(d,0x3f3f3f3f,sizeof(d));
    d[++cnt]=a[1];
    for(int i=2;i<=n;i++)
      {
      	if(d[cnt]>=a[i]) d[++cnt]=a[i];
      	else 
      	  {
      	  	l=0,r=cnt;
      	  	while(l<=r)
      	  	  {
      	  	  	mid=(l+r)/2;
      	  	  	if(d[mid]<a[i]) r=mid-1;
      	  	  	else l=mid+1,ans=mid;
      	  	  }
      	  	d[ans+1]=a[i];
      	  }
      }
    return cnt;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
      scanf("%d",&a[i]);
    int num=0x3f3f3f3f;
    num=min(num,n-find_no_down());
    num=min(num,n-find_no_up());
    printf("%d",num);
    
} 