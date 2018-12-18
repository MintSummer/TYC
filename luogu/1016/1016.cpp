#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int n,flag_have_ans=1;
    double TotDis,C,D,dis[10],price[10],ans,once;

    void search()
    {
        double res=0;
        for(int i=0,nxt;i<=n+1;i=nxt)
        {
            int flag_less=0,limit=i;
            for(int j=i+1;j<=n&&dis[j]-dis[i]<=once;j++) limit++;
            if(limit==i) {flag_have_ans=0;return;}
            for(int j=i+1;j<=limit;j++) 
                if(price[j]<price[i]) {flag_less=1;break;}
            if(!flag_less)
            {
                if(limit==n) 
                {
                    double oil=(dis[n]-dis[i])/D;
                    ans+=(oil-res)*price[i];
                    return;
                } 
                ans+=(C-res)*price[i];
                res=C;
                int to=i+1;
                for(int j=i+2;j<=limit;j++)
                    if(price[j]<=price[to]) to=j;
                if(to==-1) {flag_have_ans=0;return;}
                nxt=to;
                res=res-(dis[nxt]-dis[i])/D;
            }
            else 
            {
                int to=i;
                for(int j=i+1;j<=limit;j++)
                    if(price[j]<price[i]) {to=j;break;}
                nxt=to;
                double oil=(dis[nxt]-dis[i])/D;
                ans+=(oil-res)*price[i];
                res=0;
            }
        }
    }

    void work()
    {
        scanf("%lf%lf%lf%lf%d",&TotDis,&C,&D,&price[0],&n);
		dis[n+1]=TotDis;
		price[n+1]=1e18;
        once=C*D;
		for(int i=1;i<=n;i++)
			scanf("%lf%lf",&dis[i],&price[i]);
        if(!n&&TotDis>once) flag_have_ans=0;
        else n++,search();
        if(!flag_have_ans) printf("No Solution\n");
        else printf("%.2lf\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
