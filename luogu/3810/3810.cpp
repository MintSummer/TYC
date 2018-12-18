#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,k,C[MAXN*2],ans[MAXN];

inline int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct node
{
    int a,b,c,cnt,sum;
    //cnt表示跟它a、b、c均相等的个数，sum表示排在它前面的数的个数
    bool operator != (const node &d) const
    {
		return a!=d.a||b!=d.b||c!=d.c;
    }
}a[MAXN];

bool cmp1(const node &x,const node &y)
{
    if(x.a!=y.a) return x.a<y.a;
    if(x.b!=y.b) return x.b<y.b;
    return x.c<y.c;
}

bool cmp2(const node &x,const node &y)
{
    return x.b<y.b;
}

int lowbit(int x) {return x&(-x);}

void add(int x,int val) 
{
    for(;x<=k;x+=lowbit(x)) C[x]+=val;
}

int ask(int x)
{
    int sum=0;
    for(;x;x-=lowbit(x)) sum+=C[x];
    return sum;
}

void CDQ(int lt,int rt)
{
    if(lt==rt) return;
    int mid=(lt+rt)>>1;
    CDQ(lt,mid),CDQ(mid+1,rt);
    sort(a+lt,a+mid+1,cmp2);
    sort(a+mid+1,a+rt+1,cmp2);
    int i=lt;
    for(int j=mid+1;j<=rt;j++)
    {
		while(i<=mid&&a[i].b<=a[j].b)
			add(a[i].c,a[i].cnt),i++;
		a[j].sum+=ask(a[j].c);
    }
    for(i--;i>=lt;i--) add(a[i].c,-a[i].cnt);
    //清空刚刚加的部分，可能加的不是特别多，这样比memset更优
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++) 
		a[i].a=read(),a[i].b=read(),a[i].c=read();
		
    sort(a+1,a+1+n,cmp1);
    int tot=0;
    for(int i=1;i<=n;i++)
    {
		if(i==1||a[i]!=a[tot]) a[++tot]=a[i];
		a[tot].cnt++;
    }
    CDQ(1,tot);
    
    for(int i=1;i<=tot;i++)
		ans[a[i].cnt+a[i].sum-1]+=a[i].cnt;//原题目中的d从0开始,而cnt至少为1
    for(int i=0;i<n;i++) printf("%d\n",ans[i]);
    return 0;
}
