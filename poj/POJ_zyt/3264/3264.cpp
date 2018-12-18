#include<cstdio>
#include<algorithm>
using namespace std;
struct group
{
       int minn;
       int maxx;
}tree[100010];
int cow[50010],n,q;
void build(int root,int l,int r)
{
     if(r-l<=1)
     {
               tree[root]=(group){min(cow[l],cow[r]),max(cow[l],cow[r])};
               return;
     }
     int mid=(l+r)/2;
     build(root*2+1,l,mid);
     build(root*2+2,mid+1,r);
     tree[root].minn=min(tree[root*2+1].minn,tree[root*2+2].minn);
     tree[root].maxx=max(tree[root*2+1].maxx,tree[root*2+2].maxx);
}
group search(int root,int l,int r,int a,int b)
{
      if(l>=a&&r<=b);
      {
                 return tree[root];
      }
      int mid=(l+r)/2;
      group ans;
      if(b<=mid)
                 ans=search(root*2+1,l,mid,a,b);
      else if(a>=mid+1)
                 ans=search(root*2+2,mid+1,r,a,b);
      else
      {
          group g1=search(root*2+1,l,mid,a,b);
          group g2=search(root*2+2,mid+1,r,a,b);
          ans=(group){min(g1.minn,g2.minn),max(g1.maxx,g2.maxx)};
      }
      return ans;
}
int main(void)
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%d",cow+i);
    build(0,1,n);
    while(q--)
    {
              int a,b;
              scanf("%d%d",&a,&b);
              group g=search(0,1,n,a,b);
              printf("%d\n",g.maxx-g.minn);
    }
    return 0;
}
