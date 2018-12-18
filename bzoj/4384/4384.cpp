#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=1000010;
	const int inf=0x3f3f3f3f;

	struct Point
	{
		int pos,a,b,c;
		bool operator < (const Point &t) const
		{
			return a<t.a;
		}
	}node[N];

	struct Node
	{
		pa mx,smx,mn,smn;

		Node()
		{
			mx=pa(-inf,-inf),smx=pa(-inf,-inf);
			mn=pa(inf,-inf),smn=pa(inf,-inf);
		}

		Node(const pa &t):mx(t),mn(t) 
		{
			smx=pa(-inf,-inf),smn=pa(inf,-inf);
		}
		
		Node operator + (const Node &t)
		{
			Node ans;
			if(mx.first<t.mx.first) 
			{
				ans.mx=t.mx;
				if(mx.first<t.smx.first) ans.smx=t.smx;
				else
				{	
					if(mx.second!=ans.mx.second) ans.smx=mx;
					else if(smx.first>t.smx.first) ans.smx=smx;
					else ans.smx=t.smx;
				}
			}
			else
			{
				ans.mx=mx;
				if(smx.first>t.mx.first) ans.smx=smx;
				else
				{	
					if(t.mx.second!=ans.mx.second) ans.smx=t.mx;
					else if(smx.first>t.smx.first) ans.smx=smx;
					else ans.smx=t.smx;
				}
			}
			if(mn.first<t.mn.first)
			{
				ans.mn=mn;
				if(smn.first<t.mn.first) ans.smn=smn;
				else
				{	
					if(t.mn.second!=ans.mn.second) ans.smn=t.mn;
					else if(smn.first<t.smn.first) ans.smn=smn;
					else ans.smn=t.smn;
				}
			}
			else
			{
				ans.mn=t.mn;
				if(mn.first>t.smn.first) ans.smn=t.smn;
				else
				{	
					if(mn.second!=ans.mn.second) ans.smn=mn;
					else if(smn.first<t.smn.first) ans.smn=smn;
					else ans.smn=t.smn;
				}
			}
			return ans;
		}
	};

	struct BitTree
	{
		Node c[N];

		#define lowbit(x) (x)&(-(x))

		void insert(const int &x,const Node &t,const int &n) 
		{
			for(int i=x;i<=n;i+=lowbit(i)) c[i]=c[i]+t;
		}

		Node query(const int &x)
		{
			Node ans;
			for(int i=x;i;i-=lowbit(i)) ans=ans+c[i];
			return ans;
		}
	}Ltree,Rtree;

	void work()
	{	
		static int n,ans,arr[N],tmp[N];
		scanf("%d",&n);
		char ch;
		arr[0]=-1;
		int n0=0,n1=0,n2=0;
		for(int i=1,l=1,r=0;i<=n;i++)
		{
			do ch=getchar(); while(!isalpha(ch));
			switch(ch)
			{
				case 'B': arr[i]=0,n0++;break;
				case 'C': arr[i]=1,n1++;break;
				case 'S': arr[i]=2,n2++;break;
			}
			if(i==1||arr[i]==arr[i-1]) r++;
			else l=r=i;
			ans=max(ans,r-l+1);
			if(n0!=n1&&n1!=n2&&n0!=n2) ans=max(ans,i);
			node[i]=(Point){i,n0-n1,n0-n2,n1-n2};
			tmp[i]=n0-n2;
		}	
		node[++n]=(Point){0,0,0};
		sort(node+1,node+1+n);
		sort(tmp+1,tmp+1+n);
		int tot=unique(tmp+1,tmp+1+n)-tmp-1;
		for(int i=1;i<=n;i++)
			node[i].b=lower_bound(tmp+1,tmp+1+tot,node[i].b)-tmp;
		for(int i=1,j=1;i<=n;i=j+1)
		{
			while(j<n&&node[i].a==node[j+1].a) j++;
			for(int k=i;k<=j;k++)
			{
				Node L=Ltree.query(node[k].b-1);
				Node R=Rtree.query(tot-node[k].b);
				int p=node[k].pos,c=node[k].c;
				if(L.mn.second!=c) ans=max(ans,p-L.mn.first);
				else ans=max(ans,p-L.smn.first);
				if(L.mx.second!=c) ans=max(ans,L.mx.first-p);
				else ans=max(ans,L.smx.first-p);
				if(R.mx.second!=c) ans=max(ans,R.mx.first-p);
				else ans=max(ans,R.smx.first-p);
				if(R.mn.second!=c) ans=max(ans,p-R.mn.first);
				else ans=max(ans,p-R.smn.first);
			}
			for(int k=i;k<=j;k++)
			{
				Ltree.insert(node[k].b,pa(node[k].pos,node[k].c),tot);
				Rtree.insert(tot-node[k].b+1,pa(node[k].pos,node[k].c),tot);
			}
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
