#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void example() {
	ordered_set X;
	X.insert(1);                 
	cout << *X.find_by_order(1) << " " << X.order_of_key(1) << "\n"; 
}	