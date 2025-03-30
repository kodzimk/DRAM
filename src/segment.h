// Segment - is a array of rows and columns that contain MUlti and Demulti Plexers and cell with decoders(just array of memory)
#ifndef SEGMENT_H
#define SEGMENT_H

#define RADECODER_IMPLEMENTATION
#define DEMPLEX_IMPLEMENTATION
#define MPLEX_IMPLEMENTATION
#define CELL_IMPLEMENTATION

#include"components/RADecoder.h"
#include"components/DEMPlex.h"
#include"components/MPlex.h"
#include"components/cell.h"

typedef struct {
	char stage;
	cell_t cells[8][8];
	char sense_amplifier[8];
}Memory_Array;

char read_bit_from_cell(Memory_Array* arr, char control_lines[9]);
void write_bit_to_cell(Memory_Array* arr,char control_lines[9], char data);
void init_cells(Memory_Array* arr);

#endif

#ifdef SEGMENT_IMPLEMENTATION

// address_bus[0] = RAS
// address_bus[1] = CAS
// address_bus[2] = WE
// address_bus[3 - 5] = row address
// address_bus[6 - 8] = column address

void init_cells(Memory_Array* arr)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			init_cell(&arr->cells[i][j]);
		}
	}
}

char read_bit_from_cell(Memory_Array* arr, char address_bus[9])
{
	if (address_bus[2] == '0') {
		arr->stage = 'R';
	}
	else {
		fprintf(stderr, "To read bit we need WE equal to '1'\n");
		exit(1);
	}

	char RAS = address_bus[0];
	char CAS = address_bus[1];
	char WE = address_bus[2];
	char row_addr[3] = { address_bus[3],address_bus[4],address_bus[5] };
	char column_addr[3] = { address_bus[6],address_bus[7],address_bus[8] };

	int row_index = decode_ras_pins(row_addr);
	for (int i = 0; i < 8; i++)
	{
		arr->sense_amplifier[i] = arr->cells[row_index][i].capacitor;
	}

	arr->stage = 'N';
	return choose_bite(arr->sense_amplifier, column_addr);
}

void write_bit_to_cell(Memory_Array* arr, char address_bus[9], char data)
{
	if (address_bus[2] == '0') {
		arr->stage = 'W';
	}
	else {
		fprintf(stderr, "To write bit we need WE equal to '0'\n");
		exit(1);
	}
	char row_addr[3] = { address_bus[3],address_bus[4],address_bus[5] };
	char column_addr[3] = { address_bus[6],address_bus[7],address_bus[8] };
	char RAS = address_bus[0];
	char CAS = address_bus[1];
	char WE = address_bus[2];

	int row_index = decode_ras_pins(row_addr);
	for (int i = 0; i < 8; i++)
	{
		arr->sense_amplifier[i] = arr->cells[row_index][i].capacitor;
	}

	choose_bite_addr(data, column_addr, arr->sense_amplifier);
	for (int i = 0; i < 8; i++)
	{
		arr->cells[row_index][i].capacitor = arr->sense_amplifier[i];
		arr->sense_amplifier[i] = ' ';
	}

	arr->stage = 'N';
}

#endif