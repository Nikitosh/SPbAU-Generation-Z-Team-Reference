#include <bits/stdc++.h> 
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define sz(x) (int) ((x).size()) 
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define fornr(i, n) for (int i = (n) - 1; i >= 0; --i)
#define forab(i, a, b) for (int i = (a); i < (b); ++i)
#define all(c) (c).begin(), (c).end() 
 
using ll = long long;
using dbl = double;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using ld = long double;
 
const int MAXVAR = 100;
const int LOG = 15;
const int MAX_LOG = 10;
const int MAX_M = 1e3; 
const int MAX_N = (1 << MAX_LOG);
const int MAX_MASK = 15;
const int INF = 1e9;
const int INF_LOG = 30;
const double PI = acos(-1);

namespace big_int {
#include "big_int/BigInt.cpp"
}
namespace fft {
#include "big_int/FFT.cpp"
#include "big_int/FFTMod.cpp"
}

#include "cpp_tricks/Allocation.cpp"
namespace fast_io_long {
#include "cpp_tricks/FastIOLong.cpp"
}
namespace fast_io_short {
#include "cpp_tricks/FastIOShort.cpp"
}
#include "cpp_tricks/HashMap.cpp"
#include "cpp_tricks/OrderedSet.cpp"
namespace pair_hasher {
#include "cpp_tricks/PairHasher.cpp"
}

namespace centroid_decomposition {
#include "data_structures/CentroidDecomposition.cpp"
}
namespace convex_hull_trick {
#include "data_structures/ConvexHullTrick.cpp"
}
namespace disjoint_set_union {
#include "data_structures/DisjointSetUnion.cpp"
}
namespace fenwick_tree {
#include "data_structures/FenwickTree.cpp"
}
namespace fenwick_tree_2d {
#include "data_structures/FenwickTree2D.cpp"
}
namespace hash_table {
#include "data_structures/HashTable.cpp"
}
namespace heavy_light_decomposition {
#include "data_structures/HeavyLightDecomposition.cpp"
}
namespace next_greater_in_segment_tree {
#include "data_structures/NextGreaterInSegmentTree.cpp"
}
namespace segment_tree_2d {
#include "data_structures/SegmentTree2D.cpp"
}
namespace sparse_table {
#include "data_structures/SparseTable.cpp"
}

namespace longest_increasing_subsequence {
#include "dynamic_programming/LongestIncreasingSubsequence.cpp"
}
namespace masks {
#include "dynamic_programming/Masks.cpp"
}
namespace tree_knapsack {
#include "dynamic_programming/TreeKnapsack.cpp"
}  

namespace ford_fulkerson {
#include "flows/Utilities.cpp"
#include "flows/FordFulkerson.cpp"
}
namespace edmonds_karp {
#include "flows/Utilities.cpp"
#include "flows/EdmondsKarp.cpp"
}
namespace dinic {
#include "flows/Utilities.cpp"
#include "flows/Dinic.cpp"
}
namespace min_cost_max_flow {
#include "flows/MinCostMaxFlow.cpp"
}
namespace hungarian {
#include "flows/Hungarian.cpp"
}

namespace retrograde_analysis {
#include "games/RetrogradeAnalysis.cpp"
}

namespace sat {
#include "graphs/2Sat.cpp"
}
namespace bridges {
#include "graphs/Bridges.cpp"
}
namespace cut_points {
#include "graphs/CutPoints.cpp"
}
namespace euler_tour_tree {
#include "graphs/EulerTourTree.cpp"
}
namespace eulerian_cycle {
#include "graphs/EulerianCycle.cpp"
}
namespace hamilton {
#include "graphs/Hamilton.cpp"
}
namespace karp {
#include "graphs/Karp.cpp"
}
namespace kuhn {
#include "graphs/Kuhn.cpp"
}
namespace lca {
#include "graphs/Lca.cpp"
}
namespace lca_tarjan {
#include "graphs/LcaTarjan.cpp"
}

namespace math {
#include "math/PowerAndMul.cpp"
#include "math/Gcd.cpp"
#include "math/Crt.cpp"
#include "math/DiscreteLogarithm.cpp"
#include "math/Phi.cpp"
#include "math/PrimitiveRoot.cpp"
#include "math/DiscreteRoot.cpp"
#include "math/Eratosthenes.cpp"
#include "math/Factorial.cpp"
#include "math/Gauss.cpp"
#include "math/GaussBinary.cpp"
#include "math/Gray.cpp"
#include "math/MillerRabin.cpp"
#include "math/Pollard.cpp"
#include "math/Simpson.cpp"
}

namespace aho_corasick {
#include "strings/AhoCorasick.cpp"
}
namespace hashes {
#include "strings/Hashes.cpp"
}
namespace manaker {
#include "strings/Manaker.cpp"
}
namespace palindromic_tree {
#include "strings/PalindromicTree.cpp"
}
namespace prefix {
#include "strings/Prefix.cpp"
}
namespace suffix_array {
#include "strings/SuffixArray.cpp"
}
namespace suffix_automaton {
#include "strings/SuffixAutomaton.cpp"
}
namespace suffix_tree {
#include "strings/SuffixTree.cpp"
}
namespace z {
#include "strings/Z.cpp"
}

int main() {
	return 0;
}