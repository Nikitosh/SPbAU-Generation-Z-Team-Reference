using H = ll;
const int HT_SIZE = 1<<20, HT_AND = HT_SIZE - 1, HT_SIZE_ADD = HT_SIZE / 100;
H ht[HT_SIZE + HT_SIZE_ADD];
int data[HT_SIZE + HT_SIZE_ADD];

int get(const H &hash){
  int k = ((ll) hash) & HT_AND;
  while (ht[k] && ht[k] != hash) ++k;
  return k;
}

void insert(const H &hash, int x){
  int k = get(hash);
  if (!ht[k]) ht[k] = hash, data[k] = x;
}

bool count(const H &hash){
  int k = get(hash);
  return ht[k] != 0;
}
