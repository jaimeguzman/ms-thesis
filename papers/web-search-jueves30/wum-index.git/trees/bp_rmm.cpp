/* Copyright (C) 2010, Rodrigo Cánovas, all rights reserved.
 *
 *This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "bp_rmm.h"
 #include <string.h>

int bp_rmm::users = 0;
bp_rmm::bp_rmm(){
}

bp_rmm::bp_rmm(int n, pb *B, int opt){
	bzero(&b1, sizeof(b1));
	pb *B_aux = new pb[(n+D-1)/D];
	this->n = n;
	for(int i=0; i<n;i++)
		setbit(B_aux,i,CP);
	for(int i=0; i<n;i++){
		if(!bitget1(B,i))
			setbit(B_aux,i,OP);
	}
	bp_construct(&b1, n, B_aux,opt);
	users++;
}

void myfree(void *arg) {
	if (arg!=NULL)
		free(arg);
}

extern i64 *matchtbl,*parenttbl;
bp_rmm::~bp_rmm(){
	myfree(b1.sm);
	myfree(b1.sM);
	myfree(b1.sd);
	myfree(b1.mm);
	myfree(b1.mM);
	myfree(b1.md);
	delete [] b1.da->buf;
	myfree(b1.da->lp);
	myfree(b1.da->sl);
	myfree(b1.da->ss);
	myfree(b1.da->p);
	myfree(b1.da->rl);
	myfree(b1.da->rm);
	myfree(b1.da->rs);
	myfree(b1.da);
	users--;
	if (users == 0)  {
		myfree(parenttbl);
		myfree(matchtbl);
	}
	// delete []B_aux;
}

uint bp_rmm::excess(int v){
	return 2*rank_open(&b1,v) - (v+1);
}

uint bp_rmm::close(int v){
	return find_close(&b1, v);
}

uint bp_rmm::open(int v){
	return find_open(&b1, v);
}

uint bp_rmm::enclose(int v){
	return find_enclose(&b1,v);
}

uint bp_rmm::size(){
	uint mem = b1.idx_size+(this->n)/8;
	//cout << "mem2 = " << mem << endl;
	return mem;
}

int bp_rmm::save(FILE *fp){
	return 0;
}

bp_rmm * bp_rmm::load(FILE *fp){
	return NULL;
}

