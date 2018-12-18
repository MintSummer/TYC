#include<bits/stdc++.h>
using namespace std;
const int MAXN=1010; 
typedef long long ll;
int n,m;
 
ll C(int x)
{
    return (ll)x*(x-1)*(x-2)/6;//只用求C(x,3)的值 
}
 
inline int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}
 
inline ll get_ans()
{
     
}
 
int main()
{
    scanf("%d%d",&n,&m);
    n++,m++;//网格啊，顶点在点上 
    ll ans=C(n*m)-m*C(n)-n*C(m);//网格中任取三个点 ,并去掉三点在同一条网格线上的
    //考虑斜着的三点 
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)//枚举两坐标之差 
        {
            /*
            假定这两个点组成的线段是一个直角三角形的斜边，设一点坐标为(0,0)，另一点为(i,j)
            那么这两个点之间的点的个数(网格上整点)即为 
            */
            int tmp=gcd(i,j)-1; 
            if(tmp>=1) ans-=(ll)(n-i)*(m-j)*tmp*2;
        }
    printf("%lld",ans);
} 

