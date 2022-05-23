# Dijkstra求最短路（堆优化）

#### 最后更新于	2021/11/11

#### 题目来源：[850. Dijkstra求最短路 II - AcWing题库](https://www.acwing.com/problem/content/submission/code_detail/6314589/)

## 前置变量

```C++
const int MAX = 1e6 + 5;
typedef pair<int, int> PII;//first存到原点的距离distance，second存当前所在点
bool Point_Checked[MAX];
int Next_Edge[MAX];//这条边所连接的下一条边
int Next_Point[MAX];//这条边所指向的下一个点
int Edge_Length[MAX];//这条边的权值
int Point_Edge[MAX];//链接这个点的第一条边
int cnt = 0;
int Dis[MAX];//当前点到原点的距离
```

## 链式前向星添加边

```c++
void Add_Edge(int a, int b, int c)
{
	Edge_Length[cnt] = c;
	Next_Point[cnt] = b;
	Next_Edge[cnt] = Point_Edge[a];//这条边所指向的下条边的地址
	Point_Edge[a] = cnt++;
}
```

## Dijkstra函数

```c++
long long DJ(int n)
{
	memset(Dis, 0x3f, sizeof(Dis));
	Dis[1] = 0;
	PII Start = { 0,1 };
	priority_queue<PII, vector<PII>, greater<PII>> Heap;
	Heap.push(Start);
	while (Heap.size())
	{
		PII t = Heap.top();
		Heap.pop();
		int distance = t.first, ver = t.second;
		if (Point_Checked[ver])
			continue;
		Point_Checked[ver] = true;
		for (int i = Point_Edge[ver]; i != -1; i = Next_Edge[i])
		{
			int j = Next_Point[i];
			if (Dis[j] > distance + Edge_Length[i])
			{
				Dis[j] = distance + Edge_Length[i];
				Heap.push({ Dis[j],j });
			}
		}
	}
	if (Dis[n] == INF)
	{
		return -1;
	}
	return Dis[n];
}
```

## 完整代码

```c++
//Dijkstra求最短路   模板
//https://www.acwing.com/problem/content/852/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
///-------------------///
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#define endl "\n"
#define ls (rt<<1)
#define rs (rt<<|1)
#define mid ((l+r)<<1)
using namespace std;
//inline int gcd(int a, int b) { int r; while (b > 0) { r = a % b; a = b; b = r; }return a; }

const int MAX = 1e6 + 5;
const int INF = 0x3f3f3f3f;
bool Point_Checked[MAX];
int Next_Edge[MAX], Next_Point[MAX], Edge_Length[MAX], Point_Edge[MAX];
int cnt = 0;
int Dis[MAX];//当前点到原点的距离
void Add_Edge(int a, int b, int c)
{
	Edge_Length[cnt] = c;
	Next_Point[cnt] = b;
	Next_Edge[cnt] = Point_Edge[a];//这条边所指向的下条边的地址
	Point_Edge[a] = cnt++;
}
typedef pair<int, int> PII;//first存到原点的距离distance，second存当前所在点
long long DJ(int n)
{
	memset(Dis, 0x3f, sizeof(Dis));
	Dis[1] = 0;
	PII Start = { 0,1 };
	priority_queue<PII, vector<PII>, greater<PII>> Heap;
	Heap.push(Start);
	while (Heap.size())
	{
		PII t = Heap.top();
		Heap.pop();
		int distance = t.first, ver = t.second;
		if (Point_Checked[ver])
			continue;
		Point_Checked[ver] = true;
		for (int i = Point_Edge[ver]; i != -1; i = Next_Edge[i])
		{
			int j = Next_Point[i];
			if (Dis[j] > distance + Edge_Length[i])
			{
				Dis[j] = distance + Edge_Length[i];
				Heap.push({ Dis[j],j });
			}
		}
	}
	if (Dis[n] == INF)
	{
		return -1;
	}
	return Dis[n];
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	memset(Point_Edge, -1, sizeof(Point_Edge));
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		Add_Edge(a, b, c);
	}
	cout << DJ(n) << endl;
	return 0;
}
```

## 2021/11/11 重构

```c++
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef vector<int> VI;
const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;
vector<PII> v[maxn];
int Dis[maxn];
int n, m;
int Dj()
{
	memset(Dis, 0x3f, sizeof(Dis));
	Dis[1] = 0;
	priority_queue<PII, vector<PII>, greater<PII> >Heap;
	Heap.push({ 0,1 });
	while (!Heap.empty())
	{
		PII now = Heap.top();
		Heap.pop();
		if (now.first > Dis[now.second])
			continue;
		if (now.second == n)
			return now.first;
		for (const PII& i : v[now.second])
		{
			int nextdis = now.first + i.first;
			if (Dis[i.second] <= nextdis)
				continue;
			Dis[i.second] = nextdis;
			Heap.push({ nextdis,i.second });
		}
	}
	return -1;
}
int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		int x, y, z;
		cin >> x >> y >> z;
		v[x].push_back({ z,y });
	}
	cout << Dj() << endl;
	return 0;
}
```

