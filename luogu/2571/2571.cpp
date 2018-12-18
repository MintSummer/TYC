#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cmath>
using namespace std;

namespace TYC
{
    const double eps=1e-5;
    double Ax,Ay,Bx,By,Cx,Cy,Dx,Dy,P,Q,R;

    double sqr(double x)
    {
        return x*x;
    }

    double dis(double x1,double y1,double x2,double y2)
    {
        return sqrt(sqr(x2-x1)+sqr(y2-y1));
    }

    double len(double x1,double y1,double x2,double y2)
    {
        return dis(Ax,Ay,x1,y1)/P+dis(x1,y1,x2,y2)/R+dis(x2,y2,Dx,Dy)/Q;
    }

    double query(double x,double y)
    {
        double lx=Cx,ly=Cy,rx=Dx,ry=Dy,ans;
        while(fabs(rx-lx)>=eps||fabs(ry-ly)>=eps)
        {
            double midx=(lx+rx)/2.0,midy=(ly+ry)/2.0;
            double lmidx=(lx+midx)/2.0,lmidy=(ly+midy)/2.0;
            double ans1=len(x,y,midx,midy),ans2=len(x,y,lmidx,lmidy);
            if(ans1>ans2) rx=midx,ry=midy;
            else lx=lmidx,ly=lmidy;
            ans=min(ans1,ans2);
        }
        return ans;
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>Ax>>Ay>>Bx>>By>>Cx>>Cy>>Dx>>Dy;
        cin>>P>>Q>>R;
        double lx=Ax,ly=Ay,rx=Bx,ry=By,ans;
        do
        {
            double midx=(lx+rx)/2.0,midy=(ly+ry)/2.0;
            double lmidx=(lx+midx)/2.0,lmidy=(ly+midy)/2.0;
            double ans1=query(midx,midy),ans2=query(lmidx,lmidy);
            if(ans1>ans2) rx=midx,ry=midy;
            else lx=lmidx,ly=lmidy;
            ans=min(ans1,ans2);
        }
        while(fabs(rx-lx)>=eps||fabs(ry-ly)>=eps);
        cout<<fixed<<setprecision(2)<<ans;
    }
}

int main()
{
    TYC::work();
    return 0;
}
