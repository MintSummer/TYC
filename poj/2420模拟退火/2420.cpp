#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<ctime>
using namespace std;

namespace TYC
{
    const double delta=0.996;
    const int dx[5]={0,0,0,1,-1},dy[5]={0,1,-1,0,0};
    int n;
    struct node
    {
        double x,y;
    }a[110],fir;

    inline double sqr(double r)
    {
        return r*r;
    }

    inline double dis(double x1,double y1,double x2,double y2)
    {
        return sqrt(sqr(x2-x1)+sqr(y2-y1));
    }

    inline double get_ans(node now)
    {
        double ans=0;
        for(int i=1;i<=n;i++) 
            ans+=dis(now.x,now.y,a[i].x,a[i].y);
        return ans;
    }

    double climb_mountains()
    {
        double T=100.0,ans=1e18;
        while(T>1e-3)
        {
            int flag=1;
			while(flag)
			{
				flag=0;
				for(int i=1;i<=4;i++)
				{
					node tmp;
					tmp.x=fir.x+dx[i]*T,tmp.y=fir.y+dy[i]*T;
					if(tmp.x<0||tmp.x>10000||tmp.y<0||tmp.y>10000) continue;
					double new_ans=get_ans(tmp);
					if(new_ans<ans) 
						flag=1,ans=new_ans,fir=tmp;
				}
			}
        	T*=delta;
		}
		return ans;
    }

    void work()
    {
        scanf("%d",&n);
        fir=(node){0,0};
        for(int i=1;i<=n;i++)
            scanf("%lf%lf",&a[i].x,&a[i].y);
        printf("%.0f\n",climb_mountains());
        //用%lf会WA
    }
}

int main()
{
    TYC::work();
    return 0;
}
