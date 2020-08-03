#pragma once
#include "matrix.h"

class myMenu
{
public:
	myMenu() : fst_mtx(0) { }
	void executeMenu();

private:
	Matrix fst_mtx;
	void showMenu();
	void readMatrix();
	void getIndices() const;
	void sumMatrices();
	void multMatrices();
	void printOutMtx();
	void setIndices();

};





