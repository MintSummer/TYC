#include<cstdio>
using namespace std;

int main()
{
    int a,ans,cnt=0,n;
    scanf("%d",&n);
    scanf("%d",&ans),cnt++;
    for(int i=2;i<=n;i++)
    {
		scanf("%d",&a);
		if(a!=ans) cnt--;
		else cnt++;
		if(!cnt) ans=a,cnt=1;
    }
    printf("%d",ans);
    return 0;
}
