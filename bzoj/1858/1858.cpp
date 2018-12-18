#include<iostream>
#include<cstdio>
#define N 100005
using namespace std;
int n,m; 
struct seg
{
    int l,r;
    int l0,l1,r0,r1,mx0,mx1,sum0,sum1;
    int rev,c,full;
    }t[N<<2];
void rev(int k)
{
    swap(t[k].l0,t[k].l1);
    swap(t[k].r0,t[k].r1);
    swap(t[k].mx0,t[k].mx1);
    swap(t[k].sum0,t[k].sum1);
    if(t[k].full!=-1)t[k].full^=1;
}
void color(int k,int v)
{
    t[k].rev=0;
    int s=t[k].r-t[k].l+1;
    if(v==0)
    {
       t[k].sum0=t[k].l0=t[k].r0=t[k].mx0=s;
       t[k].sum1=t[k].l1=t[k].r1=t[k].mx1=0;
    }
    else
    {
       t[k].sum0=t[k].l0=t[k].r0=t[k].mx0=0;
       t[k].sum1=t[k].l1=t[k].r1=t[k].mx1=s;
    }
    t[k].full=v;
}
seg merge(seg a,seg b) 
{
    seg tmp;tmp.l=a.l;tmp.r=b.r;
    tmp.rev=0;tmp.c=-1;
    tmp.l0=a.l0;tmp.l1=a.l1;
    tmp.r0=b.r0;tmp.r1=b.r1;
    tmp.mx0=max(a.mx0,b.mx0);
    tmp.mx1=max(a.mx1,b.mx1);
    tmp.mx0=max(tmp.mx0,a.r0+b.l0);
    tmp.mx1=max(tmp.mx1,a.r1+b.l1);
    tmp.sum0=a.sum0+b.sum0;
    tmp.sum1=a.sum1+b.sum1;
    if(a.full==0)tmp.l0=a.mx0+b.l0;
    else if(a.full==1)tmp.l1=a.mx1+b.l1;
    if(b.full==0)tmp.r0=b.mx0+a.r0;
    else if(b.full==1)tmp.r1=b.mx1+a.r1;
    if(a.full==b.full)
       tmp.full=a.full;
    else tmp.full=-1;
    return tmp;
}
void pushup(int k)
{
    t[k]=merge(t[k<<1],t[k<<1|1]);
}
void pushdown(int k)
{
    if(t[k].l==t[k].r)return;
    if(t[k].c!=-1)
    {
        t[k<<1].c=t[k<<1|1].c=t[k].c;
        color(k<<1,t[k].c);color(k<<1|1,t[k].c);
        t[k].c=-1;
    }
    if(t[k].rev)
    {
        t[k<<1].rev^=1;
        t[k<<1|1].rev^=1;
        rev(k<<1);rev(k<<1|1);
        t[k].rev=0;
    }
}
void build(int k,int l,int r)
{
    t[k].l=l;t[k].r=r;
    t[k].c=-1;
    if(l==r)
    {
        scanf("%d",&t[k].full);
        if(t[k].full)
        {t[k].l1=t[k].r1=t[k].mx1=t[k].sum1=1;}
        else
        {t[k].l0=t[k].r0=t[k].mx0=t[k].sum0=1;}
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);build(k<<1|1,mid+1,r);
    pushup(k);
}
void change(int k,int x,int y,int v)
{
    pushdown(k);
    int l=t[k].l,r=t[k].r;
    if(l==x&&r==y)
    {
        color(k,v);
        t[k].c=v;
        return;
    }
    int mid=(l+r)>>1;
    if(mid>=y)change(k<<1,x,y,v);
    else if(mid<x)change(k<<1|1,x,y,v);
    else
    {
        change(k<<1,x,mid,v);
        change(k<<1|1,mid+1,y,v);
    }
    pushup(k);
}
void rever(int k,int x,int y)
{
    pushdown(k);
    int l=t[k].l,r=t[k].r;
    if(l==x&&r==y)
    {
        rev(k);
        t[k].rev=1;
        return;
    }
    int mid=(l+r)>>1;
    if(mid>=y)rever(k<<1,x,y);
    else if(mid<x)rever(k<<1|1,x,y);
    else
    {
        rever(k<<1,x,mid);
        rever(k<<1|1,mid+1,y);
    }
    pushup(k);
}
seg ask(int k,int x,int y)
{
    pushdown(k);
    int l=t[k].l,r=t[k].r;
    if(l==x&&y==r)return t[k];
    int mid=(l+r)>>1;
    if(mid>=y)return ask(k<<1,x,y);
    else if(mid<x)return ask(k<<1|1,x,y);
    else return merge(ask(k<<1,x,mid),ask(k<<1|1,mid+1,y));
}
int asksum(int k,int x,int y)
{
    pushdown(k);
    int l=t[k].l,r=t[k].r;
    if(l==x&&y==r)return t[k].sum1;
    int mid=(l+r)>>1;
    if(mid>=y)return asksum(k<<1,x,y);
    else if(mid<x)return asksum(k<<1|1,x,y);
    else return asksum(k<<1,x,mid)+asksum(k<<1|1,mid+1,y);
}
int main()
{
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int f,x,y;
        scanf("%d%d%d",&f,&x,&y);
        x++;y++;
        switch(f)
        {
            case 0:change(1,x,y,0);break;
            case 1:change(1,x,y,1);break;
            case 2:rever(1,x,y);break;
            case 3:printf("%d\n",asksum(1,x,y));break;
            case 4:printf("%d\n",ask(1,x,y).mx1);break;
        }
    }
    return 0;
}
