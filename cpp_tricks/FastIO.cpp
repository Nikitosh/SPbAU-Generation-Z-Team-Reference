const int BUF_SIZE = 4096;

char buf[BUF_SIZE];
int bufLen = 0, pos = 0;

inline int getChar() {
  if (pos == bufLen) {
    pos = 0, bufLen = (int) fread(buf, 1, BUF_SIZE, stdin);
    if (!bufLen) return -1;
  }
  return buf[pos++];;
}

inline int readChar() {
  int c = getChar();
  while (c != -1 && c <= 32) c = getChar();
  return c;
}

template <class T>
inline T readInt() {
  int s = 1, c = readChar();
  T x = 0;
  if (c == '-') {
    s = -1, c = getChar();
  }
  while ('0' <= c && c <= '9') {
    x = x * 10 + c - '0', c = getChar();
  }
  return s == 1 ? x : -x;
}

inline void readWord(char *s) { 
  int c = readChar();
  while (c > 32) {
    *s++ = (char) c, c = getChar();
  }
  *s = 0;
}

int writePos = 0;
char writeBuf[BUF_SIZE];

inline void flush() {
  if (writePos) fwrite(writeBuf, 1, writePos, stdout), writePos = 0;
}

inline void writeChar(int x) {
  if (writePos == BUF_SIZE) flush();
  writeBuf[writePos++] = (char) x;
}

template <class T> 
inline void writeInt(T x, char after = '\0') {
  if (x < 0) {
    writeChar('-'), x = -x;
  }
  char s[24];
  int n = 0;
  while (x || !n) {
    s[n++] = '0' + x % 10, x /= 10;
  }
  while (n--) writeChar(s[n]);
  if (after) writeChar(after);
}

inline void writeWord(const char *s) {
  while (*s) writeChar(*s++);
}
