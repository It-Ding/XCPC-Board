#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

using ll = long long;
using VI = vector<ll>;
using PII = pair<int, int>;

const int maxn = 1e5 + 5;
const ll mod = 1e9 + 7;

ll a[64];
bool flag;

void insert(ll x) {
    for (int i = 62; i >= 0; --i)
        if (x & (1ll << i)) {
            if (a[i])
                x ^= a[i];
            else {
                a[i] = x;
                return;
            }
        }
    flag = false;
}

ll get_max() {
    ll ret = 0;
    for (int i = 62; i >= 0; --i)
        if ((ret ^ a[i]) > ret)
            ret ^= a[i];
    return ret;
}

ll get_min() {
    if (flag)
        return 0;
    for (int i = 0; i <= 62; ++i)
        if (a[i])
            return a[i];
}

vector<ll> p; //每次异或p[i],对名次的贡献为 1<<i

//如 p[0] 为第一小，p[0]^p[1] 为第三小，p[1]为第二小

void rebuild() {
    for (int i = 62; i >= 0; --i) {
        if (a[i])
            for (int j = i - 1; j >= 0; --j)
                if (a[j] && (a[i] & (1ll << j)))
                    a[i] ^= a[j];
    }
    for (int i = 0; i <= 62; ++i)
        if (a[i])
            p.push_back(a[i]);
}

ll kth(int k) {
    if (flag)
        --k;
    if (k == 0)
        return 0;
    if (k >= (1ll << p.size()))
        return -1;
    ll ret = 0;
    for (int i = 0; i < p.size(); ++i)
        if (k & (1 << i))
            ret ^= p[i];
    return ret;
}

int main() {
    int n;
    cin >> n;
    memset(a, 0, sizeof a);
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        insert(x);
    }
    cout << get_max() << endl;
    return 0;
}
