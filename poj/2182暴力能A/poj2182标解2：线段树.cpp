#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <cmath>  
#define MAXN 8008  
using namespace std;  
  
struct Node{  
    int l, r, v;  
} tree[3*MAXN];//是不是有人疑问这里，你举个例子就好了；  
int res[MAXN], a[MAXN]; 
//线段树里面的v表示这个区间内未被删除的数字个数； 
  
void build(int k, int l, int r) {  
    tree[k].l = l;  
    tree[k].r = r;  
    tree[k].v = r-l+1;  
    if (l == r) return;  
    int mid = (l+r)/2;  
    build(k*2, l, mid);  
    build(k*2+1, mid+1, r);  
    return ;  
}  
  
int query(int j, int k) {  
    tree[j].v--; // 节点长度减一  
    if (tree[j].l == tree[j].r) return tree[j].l;  
    if (tree[j*2].v >= k) //如果左子树的长度大于k就搞左子树  
        return query(j*2, k);  
    else  
        return query(j*2+1, k-tree[2*j].v); //搞右子树的话就要减去左子树的长度；  
}  
  
int main() {  
    int n;  
    scanf("%d", &n);  
    for(int i = 2; i <= n; i++)  
        scanf("%d", a+i);  
    a[1] = 0;  
    build(1, 1, n);  
    for(int i = n; i > 0; i--)  
        res[i] = query(1, a[i]+1);  
    for(int i = 1; i <= n; i++)  
        printf("%d\n", res[i]);  
    return 0;  
}  
