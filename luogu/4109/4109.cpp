#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;

	ll T,L,R;
	int lenL,lenR,a[30],b[30];
	
	inline void get_len(ll t,int &len,int x[])
	{
		memset(x,0,sizeof(int[28]));
		for(ll tmp=t;tmp;tmp/=10) len++;
		for(ll tmp=t,i=len;i;i--,tmp/=10) x[i]=tmp%10;
	}

	inline bool check0(int s,int x[])
	{
		for(int i=s;i<=lenL;i++)
			if(x[i]!=0) return false;
		return true;
	}

	void work()
	{
		scanf("%lld",&T);
		while(T--)
		{
			scanf("%lld%lld",&L,&R);
			if(L==5) 
			{
				putchar('5');
				putchar('\n');
				continue;
			}
			lenL=0,lenR=0;
			get_len(L,lenL,a);
			get_len(R,lenR,b);
			if(lenL!=lenR)
			{
				if(lenL==lenR-1)
				{
					int flag=check0(2,a);
					if((a[1]>5||(a[1]==5&&!flag))&&b[1]<5) 
					{
						int x=a[1]+!flag;
						if(x>=10) x=1,lenL++;
						putchar('0'+x);
						for(int i=2;i<=lenL;i++) putchar('0');
					}
					else if(a[1]==5&&flag)
					{
						putchar('1');
						for(int i=2;i<=lenL;i++) putchar('0');
					}
					else
					{
						putchar('5');
						for(int i=2,lim=(a[1]>5||(a[1]==5&&!flag)?lenR:lenL);i<=lim;i++) putchar('0');
					}
				}
				else 
				{
					putchar('5');
					if(a[1]>5||(a[1]==5&&check0(2,a))) lenL++;
					for(int i=2;i<=lenL;i++) putchar('0');
				}
				putchar('\n');
				continue;
			}
			for(int i=1;i<=lenL;i++)
			{
				if(a[i]==b[i]) putchar('0'+a[i]);
				else
				{
					if(check0(i,a)) 
						for(int j=i;j<=lenL;j++) putchar('0');
					else if(b[i]>=5&&(a[i]<5||(a[i]==5&&check0(i+1,a))))
					{
						putchar('5');
						for(int j=i+1;j<=lenL;j++) putchar('0');
					}
					else
					{
						int x=a[i]+!check0(i+1,a);
						if(x>=10) x=1,lenL++;
						putchar('0'+x);
						for(int j=i+1;j<=lenL;j++) putchar('0');
					}
					break;
				}
			}
			putchar('\n');
		}
	}
}

int main()
{
	TYC::work();
	return  0;
}
