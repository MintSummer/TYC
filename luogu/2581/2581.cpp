#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=55;
int n,cnt[15];
ll C[MAXN][MAXN];
/*
按照数位dp的方法从高到低按位统计。
如n = 2345时，分别统计前缀为0~1, 20~22, 230~233, 2340~2344的答案。

设最高位为第1位。
假设当前考虑到第i位，1~i-1位都和原数字n完全匹配。
从i到n的那些可以用剩下的数全排列
然后就是i+1位之后的数如何填了。

设len = n-i。
方案数 = 先从len个位置中找了cnt[0]个位置全填0的方案数 * 又从(len-cnt[0])个位置中找了cnt[1]个位置全填1的方案数...
即：方案数 = C(len,cnt[0]) * C(len-cnt[0],cnt[1]) * C(len-cnt[0]-cnt[1],cnt[2])...
*/

void init()
{
    C[0][0]=1;
    for(int i=1;i<=50;i++)
    {
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
}

ll get_ans(int len)
{
    ll ans=1;
    for(int i=0;i<=9;i++)
		ans*=C[len][cnt[i]],len-=cnt[i];
    return ans;
}

int main()
{
    init();
    char ch[MAXN];
    scanf("%s",ch+1);
    n=strlen(ch+1);
    for(int i=1;i<=n;i++) cnt[ch[i]-'0']++;
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
		for(int j=0;j<ch[i]-'0';j++)
			if(cnt[j])
			{
				cnt[j]--;
				ans+=get_ans(n-i);
				cnt[j]++;
			}
		cnt[ch[i]-'0']--;
    }
    printf("%lld",ans);
    return 0;
}
