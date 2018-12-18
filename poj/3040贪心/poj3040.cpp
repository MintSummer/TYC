#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f 
using namespace std;
int use[30];//记录当前取法的第i种面值取的个数 
struct node
{
    int v,b;
}a[25];

int cmp(node a,node b)
{
    return a.v<b.v;
} 

int main()
{
    int n,c,i,cnt,ans,k,m;
    while(scanf("%d%d",&n,&c)!=EOF)
    {
        for(i=0;i<n;++i)
            scanf("%d%d",&a[i].v,&a[i].b);
        sort(a,a+n,cmp);
        ans=0;
        for(i=n-1;i>=0;i--)//第一步，满足大于C的面值全部取走 
        {
            if(a[i].v>=c)
            {
                ans+=a[i].b;
                a[i].b=0;
            }
        }
        while(1)//每次循环都在找一次当前最优取法，直到剩下的总金额小于C元 
        {
            int sign=0;
            cnt=c;
            memset(use,0,sizeof(use));
            for(i=n-1;i>=0;--i)//第二步，从大到小取，不能超过C的值 
            {
                if(a[i].b)
                {
                    k=cnt/a[i].v;
                    m=min(k,a[i].b);
                    cnt-=m*a[i].v;
                    use[i]=m;
                    if(cnt==0)
                    {
                        sign=1;
                        break;
                    }
                }
            }
            if(cnt>0)
            {
                for(i=0;i<n;++i)//第三步，从小到大取，凑满C 
                {
                    if(a[i].b>use[i])
                    {
                        while(use[i]<a[i].b)
                        {
                            cnt-=a[i].v;
                            use[i]++;
                            if(cnt<=0)
                            {
                                sign=1;
                                break;
                            }
                        }
                    }
                    if(sign)
                        break;
                }
            }
            if(!sign)
                break;
            m=INF;
            for(i=0;i<n;++i)
            {
                if(use[i])//找到当前取法的能取的总次数 
                    m=min(m,a[i].b/use[i]);
            }
            ans+=m;
            for(i=0;i<n;++i)
            {
                if(use[i])
                    a[i].b-=m*use[i];
            } 
        }
        printf("%d\n",ans);
    }
    return 0;
}