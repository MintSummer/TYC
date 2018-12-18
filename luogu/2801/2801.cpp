#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
int n,m,block,tot,belong[MAXN],cnt[MAXN],l[MAXN],r[MAXN],tag[MAXN],re[MAXN];
//re[i]表示是否要重新排序块i，只有单独加的小块需要重新排序，统一加地顺序不变
//大力加标记，速度翻一番 

struct node
{
    int x,id;
    bool operator < (const node &d) const
    {
        return (x<d.x)||(x==d.x&&id<d.id);
    }
}a[MAXN];

void add(int lt,int rt,int val)
{
    for(int i=belong[lt]+1;i<belong[rt];i++) tag[i]+=val;
    for(int i=l[belong[lt]];i<=r[belong[lt]];i++)
        if(a[i].id>=lt&&a[i].id<=rt) a[i].x+=val;
    re[belong[lt]]=1;
    if(belong[lt]==belong[rt]) return;
    for(int i=l[belong[rt]];i<=r[belong[rt]];i++)
        if(a[i].id>=lt&&a[i].id<=rt) a[i].x+=val;
    re[belong[rt]]=1;
}

int find(int x,int val)
{
    int lt=l[x],rt=r[x],mid,ans=r[x]+1;//小心，可能有整个块都没有大于val的情况 
    while(lt<=rt)
    {
        mid=(lt+rt)>>1;
        if(a[mid].x>=val) ans=mid,rt=mid-1;
        else lt=mid+1;
    }
    return r[x]-ans+1;
}

int get_ans(int lt,int rt,int val)
{
    int ans=0;
    for(int i=belong[lt]+1;i<belong[rt];i++)
    {
        if(re[i]) {sort(a+l[i],a+r[i]+1);re[i]=0;}
        ans+=find(i,val-tag[i]);
    }
    int x=belong[lt];
    for(int i=l[x];i<=r[x];i++)
        if(a[i].id>=lt&&a[i].id<=rt&&a[i].x>=val-tag[x]) ans++;
    if(belong[lt]==belong[rt]) return ans;
    x=belong[rt];
    for(int i=l[x];i<=r[x];i++)
        if(a[i].id>=lt&&a[i].id<=rt&&a[i].x>=val-tag[x]) ans++;
    return ans;
}

int main()
{
    scanf("%d%d",&n,&m);
    block=sqrt(n);
    for(int i=1;i<=n;i++) 
        scanf("%d",&a[i].x),a[i].id=i,belong[i]=(i-1)/block+1;
    tot=belong[n];
    for(int i=1;i<=tot;i++)
    {
        l[i]=r[i-1]+1;
		r[i]=((i==tot)?n:i*block);
        sort(a+l[i],a+r[i]+1);
    }
    char ch[5];
    int lt,rt,k;
    while(m--)
    {
        scanf("%s%d%d%d",ch,&lt,&rt,&k);
        if(ch[0]=='M') add(lt,rt,k);
        else printf("%d\n",get_ans(lt,rt,k));
    }
} 
