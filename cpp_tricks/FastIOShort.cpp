inline int readChar();
inline int readInt();
template <class T> inline void writeInt(T x);

inline int readChar() {
	int c = getchar();
	while (c <= 32)
		c = getchar();
	return c;
}

inline int readInt() {
	int s = 0, c = readChar(), x = 0;
	if (c == '-')
		s = 1, c = readChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = readChar();
	return s ? -x : x;
}

template <class T> inline void writeInt(T x) {
	if (x < 0)
		putchar('-'), x = -x;
	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n--)
		putchar(s[n]);
}
