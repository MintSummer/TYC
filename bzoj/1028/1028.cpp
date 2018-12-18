#include<bits/stdc++.h>
using namespace std;
int n,m,a[410],ans[410],tmp[410];

bool check()
{
    bool flag=false;
    for(int i=1;i<=n;i++)
	if(a[i]>=2)//枚举对子，看该对子是否可以和
	//然后判断剩余的牌能否分组，分组的时候优先考虑组成刻子，再考虑组成顺子 
	{
	    flag=true;
	    a[i]-=2;
	    for(int j=1;j<=n+2;j++) tmp[j]=a[j];
	    for(int j=1;j<=n+2;j++)
	    {
		if(tmp[j]<0){flag=false;break;}
		tmp[j]%=3;
		tmp[j+1]-=tmp[j];
		tmp[j+2]-=tmp[j];
	    }
	    a[i]+=2;
	    if(flag) return true;
	}
    return false;
}

int main()
{
    scanf("%d%d",&n,&m);
    int x,cnt=0;
    for(int i=1;i<=m*3+1;i++)
	scanf("%d",&x),a[x]++;
    for(int i=1;i<=n;i++)
    {
	a[i]++;
	if(check()) ans[++cnt]=i;
	a[i]--;
    }
    if(!cnt) {printf("NO");return 0;}
    else for(int i=1;i<cnt;i++)
	printf("%d ",ans[i]);
    printf("%d",ans[cnt]);
    return 0;
}
