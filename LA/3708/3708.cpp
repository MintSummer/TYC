#include<cstdio>
#include<cmath>
using namespace std;
const double eps=1e-8;
int n,m;

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
	double ans=0;
	for(int i=1;i<n;i++)//假定有一个不动
	{
	    double pos=(double)i/n*(n+m);
	    //确定现在这个柱子的位置是圆上的(n+m）分之几
	    ans+=fabs(pos-floor(pos+0.5))/(n+m);//floor下取整，+0.5为了四舍五入
	    //如果pos离下一个柱子近，那么floor(~)就会表示为现在需要的位置上这个位置的下一个位置，就求出了移动的距离，反之同理
	    //真是巧妙地不行啊……感谢lrj大佬
	}
	printf("%.4lf\n",ans*10000);
	//前面全部用分数表示，表示为单位1的几分之几，所以最后要乘上单位1的真实值10000
    }
    return 0;
}
