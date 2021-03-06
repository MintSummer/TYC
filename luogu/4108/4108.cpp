#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=100010;
	int n,m,block,tot,val[N],belong[N],start[N],end[N],gcd_sum[N],xor_sum[N];

	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct node
	{
		ll x;
		int id;
		bool operator < (const node &t) const
		{
			return (x<t.x)||(x==t.x&&id<t.id);
		}
	}a[N];

	inline int gcd(int x,int y)
	{
		int tmp;
		while(y) 
			tmp=x,x=y,y=tmp%y;
		return x;	
	}

	inline void init(int x)
	{
		int l=start[x],r=end[x];
		gcd_sum[l]=xor_sum[l]=val[l];
		a[l]=(node){val[l],l};
		for(int i=l+1;i<=r;i++)
		{
			gcd_sum[i]=gcd(gcd_sum[i-1],val[i]);
			xor_sum[i]=xor_sum[i-1]^val[i];
			a[i]=(node){xor_sum[i],i};
		}
		sort(a+l,a+r+1);
	}

	inline int find(int l,int r,ll x)
	{
		int ans=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(a[mid].x>=x) ans=mid,r=mid-1;
			else l=mid+1;
		}
		return ans;
	}
		
	void search(ll x)
	{
		ll Gcd=val[1],Xor=0;
		int ans=-1;
		for(int i=1;i<=tot;i++)
			if(gcd(Gcd,gcd_sum[end[i]])==Gcd)
			{
				if(!(x%Gcd))
				{
					ll tmp=(x/Gcd)^Xor;
					int pos=find(start[i],end[i],tmp);
					if(a[pos].x==tmp) {ans=a[pos].id;break;}
				}
				//Gcd=gcd(Gcd,gcd_sum[end[i]]);
				Xor=Xor^xor_sum[end[i]];
			}
			else 
			{
				for(int j=start[i];j<=end[i];j++)
				{
					Gcd=gcd(Gcd,val[j]);
					Xor=Xor^val[j];
					if(Gcd*Xor==x) {ans=j;break;}
				}
				if(~ans) break;
			}
		if(ans==-1) printf("no\n");
		else printf("%d\n",ans-1);
	}

	void work()	
	{
		n=read();
		block=sqrt(n);
		tot=(n/block)+(n%block!=0);
		for(int i=1;i<=n;i++) 
			val[i]=read(),belong[i]=(i-1)/block+1;
		for(int i=1;i<=tot;i++)
			start[i]=end[i-1]+1,end[i]=end[i-1]+block;
		end[tot]=n;
		for(int i=1;i<=tot;i++) init(i);
		m=read();
		char ch[10];
		while(m--)
		{
			scanf("%s",ch);
			if(ch[0]=='M') 
			{
				int id=read()+1,x=read();
				val[id]=x;
				init(belong[id]);
			}	
			else search(read());
		}
	}
}

int main()
{
    TYC::work();
    return 0;
}
