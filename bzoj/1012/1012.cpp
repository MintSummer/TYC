//from:TYC的单调队列
#include<cstdio>
int m,d,a[200001],t,max[200001],l=0,p;
char q[1];
int main()
{
	scanf("%d%d", &m, &d);
	while (m--)
	{
		scanf("%s%d",q,&p);
		if(q[0]=='A')
		{
			a[++t]=(l+p)%d;
			for(int i=t;i;i--)
				if(max[i]<a[t])max[i]=a[t];
				else break;
		}
		else printf("%d\n",l=max[t-p+1]);
	}
	return 0;
}
