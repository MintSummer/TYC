#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=50010;
int n,q[MAXN];
ll dp[MAXN],x[MAXN],y[MAXN];

struct earth
{
    ll x,y;
}e[MAXN];

bool cmp(earth a,earth b)
{
	return a.x==b.x?a.y<b.y:a.x<b.x;//����x��y��������
}

inline double k(int a,int b)
{
	return (double)(dp[b]-dp[a])/(y[a+1]-y[b+1]);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
        scanf("%lld%lld",&e[i].x,&e[i].y);
    sort(e+1,e+1+n,cmp);
    
    int tot=0;
    for(int i=1;i<=n;i++)
    {
        while(tot&&y[tot]<=e[i].y) tot--;//һ��Ҫ��= 
        x[++tot]=e[i].x,y[tot]=e[i].y;
    }//�ѿ��Ժ�i���һ�����ȥ��,Ȼ��ʹ��ʣ��һЩy�ݼ�x�����ľ���
	//��Ȼf[i]=min(f[j]+y[j+1]x[i])
	//б���Ż�:������(f[j]-f[k])/(y[k+1]-y[j+1])<x[i]
    int h=0,t=0;
    for(int i=1;i<=tot;i++)//ά��һ����͹��
    {
        while(h<t&&k(q[h],q[h+1])<x[i]) h++;
        dp[i]=dp[q[h]]+x[i]*y[q[h]+1];
        while(h<t&&k(q[t],i)<k(q[t-1],q[t])) t--;
        q[++t]=i;
    }
    printf("%lld",dp[tot]);
    return 0;
}
