//https://blog.csdn.net/u012288458/article/details/48624859
//https://blog.csdn.net/u011572615/article/details/43115721
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1010; 
typedef long long ll;
int n,m;

ll C(int x)
{
	return (ll)x*(x-1)*(x-2)/6;//ֻ����C(x,3)��ֵ 
}

inline int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}

inline ll get_ans()
{
	
}

int main()
{
	scanf("%d%d",&n,&m);
	n++,m++;//���񰡣������ڵ��� 
	ll ans=C(n*m)-m*C(n)-n*C(m);//��������ȡ������ ,��ȥ��������ͬһ���������ϵ�
	//����б�ŵ����� 
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)//ö��������֮�� 
		{
			/*
			�ٶ�����������ɵ��߶���һ��ֱ�������ε�б�ߣ���һ������Ϊ(0,0)����һ��Ϊ(i,j)
			��ô��������֮��ĵ�ĸ���(����������)��Ϊ 
			*/ 
			int tmp=gcd(i,j)-1; 
			if(tmp>=1) ans-=(ll)(n-i)*(m-j)*tmp*2;
		}
	printf("%lld",ans);
} 
