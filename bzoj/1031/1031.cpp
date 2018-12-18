#include<bits/stdc++.h>
using namespace std;
const int MAXN=400040;
char ch[MAXN/2];
int n,sa[MAXN],a[MAXN],w[MAXN],x[MAXN],y[MAXN];

bool cmp(int i,int j,int len)
{
    return y[i]==y[j]&&y[i+len]==y[j+len];
}

void get_sa()
{
    int m=1010;
    for(int i=0;i<=m;i++) w[i]=0;
    for(int i=1;i<=n;i++) w[x[i]=a[i]]++;
    for(int i=1;i<=m;i++) w[i]+=w[i-1];
    for(int i=n;i;i--) sa[w[x[i]]--]=i;
    
    for(int k=1,p=0;k<=n&&p<n;k<<=1,m=p,p=0)
    {
        for(int i=n-k+1;i<=n;i++) y[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>k) y[++p]=sa[i]-k;
        
        for(int i=0;i<=m;i++) w[i]=0;
        for(int i=1;i<=n;i++) w[x[y[i]]]++;
        for(int i=1;i<=m;i++) w[i]+=w[i-1];
        for(int i=n;i;i--) sa[w[x[y[i]]]--]=y[i];
        
        swap(x,y);
        p=x[sa[1]]=1;
        for(int i=2;i<=n;i++)
            x[sa[i]]=cmp(sa[i-1],sa[i],k)?p:++p;
    } 
}

int main()
{
    scanf("%s",ch);
    n=strlen(ch);
    for(int i=1;i<=n;i++) 
        a[i]=ch[i-1],ch[i+n-1]=ch[i-1],a[i+n]=a[i];
    n<<=1;
    get_sa();
    for(int i=1;i<=n;i++)
        if(sa[i]<=n/2) 
            printf("%c",ch[sa[i]+n/2-2]);
    return 0;
}
