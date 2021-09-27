#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void example() {
	ordered_set<int> s;
	s.insert(1), s.insert(3); 
	assert(s.order_of_key(3) == 1 && s.order_of_key(4) == 2 && *s.find_by_order(0) == 1);
}	