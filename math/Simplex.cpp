
/**
 	* maximize $c^T x$ subject to $Ax \le b$, $x \ge 0$.	
 	* -inf / inf / max c^T x
	* define variables such that $x = 0$ is viable.
	* vvd A = {{1,-1}, {-1,1}, {-1,-2}};
	* vd b = {1,1,-4}, c = {-1,-1}, x;
	* T val = LPSolver(A, b, c).solve(x);
 * Time: O(NM \cdot \#pivots), where a pivot may be e.g. an edge relaxation. O(2^N) in the general case.
*/
 
using vi = vector<int>;
using dbl = double;
using vd = vector<dbl>;
using vvd = vector<vd>;
const dbl eps = 1e-8, inf = 1/.0;

#define ltj(X) if (s==-1 || mp(X[j],N[j])<mp(X[s],N[s])) s=j
struct LPSolver {
	int m, n; vi N, B; vvd D; // # contraints, # variables
	LPSolver(const vvd& A, const vd& b, const vd& c) :
	  m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
		forn(i,m) forn(j,n) D[i][j] = A[i][j]; 
		forn(i,m) { // B[i]: add basic variable for each constraint, 
			B[i] = n+i, D[i][n] = -1, D[i][n+1] = b[i]; 
			// convert ineqs to eqs
		} // D[i][n]: artificial variable for testing feasibility
		forn(j,n) { 
			N[j] = j; // non-basic variables, all zero
			D[m][j] = -c[j]; // minimize -c^T x
		} 
		N[n] = -1; D[m+1][n] = 1; 
	}
	void pivot(int r, int s) { // r = row, c = column
		dbl *a = D[r].data(), inv = 1/a[s]; 
		forn(i,m+2) if (i != r && abs(D[i][s]) > eps) {
			dbl *b = D[i].data(), binv = b[s]*inv;
			forn(j,n+2) b[j] -= a[j]*binv; 
			// make column corresponding to s all 0s
			b[s] = a[s]*binv; // swap N[s] with B[r]
		}
		// equation for r scaled so x_r coefficient equals 1
		forn(j,n+2) if (j != s) D[r][j] *= inv; 
		forn(i,m+2) if (i != r) D[i][s] *= -inv; 
		D[r][s] = inv; swap(B[r], N[s]); // swap basic w/ non-basic
	}
	bool simplex(int phase) {
		int x = m+phase-1;
		while (1) {
			int s = -1; forn(j,n+1) if (N[j] != -phase) ltj(D[x]); 
			// find most negative col for nonbasic (nb) variable
			if (D[x][s] >= -eps) return 1; 
			// can't get better sol by increasing nb variable
			int r = -1;
			forn(i,m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || mp(D[i][n+1] / D[i][s], B[i])
							 < mp(D[r][n+1] / D[r][s], B[r])) r = i; 
				// find smallest positive ratio
			} // -> max increase in nonbasic variable
			if (r == -1) return 0; // unbounded
			pivot(r,s);
		}
	}
	dbl solve(vd& x) {
		int r = 0; forab(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) { // run simplex, find feasible x!=0
			pivot(r, n); // N[n] = -1 is artificial variable
			// initially set to smth large
			if (!simplex(2) || D[m+1][n+1] < -eps) return -inf; 
			// D[m+1][n+1] is max possible value of the negation of 
			// artificial variable, optimal value should be zero 
			// if exists feasible solution
			forn(i,m) if (B[i] == -1) { // ?
				int s = 0; forab(j,1,n+1) ltj(D[i]);
				pivot(i,s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		forn(i,m) if (B[i] < n) x[B[i]] = D[i][n+1]; 
		return ok ? D[m][n+1] : inf;
	}
};
