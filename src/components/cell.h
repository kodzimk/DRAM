#ifndef CELL_H
#define CELL_H

#include<stdbool.h>

typedef struct {
	char capacitor;
	bool transistor;
}cell_t;

void init_cell(cell_t* cell);

#endif

#ifdef CELL_IMPLEMENTATION

void init_cell(cell_t* cell)
{
	cell->capacitor = '0';
	cell->transistor = 0;
}

#endif