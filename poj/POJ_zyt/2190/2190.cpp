#include<iostream>
#include<cstdlib>
using namespace std;
int main(void)
{
	int num[10],qu,sum=0;
	char c[1];
	for(int i=0;i<9;i++)
	{
		cin>>c[0];
		if(c[0]!='?')num[i]=atoi(c);
		else
		{
			num[i]=0;
			qu=10-i;
		}
	}
	cin>>c[0];
	if(c[0]=='X')num[9]=10;
	else if(c[0]=='?')num[9]=0,qu=1;
	else num[9]=atoi(c);
	for(int i=0;i<10;i++)sum+=num[i]*(10-i);
	int k;
	for(k=1;k*11<sum||(k*11-sum)%qu!=0;k++)
		;
	if((k*11-sum)/qu>10)cout<<-1;
	else if((k*11-sum)/qu==10)qu==1?cout<<'X':cout<<-1;
	else cout<<(k*11-sum)/qu;
	return 0;
} 
