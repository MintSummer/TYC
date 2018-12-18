#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;

double dfs(double x,double y,int n)//n为剩余要切的块数
{
    if(n==1) return x>y?x/y:y/x;//只剩一块了
    double ans=1e10;
    //考虑将这一块分成两部分，其中一部分占(当前)全部的i/n,即这一块切给i个人
    for(int i=1;i<=n/2;i++)//因为不分左右，只用枚举到n/2即可
    {
		double cutx=x*i/n/*横着切*/,cuty=y*i/n/*竖着切*/;
		ans=min(ans,max(dfs(cutx,y,i),dfs(x-cutx,y,n-i)));
		ans=min(ans,max(dfs(x,cuty,i),dfs(x,y-cuty,n-i)));
    }
    return ans;
}

int main()
{
    double x,y;
    int n;
    scanf("%lf%lf%d",&x,&y,&n);
    printf("%.6lf",dfs(x,y,n));
    return 0;
}
