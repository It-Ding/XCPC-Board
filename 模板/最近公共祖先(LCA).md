# 最近公共祖先(LCA)

## DFS部分

```c++
void dfs(int now, int fa)
{
	depth[now] = depth[fa] + 1;
	father[now][0] = fa;
	for (int i = 1; (1 << i) <= depth[now]; ++i)
		father[now][i] = father[father[now][i - 1]][i - 1];
	for (int next : g[now])
		if (next != fa)
			dfs(next, now);
}
```

## 查询LCA部分

```c++
int lca(int x, int y)
{
	if (depth[x] < depth[y])
		swap(x, y);
	for (int i = 22; i >= 0; --i)
	{
		if (depth[father[x][i]] >= depth[y])
			x = father[x][i];
	}
	if (x == y)
		return x;
	for (int i = 22; i >= 0; --i)
	{
		if (father[x][i] != father[y][i])
		{
			x = father[x][i];
			y = father[y][i];
		}
	}
	return father[x][0];
}
```

