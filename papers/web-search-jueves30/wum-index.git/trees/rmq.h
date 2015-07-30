#ifndef _RMQ__H
#define _RMQ__H

#include <iostream>
#include <fstream>

#include <tree_ff.h>

namespace rmq_space {
	class Tree 	{
	public:
		int pos;
		Tree *prevSibl,*lastChild;
	};

	class Path {
	public:
		Tree *node;
		Path *next;
	};

	class RMQ {
	public:
		size_t n;
		unsigned int *bitmap;
		tree_ff *t;

		RMQ(int *A,size_t n);
		RMQ(size_t n);
		~RMQ();
		
		void  mapTree (unsigned int *bitmap, Tree *T, int i);
		unsigned int *buildrmq (int *A, size_t n);
		unsigned int query(size_t i,size_t j);
		size_t getSize();
		
		void save(ofstream &f);
		static RMQ * load(ifstream &fp);
	};
};
#endif
