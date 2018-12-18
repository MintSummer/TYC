#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
using namespace std;
int n;
double xx,yy,ans,t;
struct point{double x,y;}p[105];
double sqr(double x){return x*x;}
double dis(double x,double y,point p)
{return sqrt(sqr(x-p.x)+sqr(y-p.y));}
double getsum(double x,double y)
{
    double tmp=0;
    for(int i=1;i<=n;i++)
        tmp+=dis(x,y,p[i]);
    return tmp;
}
int main()
{
    srand(time(0));
    while(scanf("%d",&n)!=EOF)
    {
        xx=yy=0;ans=1e20;t=100000;
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
            xx+=p[i].x;yy+=p[i].y;
        }
        xx/=n;yy/=n;
        ans=getsum(xx,yy);
        double tmp,x,y;
        while(t>0.02)
        {
            x=y=0;
            for(int i=1;i<=n;i++)
            {
                x+=(p[i].x-xx)/dis(xx,yy,p[i]);
                y+=(p[i].y-yy)/dis(xx,yy,p[i]);
            }
            tmp=getsum(xx+x*t,yy+y*t);
            if(tmp<ans)
            {ans=tmp;xx+=x*t,yy+=y*t;}
            else if(log((tmp-ans)/t)<(rand()%10000)/10000.0)
            {ans=tmp;xx+=x*t,yy+=y*t;}       
            t*=0.9; 
        }
        printf("%.0lf\n",ans);
    }
    return 0;
}
