#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
 
using namespace std;
 
namespace Tzh{
     
    const int maxn=510,maxm=60010;
    int cnt,g[maxn][maxn],n,m,tot,ans[maxm],id[maxm],qu1[maxm],qu2[maxm];
 
    struct Change
    {
        int x,y,val;
    }c[maxn*maxn];
 
    struct node
    {
        int x,y,xx,yy,k;
    }q[maxm];
 
    int ask(int x,int y)
    { 
    	int sum=0;
        for(int i=x;i;i-=lowbit(i))
            for(int j=y;j;j-=lowbit(j))
                sum+=g[i][j];
        return sum;
    }
 
    int ask(int x,int y,int xx,int yy)
    {
        return ask(xx,yy)+ask(x-1,y-1)-ask(xx,y-1)-ask(x-1,yy);
    }
 
    void add(int x,int y,int type)
    {
        for(int i=x;i<=n;i+=lowbit(i))
            for(int j=y;j<=n;j+=lowbit(j))
                g[i][j]+=type;
    }   
 
    bool cm(Change a,Change b)
    {
        return a.val<b.val;
    }
 
    void solve(int lt,int rt,int h,int t){ 
    	int mid=(lt+rt)>>1;
        if(lt==rt||h>t) return ;
        while(cnt<tot&&c[cnt+1].val<=mid) 
            cnt++,add(c[cnt].x,c[cnt].y,1);
        while(cnt>0&&c[cnt].val>mid)
            add(c[cnt].x,c[cnt].y,-1),cnt--;
        int cnt1=0,cnt2=0;
        for(int i=h;i<=t;i++)
        {
        	int tmp=ask(q[id[i]].x,q[id[i]].y,q[id[i]].xx,q[id[i]].yy);
            if(tmp<q[id[i]].k) qu2[++cnt2]=id[i];
            else ans[id[i]]=mid,qu1[++cnt1]=id[i];
        }
        for(int i=1;i<=cnt1;i++) id[h+i-1]=qu1[i];
        for(int i=1;i<=cnt2;i++) id[h+cnt1+i-1]=qu2[i];
        solve(lt,mid,h,h+cnt1-1);
        solve(mid+1,rt,h+cnt1,t);
    }   
 
    void work(){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) 
        	for(int j=1;j<=n;j++)
        	{
            	c[++tot].x=i;
            	c[tot].y=j; 
            	scanf("%d",&c[tot].val);
        	} 
        sort(c+1,c+tot+1,cm);
        for(int i=1;i<=m;i++) 
            scanf("%d%d%d%d%d",&q[i].x,&q[i].y,&q[i].xx,&q[i].yy,&q[i].k);
        for(int i=1;i<=m;i++) id[i]=i;
        solve(0,1000000000,1,m); 
        for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
        return ;
    }
}
 
int main(){
    Tzh::work();
    return 0;
}
