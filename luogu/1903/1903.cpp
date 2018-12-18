#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e6+10;
int n,m,totq,totc,bask,ans,a[MAXN],belong[MAXN],cnt[MAXN],Ans[MAXN];

inline int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct Query
{
    int id,l,r,pre;
}q[MAXN];

struct Change
{
    int pos,val;
}c[MAXN];

bool cmp(const Query &x,const Query &y)
{
    if(belong[x.l]!=belong[y.l]) return belong[x.l]<belong[y.l];
    if(belong[x.r]!=belong[y.r]) return belong[x.r]<belong[y.r];
    return x.pre<y.pre;
}

void add(int x)
{
    if(++cnt[x]==1) ans++;
}

void del(int x)
{
    if(--cnt[x]==0) ans--;
}

void change(int now,int i)
{
    if(c[now].pos>=q[i].l&&c[now].pos<=q[i].r)
    {
        if(--cnt[a[c[now].pos]]==0) ans--;
        if(++cnt[c[now].val]==1) ans++;
    }
    swap(c[now].val,a[c[now].pos]);
}

void Mo()
{
    int lt=1,rt=0,now=0;
    for(int i=1;i<=totq;i++)
    {
        while(lt<q[i].l) del(a[lt++]);
        while(lt>q[i].l) add(a[--lt]);
        while(rt<q[i].r) add(a[++rt]);
        while(rt>q[i].r) del(a[rt--]);
        while(now<q[i].pre) change(++now,i);
        while(now>q[i].pre) change(now--,i);
        Ans[q[i].id]=ans;
    }
    for(int i=1;i<=totq;i++) 
    printf("%d\n",Ans[i]);
}

int main()
{
    n=read(),m=read();
    bask=pow(n,2.0/3.0);//带修莫队的块为n的2/3次方
    for(int i=1;i<=n;i++)
    a[i]=read(),belong[i]=(i-1)/bask+1;
    char ch[5];
    while(m--)
    {
        scanf("%s",ch);
        if(ch[0]=='Q')
        {
            q[++totq].l=read(),q[totq].r=read();
            q[totq].pre=totc;
            q[totq].id=totq;
        }
        else c[++totc].pos=read(),c[totc].val=read();
    }
    sort(q+1,q+1+totq,cmp);
    Mo();
    return 0;
}
