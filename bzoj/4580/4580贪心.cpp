#include<cstdio>
using namespace std;
int n;
int a[249];
int main()
{
    int i,j,k=50,l,ans=0,r;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(i=1;i<=k;i++)
    {
        for(j=1;j<=n;j++)
        if(a[j]==i)
        {
            l=j;
            while(a[j]==i&&j<=n)
                j++;
            j--;
            if((j-l+1)%2==0)
            {
                for(r=(l+j)/2+1;r<=n-(j-l+1)/2;r++)
                    a[r]=a[r+(j-l+1)/2];
                n=n-(j-l+1)/2;
                for(r=l;r<=(l+j)/2;r++)
                    a[r]++;
                j=r-1;
            }
            else
            {
                for(r=l;r<=j;r++)
                    a[r]++;
                a[(r+l)/2]--;
            }
            if(a[l]>k)k=a[l];
        }
    }
    for(i=1;i<=n;i++)
        if(a[i]>ans)
            ans=a[i];
    printf("%d",ans);
    return 0;
}
