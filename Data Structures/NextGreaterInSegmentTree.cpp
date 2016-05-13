//на позиции строго большей чем pos число строго большее x
int nextGreaterX(int v, int l, int r, int pos, int x) {
	if (r <= pos + 1 || tree[v] <= x)
		return INF;
	if (v >= tSize)
		return v - tSize;
	int ans = nextGreaterX(2 * v, l, (l + r) / 2, pos, x);
	if (ans == INF)
		ans = nextGreaterX(2 * v + 1, (l + r) / 2, r, pos, x);
	return ans;
}
