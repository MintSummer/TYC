#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<algorithm>
#include<stack>
#define lowbit(i) (i&(-i))
#define LL long long
using namespace std;
int c[8001];
int ans[8001];
int n;
inline void add(int i, int val)
{
    while(i<=n){
        c[i] += val;
        i += lowbit(i);
    }
}
int sum(int i)
{
    int ans = 0;
    while(i>0){
        ans += c[i];
        i -= lowbit(i);
    }
    return ans;
}
int Bin_search(int L, int R, int key)
{
    int mid;
    while(L < R){
        mid = L + ((R-L)>>1);
        if(sum(mid)-1 < key) L = mid+1;
        else R = mid;
    }
    return R;
}
int main(void)
{
    scanf("%d", &n);
    memset(c, 0, sizeof(c));
    stack<int> st;
    st.push(0);
    for(int i=1; i<=n-1; i++){
        int temp;
        scanf("%d", &temp);
        st.push(temp);
        add(i, 1);
    }
    add(n, 1);
    int top = 0;
    while(!st.empty()){
        int temp = st.top();
        st.pop();
        int num = Bin_search(1, n, temp);
        ans[top++] = num;
        add(num, -1);
    }
    for(int i=top-1; i>=0; i--){
        printf("%d\n", ans[i]);
    }
    return 0;
}
