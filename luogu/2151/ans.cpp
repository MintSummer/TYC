#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
inline ll read(){
    ll re=0,flag=1;char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-') flag=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') re=(re<<1)+(re<<3)+ch-'0',ch=getchar();
    return re*flag;
}
ll MOD=45989;
ll n,m,op,ed,tt,cnt=0,first[110];
struct edge{//邻接表存边
    ll next,to;
}a[150];
inline void add(ll u,ll v){//矩阵结构体
    a[++cnt]=(edge){first[u],v};first[u]=cnt;
    a[++cnt]=(edge){first[v],u};first[v]=cnt;
}
struct ma{
    ll a[150][150],n,m;
    ma(){memset(a,0,sizeof(a));n=m=0;}
    void clear(){memset(a,0,sizeof(a));n=m=0;}
    const ma operator *(const ma &b){
        ma re;re.n=n;re.m=b.m;ll i,j,k;
        for(i=1;i<=n;i++){
            for(k=1;k<=m;k++){
                if(!a[i][k]) continue;
                for(j=1;j<=b.m;j++){
                    re.a[i][j]+=(a[i][k]*b.a[k][j]);
                    re.a[i][j]%=MOD;
                }
            }
        }
        return re;
    }
    const void operator =(const ma &b){
        n=b.n;m=b.m;ll i,j;
        for(i=1;i<=n;i++) for(j=1;j<=m;j++) a[i][j]=b.a[i][j];
    }
}A,B;
void qpow(ma &x,ma y,ll T){
    while(T){
        if(T&1) x=x*y;
        y=y*y;T>>=1;
    }
}
ll o(ll x){return ((x%2)?(x+1):(x-1));}//求一条边的反向边（因为我是一开始编号的，所以不方便直接异或）
int main(){
    memset(first,-1,sizeof(first));ll i,t1,t2,j,u;
    n=read();m=read();tt=read();op=read();ed=read();op++;ed++;
    for(i=1;i<=m;i++){
        t1=read();t2=read();t1++;t2++;
        add(t1,t2);
    }
    A.n=1;A.m=B.m=B.n=cnt;
    for(j=1;j<=cnt;j++){//构造转移矩阵
        u=a[j].to;
        for(i=first[u];~i;i=a[i].next){
            if(i==o(j)) continue;
            B.a[j][i]+=1;
        }
    }
    for(i=first[op];~i;i=a[i].next){//构造初始矩阵
        A.a[1][i]+=1;
    }
    qpow(A,B,tt-1);ll ans=0;
    for(i=first[ed];~i;i=a[i].next){//统计答案
        ans=(ans+A.a[1][o(i)])%MOD;
    }
    printf("%lld",ans);
}