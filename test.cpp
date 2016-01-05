#include "vEB.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <assert.h>

int main() {
	unsigned int u = pow(2, 10);
	unsigned int elements_count = pow(2, 8);

	random_device rd;
  	default_random_engine gen(rd());
  	uniform_int_distribution<int> d(0, u-1);
  	vector<int> values;

	vEB* veb = make_vEB(u);

	for (unsigned int i = elements_count; i > 0; --i) {
		auto x = d(gen);

		insert(veb, x);
		values.push_back(x);
	}

	cout << "[TEST INSERT]: Finish without errors." << endl;

	sort(values.begin(), values.end());
	values.erase(unique(values.begin(), values.end()), values.end());
	int min = values.front();
	int max = values.back();

	assert(biggest(veb)  == max);
	cout << "[TEST MAXIMUM]: Ok!" << endl;

	assert(smallest(veb) == min);
	cout << "[TEST MINIMUM]: Ok!" << endl;

	for (unsigned int i = 0; i < values.size() - 1; ++i)
		assert(successor(veb, values[i]) == values[i+1]);
	cout << "[TEST SUCESSOR]: Ok!" << endl;

	for (unsigned int i = 1; i < values.size(); ++i)
		assert(predecessor(veb, values[i]) == values[i-1]);
	cout << "[TEST SUCESSOR]: Ok!" << endl;

	for (int i = 0; i <= u-1; ++i) {
		assert(isMember(veb, i) == (find(values.begin(), values.end(), i) != values.end()));
	}
	cout << "[TEST MEMBER]: Ok!" << endl;

	vector<int> values_deleted;
	random_device rd_delete;
	default_random_engine gen_delete(rd_delete());
	uniform_int_distribution<int> d_delete(0, u-1);
	for (unsigned int i = 10; i > 0; --i) {
		auto x = d_delete(gen_delete);
	
		if(isMember(veb, x)) {
			delete_some(veb, x);
			values_deleted.push_back(x);
		}
	}

	for (int i = 0; i < values.size(); ++i)
		assert((find(values_deleted.begin(), values_deleted.end(), values[i]) == values_deleted.end()) == isMember(veb, values[i]));
	cout << "[TEST DELETE_SOME]: Ok!" << endl;

	return 0;
}