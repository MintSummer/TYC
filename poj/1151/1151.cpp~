#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=2010;
const double eps=1e-8;
int n,cnt;
double qx[MAXN];

double read()
{
    double x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    if(ch=='.')
    {
		double l=0.1;
		ch=getchar();
		while(ch>='0'&&ch<='9') x+=l*(ch-'0'),l/=10,ch=getchar();
    }
    return x;
}

struct node
{
    int l,r,tag;
    double rl,rr,sum;
}tree[MAXN*4];

struct Line
{
    double lx,rx,y;
    int val;
    bool operator < (const Line &a) const
    {
		return y<a.y;
    }
}line[MAXN*2];

void build(int root,int lt,int rt)
{
    tree[root].l=lt,tree[root].r=rt;
    tree[root].rl=qx[lt],tree[root].rr=qx[rt];
    tree[root].sum=tree[root].tag=0;
    if(lt+1==rt) return;
    int mid=(lt+rt)>>1;
    build(root*2,lt,mid);
    build(root*2+1,mid,rt);//要统计上mid到mid+1那一段的
}

void get_len(int root)
{
    if(tree[root].tag>0) tree[root].sum=tree[root].rr-tree[root].rl;
    else if(tree[root].l+1==tree[root].r) tree[root].sum=0;
    else tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

void add(int root,double s,double e,int val)
{
    double lt=tree[root].rl,rt=tree[root].rr;
    if(s==lt&&rt==e) 
    {
		tree[root].tag+=val;
		get_len(root);
		return;
    }
    if(e<=tree[root*2].rr) add(root*2,s,e,val);
    else if(s>=tree[root*2+1].rl) add(root*2+1,s,e,val);
    else add(root*2,s,tree[root*2].rr,val),add(root*2+1,tree[root*2+1].rl,e,val);
    get_len(root);
}

int main()
{
    int kase=0;
    while(scanf("%d",&n),n)
    {
		kase++;
		cnt=0;
		double x1,x2,y1,y2;
		for(int i=1;i<=n;i++)
		{
			x1=read(),y1=read(),x2=read(),y2=read();
			line[++cnt]=(Line){x1,x2,y1,1};
			qx[cnt]=x1;
			line[++cnt]=(Line){x1,x2,y2,-1};
			qx[cnt]=x2;
		}

		sort(qx+1,qx+cnt+1);
		sort(line+1,line+1+cnt);
		build(1,1,cnt);

		double ans=0;
		add(1,line[1].lx,line[1].rx,line[1].val);
		for(int i=2;i<=cnt;i++)
		{
			ans+=tree[1].sum*(line[i].y-line[i-1].y);
			add(1,line[i].lx,line[i].rx,line[i].val);
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n",kase,ans); 
    }
    return 0;
}
