#pragma once
#include "Starbucks.h"
using namespace std;


class node{
public:
	node* left;
    node* right;
    Entry* data;
	node();
    node(Entry*);
};

class gaydadsStarbucks : public Starbucks{
public:
	gaydadsStarbucks();
	//~gaydadsStarbucks();
	void randomize(Entry*, int);
	node* insert(Entry* e, node* r, bool isXlevel);
	Entry* search(double x, double y, node* r, bool is_x_level);
	double distance(double,double,node*);
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	Entry* Locations;
	node* root;
	node* tree;
private:
	//node* root;
	bool is_x_level;
	double x;
	double y;
};