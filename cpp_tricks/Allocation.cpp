const int MAX_MEM = 1e8;

int mpos = 0;
char mem[MAX_MEM];
inline void* operator new(size_t n) {
	char *res = mem + mpos;
	mpos += n;
	assert(mpos <= MAX_MEM);
	return (void*) res;
}
inline void operator delete(void*) {}

inline void* operator new[](size_t) { assert(0); }
inline void operator delete[](void*) { assert(0); }
