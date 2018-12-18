/*
问n=a+a+1+a+2+…+a+k 的情况总数
n=(k+1)*a+(k+1)*k/2=(k+1)(a+k/2)
n为整数，k+1为整数，(a+k/2)为整数，k为偶数，k+1为奇数
当n和k+1确定时，a为定值
故解为n的奇因子个数
*/

#include <cstdio>
#include <cmath>
int main()
{
    int n;
    while(~scanf("%d",&n)){
        n *= 2;
        int ans = 0;
        int k = sqrt((double)n);
        for( int i = 1; i <= k; i++ ){
            if(n%i == 0 && (n/i)%2 != i%2)ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
