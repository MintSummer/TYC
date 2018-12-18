#include<bits/stdc++.h>
using namespace std;
const int F=10;
const int MAXN=200010;
int n,m,block,tot,rp,belong[MAXN],ans[MAXN],arr[MAXN];
int cnt[MAXN],num[MAXN];//cnt[i]表示i出现的次数,num[i]表示出现次数为i的数有多少个
map<int,int> id;

inline int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct node
{
    int x,id;
    bool operator < (const node &a) const
    {
		return (x<a.x)||(x==a.x&&id<a.id);
    }
}a[MAXN];

struct Query
{
    int l,r,id;
    bool operator < (const Query &a) const
    {
		return belong[l]==belong[a.l]?r<a.r:l<a.l;
    }
}q[MAXN];

void change(int x,int val)
{
    int before=cnt[x];
    if(val==1&&before==rp) rp++;
    if(val==-1&&before==rp&&num[before+F]==1) rp--;
    num[before+F]--;
    num[before+F+val]++;
    cnt[x]+=val;
}

void MoQu()
{
    int lt=1,rt=0;
    num[0]=tot;
    for(int i=1;i<=m;i++)
    {
		while(lt<q[i].l) change(arr[lt++],-1);
		while(lt>q[i].l) change(arr[--lt],1);
		while(rt<q[i].r) change(arr[++rt],1);
		while(rt>q[i].r) change(arr[rt--],-1);
		ans[q[i].id]=-rp;
    }
}

int main()
{
    n=read(),m=read();
    block=sqrt(n);
    for(int i=1;i<=n;i++)
		a[i].x=read(),a[i].id=i,belong[i]=i/block+1;
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
    {
		if(i==1||a[i].x!=a[i-1].x) tot++;
		arr[a[i].id]=tot;
    }
    //离散化
    for(int i=1;i<=m;i++)
		q[i].l=read(),q[i].r=read(),q[i].id=i;
    sort(q+1,q+1+m);
    MoQu();
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}
