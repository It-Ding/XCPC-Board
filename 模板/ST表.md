# ST表

## 题目链接

[P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)

一种离线的线性数据结构，不支持任何形式的修改操作。

用于求解区间最值问题（RMQ），预处理复杂度 $O(n\log n)$ ,查询复杂度 $O(1)$ 。

在区间求gcd问题上，线段树更优。

## 完整代码

```c++
int a[maxn];
int f[maxn][22];

void init(int n) {
    for (int i = 1; i <= n; ++i)
        f[i][0] = a[i];
    int t = log(n) / log(2) + 1;
    for (int j = 1; j < t; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
}

int get_max(int l, int r) {
    int k = log2(r - l + 1);
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    init(n);
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << get_max(l, r) << endl;
    }
    return 0;
}

```

