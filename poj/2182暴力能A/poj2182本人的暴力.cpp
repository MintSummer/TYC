#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
int s[8010],b[8010],now[8010];
//b��ʾǰ���м�ͷ��Ÿ���ǰ��ţ
//s[i]��ʾ��iͷţ�ı��
//now[i]��ʾ��ʱ���Ϊi���Ƕ����еĵ�now[i]ͷţ

//˵ʵ������������߶�������״���飬���Ҳ���
//���ұ����ܽ�� 
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	  scanf("%d",&b[i]);
	s[1]=1,now[1]=1;
	int pos;
	for(int i=2;i<=n;i++)
	  {
	  	if(b[i]==i-1) 
		  {s[i]=i;now[i]=i;continue;}
	  	pos=b[i]+1;
	  	for(int j=i-1;j>=pos;j--) 
		  s[now[j]]++,now[j+1]=now[j];
	  	now[pos]=i;
	  	s[i]=pos;
	  }
	for(int i=1;i<=n;i++)
	  printf("%d\n",s[i]);
	return 0;
}
