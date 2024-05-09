const int MEM = 100 << 20;
static char buf[MEM];
inline void* operator new(size_t n) {
  static size_t i = sizeof buf;
  assert(n < i);
  return (void*) &buf[i -= n];
}
inline void operator delete(void*) {}
inline void* operator new[](size_t) { assert(0); }
inline void operator delete[](void*) { assert(0); }
