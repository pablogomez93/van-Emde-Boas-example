#ifndef VBE

#include <stdexcept>
#include <math.h>
#include "vector"
#include "iostream"
#include "algorithm"

#define NIL -1

typedef unsigned int uint;

using namespace std;

struct vEB {
	uint u;
	int max;
	int min;
	vEB* summary;
	vector<vEB*> cluster;
};

uint upperSQRTOf(uint u);
uint lowerSQRTOf(uint u);
vEB* make_vEB(uint u);
int smallest(vEB* tree);
int biggest(vEB* tree);
bool isMember(vEB* tree, int e);
int high(int e, uint u);
int low(int e, uint u);
int index(int a, int b, uint u);
int successor(vEB* tree, int e);
int predecessor(vEB* tree, int e);
void empty_tree_insert(vEB* tree, int e);
void insert(vEB* tree, int e);
void delete_some(vEB* tree, int e);

#endif