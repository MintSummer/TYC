#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f;
    int dep;
    struct node
    {
        int x,y,z;
        void sort()
        {
            if(x>y) swap(x,y);
            if(x>z) swap(x,z);
            if(y>z) swap(y,z);
        }
        bool operator == (const node &t) const
        {
            return (x==t.x)&&(y==t.y)&&(z==t.z);
        }
    }a,b;

    inline node find_root(node now,int res)
    {
        int tmp;
        for(dep=0;res;dep+=tmp)   
        {
            int d1=now.y-now.x,d2=now.z-now.y;
            if(d1==d2) return now;
            if(d1<d2) 
            {
                tmp=min((d2-1)/d1,res);
                now.x+=tmp*d1,now.y+=tmp*d1;
            }
            else
            {
                tmp=min((d1-1)/d2,res);
                now.y-=tmp*d2,now.z-=tmp*d2;
            }
            res-=tmp;
        }
		return now;
    }

    void work()
    {
        scanf("%d%d%d",&a.x,&a.y,&a.z);
        scanf("%d%d%d",&b.x,&b.y,&b.z);
        a.sort(),b.sort();
        node root=find_root(a,inf);
		int dep1=dep;
        node root2=find_root(b,inf);
		int dep2=dep;
        if(!(root==root2)) {puts("NO");return;} 
        if(dep1<dep2) swap(a,b),swap(dep1,dep2);
        a=find_root(a,dep1-dep2);
        int l=0,r=dep2,mid,ans;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(find_root(a,mid)==find_root(b,mid)) ans=mid,r=mid-1;
            else l=mid+1;
        }
        printf("YES\n%d\n",(ans<<1)+dep1-dep2);
    }
}

int main()
{
    TYC::work();
    return 0;
}
