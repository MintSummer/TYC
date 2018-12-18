#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,high,low;
int money[100010];
int main(void)
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
            scanf("%d",money+i);
            high+=money[i];
            low=max(low,money[i]);
    }
    int mid=(high+low)/2;
    while(low<high)
    {
                   int sum=0,group=0;
                   for(int i=0;i<n;i++)
                   {
                           if(sum+money[i]<=mid)sum+=money[i];
                           else sum=money[i],group++;
                   }
                   group++;
                   if(group>m)low=mid+1;
                   else high=mid-1;
                   mid=(high+low)/2;
    }
    printf("%d",mid);
    return 0;
}
