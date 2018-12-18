#include<bits/stdc++.h>
using namespace std;

namespace calendar
{
    typedef long double ld;
    const int N=200010;
    const ld eps=1e-9;
    
    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
    
    struct WaterTaps
    {
        int mx,temp;
        ld mul;
        bool operator < (const WaterTaps &t) const
        {
            return temp<t.temp;
        }
    }a[N];
    
    void work()
    {
        int n=read(),T=read();
        for(int i=1;i<=n;i++) a[i].mx=read();
        for(int i=1;i<=n;i++) a[i].temp=read()-T;
        sort(a+1,a+1+n);
        if(a[1].temp>0||a[n].temp<0) 
        {
            printf("0.0000000000\n");
            return;
        } 
        int mid=0;
        for(int i=1;i<n;i++)
            if(a[i].temp<=0&&a[i+1].temp>0) mid=i;
    	if(!mid)
    	{
			ld Water=0;
			for(int i=n;i;i--)
			{
				if(a[i].temp<0) break;
				Water+=a[i].mx;
			}
            printf("%.9f\n",(double)Water);
            return;
        } 
        for(int i=1;i<=n;i++)
            a[i].mul=(ld)a[i].temp*a[i].mx;
        
        ld SumL=0.0,SumR=0.0,WaterL=0.0,WaterR=0.0,MaxWater=0.0;
        for(int i=1;i<=mid;i++) 
            SumL+=a[i].mul,WaterL+=a[i].mx;
        for(int i=mid+1;i<=n;i++) 
            SumR+=a[i].mul,WaterR+=a[i].mx;
            
        if(fabs(SumL)<fabs(SumR))
        {
            MaxWater=WaterL;
            for(int i=mid+1;i<=n;i++)
                if(SumL+a[i].mul>0)
                {
                    MaxWater+=-SumL/a[i].temp;
                    break;
                }
                else 
                    SumL+=a[i].mul,MaxWater+=a[i].mx;
        }
        else
        {
            MaxWater=WaterR;
            for(int i=mid;i;i--)
                if(SumR+a[i].mul<0)
                {
                    MaxWater+=-SumR/a[i].temp;
                    break;
                }
                else
                    SumR+=a[i].mul,MaxWater+=a[i].mx;
        }
        printf("%.9f",(double)MaxWater);
    }
}

int main()
{
    calendar::work();
    return 0;
}
