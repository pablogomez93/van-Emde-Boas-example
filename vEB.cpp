#include "vEB.h"

vEB* make_vEB(uint u) {
	vEB* tree = new vEB{u, NIL, NIL, nullptr, vector<vEB*>(upperSQRTOf(u), nullptr)};

	if(u > 2) {
		for(int i = tree->cluster.size()-1; i >= 0; i--)
			tree->cluster[i] = make_vEB(lowerSQRTOf(u));
	
		tree->summary = make_vEB(upperSQRTOf(u));
	}

	return tree;
}

uint upperSQRTOf(uint u) {
	return pow(2.0,ceil((log2(u)/2)));
}

uint lowerSQRTOf(uint u) {
	return pow(2.0,floor((log2(u)/2)));
}

int smallest(vEB* tree) {return tree->min;}

int biggest(vEB* tree) {return tree->max;}

bool isMember(vEB* tree, int e) {
	if(smallest(tree) == e || biggest(tree) == e)
		return true;
	
	if(tree->u <= 2)
		return false;
	
	return isMember(tree->cluster[high(e, tree->u)], low(e, tree->u));
}

int high(int e, uint u) {
	//Position of e in a cluster of an vEB with universe u
	return floor( e / lowerSQRTOf(u) );
}

int low(int e, uint u) {
	//Offset of e inside the vEB of its position in a cluster of an vEB with universe u
	return e % lowerSQRTOf(u);
}

int index(int a, int b, uint u) {
	return a * lowerSQRTOf(u) + b;
}

int successor(vEB* tree, int e) {
	int l = low(e, tree->u);
	int h = high(e, tree->u);
	int min = smallest(tree);
	int max = biggest(tree);

	if(tree->u <= 2)
		return e == 0 && max == 1 ? 1 : NIL;

	if(min != NIL && e < min)
		return min;	

	auto max_low = biggest((tree->cluster)[h]);
	if(max_low != NIL && l < max_low)
		return index(h, successor(tree->cluster[h], l), tree->u);

	auto succ_cluster = successor(tree->summary, h);
	if(succ_cluster != NIL)
		return index(succ_cluster, smallest((tree->cluster)[succ_cluster]), tree->u);
	
	return NIL;
}

int predecessor(vEB* tree, int e) {
	int l = low(e, tree->u);
	int h = high(e, tree->u);
	int min = smallest(tree);
	int max = biggest(tree);

	if(tree->u <= 2)
		return e == 1 && min == 0 ? 0 : NIL;
	
	if(max != NIL && max < e) 
		return max;

	auto min_low = smallest(tree->cluster[h]);
	if(min_low != NIL && min_low < l)
		return index(h, predecessor(tree->cluster[h], l), tree->u);

	auto pred_cluster = predecessor(tree->summary, h);
	if(pred_cluster != NIL)
		return index(pred_cluster, biggest(tree->cluster[pred_cluster]), tree->u);

	if(min != NIL && min < e)
		return min;

	return NIL;
}


void insert(vEB* tree, int e) {
	if(e >= tree->u) throw runtime_error("It is not posible insert an element greater or equal than the universe size u.");
	if((tree->min != NIL && e == tree->min) || (tree->max != NIL && e == tree->max)) return;

	int l = low(e, tree->u);
	int h = high(e, tree->u);

	if(tree->min == NIL) {
		tree->min = e;
		tree->max = e;

	} else {

		if(e < (tree->min)) {
			int temp = e;
			e = tree->min;
			tree->min = temp;

			l = low(e, tree->u);
			h = high(e, tree->u);
		}

		if((tree->u) > 2) {
			if(smallest((tree->cluster)[h]) == NIL) {
				insert(tree->summary, h);

				((tree->cluster)[h])->min = l;
				((tree->cluster)[h])->max = l;
			} else {
				insert((tree->cluster)[h], l);
			}
		}

		if(e > (tree->max))
			tree->max = e;

	}

	return;
}

void delete_some(vEB* tree, int e) {
	if(e >= tree->u) throw runtime_error("It can not exists elements greater of equal than the universe size u.");
	
	int l = low(e, tree->u);
	int h = high(e, tree->u);

	if(tree->min == tree->max) {
		tree->min = NIL;
		tree->max = NIL;

	} else if(tree->u <= 2) {
		tree->min = e == 0 ? 1 : 0;
		tree->max = tree->min;

	} else {
	
		if(e == tree->min) {
			auto first_cluster = smallest(tree->summary);
			e = index(first_cluster, smallest(tree->cluster[first_cluster]), tree->u);
			tree->min = e;
		}

		delete_some(tree->cluster[h], l);

		if(smallest(tree->cluster[h]) == NIL) {
			delete_some(tree->summary, h);

			if(tree->max == e) {
				auto summary_max = biggest(tree->summary);

				if(summary_max == NIL)
					tree->max = tree->min;
				else
					tree->max = index(summary_max, biggest(tree->cluster[summary_max]), tree->u);
				
			}
		
		} else if(tree->max == e) {
		
			tree->max = index(h, biggest(tree->cluster[h]), tree->u);
		
		}

	}

	return;
}