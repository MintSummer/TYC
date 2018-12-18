#include<bits/stdc++.h>
using namespace std;
const int MAXN=20010;
int n,k,m=20000,a[MAXN],sa[MAXN],w[MAXN],wv[MAXN],x[MAXN],y[MAXN];
int rank[MAXN],height[MAXN];
int h,t,ans,q[MAXN];
//听说不用离散化…… 

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

bool cmp(int i,int j,int len)
{
    return y[i]==y[j]&&y[i+len]==y[j+len];
}

void get_sa(int n)
{
    for(int i=0;i<m;i++) w[i]=0;
    for(int i=0;i<n;i++) w[x[i]=a[i]]++;
    for(int i=1;i<m;i++) w[i]+=w[i-1];
    for(int i=n-1;i>=0;i--) sa[--w[x[i]]]=i;

    for(int j=1;j<n;j<<=1)	
    {
    	int p=0;
        for(int i=n-j;i<n;i++) y[p++]=i;
        for(int i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        
        for(int i=0;i<n;i++) wv[i]=x[y[i]];  
        for(int i=0;i<m;i++) w[i]=0;
        for(int i=0;i<n;i++) w[wv[i]]++;
        for(int i=1;i<m;i++) w[i]+=w[i-1];
        for(int i=n-1;i>=0;i--) sa[--w[wv[i]]]=y[i];
    
        swap(x,y);
        p=1,x[sa[0]]=0;
        for(int i=1;i<n;i++) 
            x[sa[i]]=cmp(sa[i-1],sa[i],j)?p-1:p++;
        if(p>=n) break;
        m=p;
    }
}

void get_height(int n)
{
    for(int i=0;i<=n;i++) rank[sa[i]]=i;
    int i,j,k;
    for(i=k=0;i<n;height[rank[i++]]=k)
        for(k?k--:0,j=sa[rank[i]-1];a[i+k]==a[j+k];k++);
}

bool check(int x)
{
    int i=1;
    while(true)
    {
        for(;i<=n&&height[i]<x;i++);
        if(i>n) break;
        int cnt=1;
        for(;i<=n&&height[i]>=x;cnt++,i++);
        if(cnt>=k) return true;
    }
    return false;
}

int main()
{
    //freopen("2852.in","r",stdin);
    //freopen("TYC.out","w",stdout);
    n=read(),k=read();
    for(int i=0;i<n;i++) a[i]=read();
    a[n]=0;
    get_sa(n+1);
    get_height(n);
    
    int lt=1,rt=n,mid;
    while(lt<=rt)
    {
        int mid=(lt+rt)>>1;
        if(check(mid)) ans=mid,lt=mid+1;
        else rt=mid-1;
    }
    printf("%d",ans);
    return 0;
}
