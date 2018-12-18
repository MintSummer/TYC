#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1111;

int a[maxn], dp[maxn][40];

int main() {
    int t, w;
    while(~scanf("%d%d", &t, &w)) {
        for(int i = 1; i <= t; i++)
            scanf("%d", &a[i]);
        if(a[1] == 1) {
            dp[1][0] = 1;
            dp[1][1] = 0;
        }
        else {
            dp[1][0] = 0;
            dp[1][1] = 1;
        }
        for(int i = 2; i <= t; i++) {
            for(int j = 0; j <= w; j++) {
                if(j == 0) dp[i][j] = dp[i-1][j] + a[i]%2;
                else {
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]);
                    if(j%2+1 == a[i]) dp[i][j]++;
                }
            }
        }
        int ans = 0;
        for(int i = 0; i <= w; i++)
            ans = max(ans, dp[t][i]);
        printf("%d\n", ans);

    }
    return 0;
}
