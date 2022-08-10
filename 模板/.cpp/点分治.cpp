#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

using ll = long long;
using VI = vector<int>;
using PII = pair<int, int>;

const int maxn = 2e5 + 5;
const ll mod = 1e9 + 7;

int n, m;
vector<PII> g[maxn];
int sum, cnt, root;
int questions[maxn], ans[maxn];
int temDis[maxn], siz[maxn], dis[maxn], son[maxn];
int judge[(int)(1e7 + 5)], vis[maxn];

//寻找重心
void get_root(int u, int fa) {
    siz[u] = 1, son[u] = 0;
    for (auto &[v, w] : g[u]) {
        if (v == fa || vis[v])
            continue;
        get_root(v, u);
        siz[u] += siz[v];
        if (siz[v] > son[u])
            son[u] = siz[v];
    }
    son[u] = max(son[u], sum - siz[u]);
    if (son[u] < son[root])
        root = u;
}

void get_dis(int u, int fa) {
    temDis[cnt++] = dis[u];
    for (auto &[v, w] : g[u]) {
        if (v == fa || vis[v])
            continue;
        dis[v] = dis[u] + w;
        get_dis(v, u);
    }
}

//判断经过重心的边是否满足条件
void evaluate(int u) {
    static queue<int> q;
    for (auto &[v, w] : g[u]) {
        if (vis[v])
            continue;
        dis[v] = w;
        cnt = 0;
        get_dis(v, u);
        for (int i = 0; i < cnt; ++i)
            for (int j = 0; j < m; ++j)
                if (questions[j] >= temDis[i] || temDis[i] > 1e7)
                    ans[j] |= judge[questions[j] - temDis[i]];
        for (int i = 0; i < cnt; ++i) {
            if (temDis[i] > 1e7)
                continue;
            q.push(temDis[i]);
            judge[temDis[i]] = true;
        }
    }
    while (!q.empty()) {
        judge[q.front()] = false;
        q.pop();
    }
}

//分治
void divide(int u) {
    vis[u] = judge[0] = true;
    evaluate(u);
    for (auto &[v, w] : g[u]) {
        if (vis[v])
            continue;
        root = 0;
        son[root] = sum = siz[v];
        get_root(v, 0);
        get_root(root, 0);
        divide(root);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    for (int i = 0; i < m; ++i)
        cin >> questions[i];
    son[0] = sum = n;
    get_root(1, 0);
    get_root(root, 0);
    divide(root);
    for (int i = 0; i < m; ++i) {
        if (ans[i])
            cout << "AYE" << endl;
        else
            cout << "NAY" << endl;
    }
}

int main() {
    solve();
    return 0;
}