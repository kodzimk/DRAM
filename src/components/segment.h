// Segment - is a array of rows and columns that contain MUlti and Demulti Plexers and cell with decoders(just array of memory)
#ifndef SEGMENT_H
#define SEGMENT_H

#include"RADecoder.h"
#include"DEMPlex.h"
#include"MPlex.h"
#include"cell.h"

typedef struct {
	cell_t cells[8][8];
	char sense_amplifier[8];
}Memory_Array;

char read_bit_from_cell(Memory_Array* arr, char control_lines[9]);
void write_bit_to_cell(Memory_Array* arr,char control_lines[9], char data);
void init_cells(Memory_Array* arr);

#endif

// address_bus[0] = RAS
// address_bus[1] = CAS
// address_bus[2] = WE
// address_bus[3 - 5] = row address
// address_bus[6 - 8] = column address

void init_cells(Memory_Array* arr)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			init_cell(&arr->cells[i][j]);
		}
	}
}

char read_bit_from_cell(Memory_Array* arr,char address_bus[9])
{
	char row_addr[3] = { address_bus[3],address_bus[4],address_bus[5] };
	char column_addr[3] = { address_bus[6],address_bus[7],address_bus[8] };
	char RAS = address_bus[0];
	char CAS = address_bus[1];
	char WE = address_bus[2];

	int row_index = decode_ras_pins(row_addr);
	for (size_t i = 0; i < 8; i++)
	{
		arr->sense_amplifier[i] = arr->cells[row_index][i].capacitor;
		arr->sense_amplifier[i] = ' ';
	}

	return choose_bite(arr->sense_amplifier, column_addr);
}

void write_bit_to_cell(Memory_Array* arr,char address_bus[9],char data)
{
	char row_addr[3] = { address_bus[3],address_bus[4],address_bus[5] };
	char column_addr[3] = { address_bus[6],address_bus[7],address_bus[8] };
	char RAS = address_bus[0];
	char CAS = address_bus[1];
	char WE = address_bus[2];

	int row_index = decode_ras_pins(row_addr);
	for (size_t i = 0; i < 8; i++)
	{
		arr->sense_amplifier[i] = arr->cells[row_index][i].capacitor;
	}

	choose_bite_addr(data, column_addr, arr->sense_amplifier);
	for (size_t i = 0; i < 8; i++)
	{
		arr->cells[row_index][i].capacitor = arr->sense_amplifier[i];
		arr->sense_amplifier[i] = ' ';
	}
}


#ifndef SEGMENT_IMPLEMENTATION



#endif