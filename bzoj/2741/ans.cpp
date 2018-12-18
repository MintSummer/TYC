#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 12100
#define M 800100
using namespace std;
int n,m;
int Block;
int a[N],size;
int lson[M],rson[M],siz[M];
int root[N],b[110][N];
void insert(int y,int &x,int num,int dep)
{
    x=++size;
    siz[x]=siz[y]+1;
    if(dep==-1)return;
    lson[x]=lson[y],rson[x]=rson[y];
    if((num&(1<<dep)))insert(rson[y],rson[x],num,dep-1);
    else insert(lson[y],lson[x],num,dep-1);
}
int query(int y,int x,int num)
{
    int ans=0;
    for(int i=30;i>=0;i--)
    {
        int tmp=num&(1<<i);
        if(!tmp)
        {
            if(siz[rson[x]]-siz[rson[y]]!=0)
            {
                ans+=(1<<i);
                x=rson[x],y=rson[y];
            }else x=lson[x],y=lson[y];
        }else
        {
            if(siz[lson[x]]-siz[lson[y]]!=0)
            {
                ans+=(1<<i);
                x=lson[x],y=lson[y];
            }else x=rson[x],y=rson[y];
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d",&n,&m);
    Block=(int)sqrt(n);
    int Size_Block=n/Block+(n%Block!=0);

    for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]^=a[i-1];
    for(int i=1;i<=n;i++)insert(root[i-1],root[i],a[i],30);
    for(int i=1;i<=Block;i++)
    {       
        for(int j=(i-1)*Size_Block+1;j<=n;j++)
        {
            b[i][j]=max(b[i][j-1],query(root[(i-1)*Size_Block],root[j],a[j]));
            if(i==1)b[i][j]=max(b[i][j],a[j]); 
        }
    }
    int lastans=0;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x=(x+lastans%n)%n+1,y=(y+lastans%n)%n+1;
        if(x>y)swap(x,y);
        x--;
        int numblock=x/Block+(x%Block!=0);
        int l1=numblock*Size_Block+1;
        lastans=0;
        if(l1<=y)lastans=b[numblock+1][y];
        l1=min(l1,y);
        for(int j=x;j<l1;j++)
        {
            lastans=max(lastans,query(root[x],root[y],a[j]));
        }
        printf("%d\n",lastans);
    }
}
