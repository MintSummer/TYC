//来自lyr大佬,快啊...我的3000ms+,他的1000ms+
#include<bits/stdc++.h>
using namespace std;
#define int long long 
inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch)){ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x;
}
const int N=100010;
struct node{
    int p,x,id,ans;
    bool operator <(const node&b)const{
        return id<b.id;
    }
}q[N],b[N];
int id[N],bk[N];
int s[N];
int n,m;
#define lb(x) x&-x
void update(int p,int x){
    while(p<=n){
        s[p]+=x;
        p+=lb(p);
    }
}
int query(int p){
    int ret=0;
    while(p){
        ret+=s[p];
        p-=lb(p);
    }
    return ret;
}
bool cmpp(node x,node y){return x.p<y.p;}
void cdq(int l,int r){
    if(l==r)return;
    int mid=(l+r)>>1;
    cdq(l,mid);cdq(mid+1,r);
    int lt=l,rt=mid+1;
    while(rt<=r){
        while(lt<=mid&&q[lt].p<q[rt].p){
            update(q[lt].x,1);
            lt++;
        }
        q[rt].ans+=lt-l-query(q[rt].x);
        rt++;
    }
    for(int i=l;i<lt;i++)update(q[i].x,-1);
    lt=mid,rt=r;
    while(rt>mid){
        while(lt>=l&&q[lt].p>q[rt].p){
            update(q[lt].x,1);
            lt--;
        }
        q[rt].ans+=query(q[rt].x);
        rt--;
    }
    for(int i=mid;i>lt;i--)update(q[i].x,-1);
    lt=l,rt=mid+1;
    for(int i=l;i<=r;i++)b[i]=((rt>r)||(lt<=mid&&q[lt].p<q[rt].p))?q[lt++]:q[rt++];
    for(int i=l;i<=r;i++)q[i]=b[i];
}
#undef int
int main(){
#define int long long 
    n=read();m=read();
    for(int i=1;i<=n;i++){
        int tmp=read();
        id[tmp]=i;
    }
    for(int i=1;i<=m;i++){
        q[i].x=read();
        q[i].p=id[q[i].x];
        q[i].id=n-i+1;
        bk[q[i].x]=1;
    }
    int cnt=m;
    for(int i=1;i<=n;i++)
        if(!bk[i]){
            q[++cnt].x=i;
            q[cnt].p=id[i];
            q[cnt].id=cnt-m;
        }
    sort(q+1,q+n+1);
    cdq(1,n);
    sort(q+1,q+n+1);
    for(int i=1;i<=n;i++)
        q[i].ans+=q[i-1].ans;
    for(int i=n;i>n-m;i--)
        printf("%lld\n",q[i].ans);
    return 0;
}
