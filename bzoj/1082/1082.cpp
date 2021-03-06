/*
首先二分答案x，那么剪下来的一定是最小的x个，然后枚举每一个从哪块上切下来就行了。有以下优化：
1.将两个数组分别排序。那么所需要的木板一定是从大到小枚举，同时枚举每一个所需要的木板时，按照提供的木板的大小从小到大枚举能不能切去，这样容易回溯。
2.对于一块提供的木板，如果其长度小于需要的最小的木板，那么剩下来的部分一定浪费了。记一个变量waste表示浪费的部分，那么如果waste+所需要的木板总长度>提供的木板总长度，直接回溯。
3.对于相邻的两块所需要的木板，如果长度相等，那么后一块直接从前一块上次放的那一块开始枚举，避免重复运算。
*/
#include<bits/stdc++.h>
using namespace std;
int n,m,a[60],b[1010],flag,cutby[1010],lt,rt,mid,ans;
long long suma,sumb[1010];

void dfs(int now,int ned,int waste)
{
    if(ned==0) flag=1;
    while(now<=n&&a[now]<b[1]) waste+=a[now],now++;
    if(now>n||flag||waste+sumb[ned]>suma) return;
    
    int st=now;
    if(b[ned]==b[ned+1]&&ned!=mid) st=cutby[ned+1];
    for(int i=st;i<=n;i++)
	if(a[i]>=b[ned])
	{
	    cutby[ned]=i;
	    a[i]-=b[ned];
	    dfs(now,ned-1,waste);
	    a[i]+=b[ned];
	}
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
	scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++) 
	scanf("%d",&b[i]);

    sort(a+1,a+1+n);
    sort(b+1,b+1+m);
    while(b[m]>a[n]) m--;
    int tot=0;
    for(int i=1;i<=n;i++) 
	if(a[i]>b[1]) a[++tot]=a[i];
    n=tot;
    for(int i=1;i<=n;i++) suma+=a[i];
    for(int i=1;i<=m;i++) sumb[i]=sumb[i-1]+b[i];

    lt=0,rt=m;
    while(lt<=rt)
    {
	mid=(lt+rt)>>1;
	flag=0;
	dfs(1,mid,0);
	if(flag) ans=mid,lt=mid+1;
	else rt=mid-1;
    }
    printf("%d",ans);
    return 0;
}
