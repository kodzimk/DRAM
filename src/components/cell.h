#ifndef CELL_H
#define CELL_H

typedef struct {
	char bit;
	char capacitor;
	bool transistor;
}cell_t;

void init_cell(cell_t* cell);

#endif

#ifndef CELL_IMPLEMENTATION

void init_cell(cell_t* cell)
{
	cell->bit = '0';
	cell->capacitor = '0';
	cell->transistor = 0;
}

#endif