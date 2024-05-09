namespace halfplanes {
Pnt st, v, p[N];
int n, sp, ss[N], ind[N], no[N], cnt[N], k = 0, a[N], b[N];
dbl ang[N];

Pnt Norm(int j) { return (p[a[j]] - p[b[j]]).getRot90(); }

void AddPlane( int i, int j ){
  a[k] = i, b[k] = j, ind[k] = k;
  ang[k] = Norm(k).angle();
  k++;
}

bool angLess(int i, int j) { return ang[i] < ang[j]; }

void Unique() {
  int i = 0, k2 = 0;
  while (i < k) {
    int ma = ind[i], st_ = i;
    Pnt no_ = Norm(ma);
    for (i++; i < k && fabs(ang[ind[st_]] - ang[ind[i]]) < EPS; i++) {
      if ((no_ * p[a[ma]]) < (no_ * p[a[ind[i]]])) ma = ind[i];
    }
    ind[k2++] = ma;
  }
  k = k2;
}

dbl xx, yy, tmp;

#define BUILD(a1, b1, c1, i) \
  dbl a1 = Norm(i).x; \
  dbl b1 = Norm(i).y; \
  tmp = sqrt(a1 * a1 + b1 * b1); \
  a1 /= tmp, b1 /= tmp; \
  dbl c1 = -(a1 * p[a[i]].x + b1 * p[a[i]].y);

void FindPoint(int i, int j, dbl step = 0.0) {
  BUILD(a1, b1, c1, i);
  BUILD(a2, b2, c2, j);

  xx = -(c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
  yy = (c1 * a2 - c2 * a1) / (a1 * b2 - a2 * b1);

  dbl no_ = sqrt(sqr(a1 + a2) + sqr(b1 + b2));
  xx += (a1 + a2) * step / no_;
  yy += (b1 + b2) * step / no_;
}

void TryShiftPoint(int i, int j, dbl step) {
  FindPoint(i, j, step);

  forn (g, k) {
    BUILD(a1, b1, c1, ind[g]);
    if (a1 * xx + b1 * yy + c1 < EPS) return;
  }

  puts("Possible");
  printf("%.20lf %.20lf\n", (double)xx, (double)yy);
  exit(0);
}

void PushPlaneIntoStack(int i) {
  while (sp >= 2 && ang[i] - ang[ss[sp - 2]] + EPS < M_PI){
    FindPoint(i, ss[sp - 2]);
    BUILD(a1, b1, c1, ss[sp - 1]);
    if ((a1 * xx + b1 * yy + c1) < -EPS) break;
    sp--;
  }
  ss[sp++] = i;
}

void solve() {
  cin >> n;
  forn (i, n) cin >> p[i].x >> p[i].y;
  p[n] = p[0];

  // Find set of planes
  forn (i, sp) {
    AddPlane(max(ss[i], ss[i + 1]), min(ss[i], ss[i + 1]));
  }
  forn (i, n - 1) {
    AddPlane(i + 1, i);
  }
  sort(ind, ind + k, angLess);
  
  int oldK = k;
  Unique();

  forn (i, oldK) no[i] = i;
  forn (i, k){
    int j = oldK + i, x = ind[i];
    ang[j] = ang[x] + 2 * M_PI;
    a[j] = a[x];
    b[j] = b[x];
    ind[i + k] = j, no[j] = x;
  }

  sp = 0;
  forn (i, 2 * k) {
    PushPlaneIntoStack(ind[i]);
  }
  forn (t, sp) {
    if (++cnt[no[ss[t]]] > 1) {
      TryShiftPoint(ss[t], ss[t - 1], 1e-5);
      break;
    }
  }
}
}
