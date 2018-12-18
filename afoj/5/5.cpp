#include<bits/stdc++.h>
using namespace std;
int t;
string A,B;
int a[1010],b[1010],c[1010];

int main()
{
	freopen("first.in","r",stdin);
	freopen("first.out","w",stdout);
	cin>>t;
	while(t--)
	{
		cin>>A>>B;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		int la=A.size(),lb=B.size();
		int len=max(la,lb),flag=0;
		for(int i=0;i<la;i++) a[i]=A[la-1-i]-'0';
		for(int i=0;i<lb;i++) b[i]=B[lb-1-i]-'0';
		if(la<lb) flag=1;
		if(la==lb) 
			for(int i=len-1;i>=0;i--) 
			{
				if(a[i]>b[i]) break;
				if(a[i]<b[i]) flag=1;
			}
		if(flag==1) 
		{
			printf("-");
			for(int i=len-1;i>=0;i--) swap(a[i],b[i]);
		}
		for(int i=0;i<len;i++)
		{
			if(a[i]-b[i]<0) a[i]+=10,a[i+1]--;
			c[i]=a[i]-b[i];
		}
		if(c[len-1]) printf("%d",c[len-1]);
		for(int i=len-2;i>=0;i--) printf("%d",c[i]);
		printf("\n");
	}
	return 0;
}
