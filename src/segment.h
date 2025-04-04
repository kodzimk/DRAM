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


#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"components/bloom.h"

typedef struct {
	cell_t cells[128][128];
	char sense_amplifier[128];
}Memory_Array;

char read_bit_from_cell(Memory_Array* arr, char control_lines[12]);
void write_bit_to_cell(Memory_Array* arr,char control_lines[12], char data, bloom_filter* filter, int index);
void refresh_cells(Memory_Array* arr, bloom_filter* filter, int index);
void refresh_cells_my_way(Memory_Array* arr);
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
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			init_cell(&arr->cells[i][j]);
		}
	}
}

char read_bit_from_cell(Memory_Array* arr, char address_bus[12])
{

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

	return choose_bite(arr->sense_amplifier, column_addr);
}

void refresh_cells(Memory_Array* arr,bloom_filter *filter, int index)
{
	for (int i = 0; i < 128; ++i)
	{
		int n = (i + 1) * index;
		if (bloom_filter_test(filter, &n, 4))
		{
			for (int j = 0; j < 128; ++j) {
				arr->sense_amplifier[i] = arr->cells[i][j].capacitor;
			}
			for (size_t k = 0; k < 128; ++k)
			{
				arr->cells[i][k].capacitor = arr->sense_amplifier[k];
				arr->sense_amplifier[k] = ' ';
			}
		}
	}
}

void refresh_cells_my_way(Memory_Array* arr)
{
	for (int i = 0; i < 128; ++i)
	{
			for (int j = 0; j < 128; ++j) {
				arr->sense_amplifier[i] = arr->cells[i][j].capacitor;
			}
			for (size_t k = 0; k < 128; ++k)
			{
				arr->cells[i][k].capacitor = arr->sense_amplifier[k];
				arr->sense_amplifier[k] = ' ';
			}
	}
}

void write_bit_to_cell(Memory_Array* arr, char address_bus[12], char data,bloom_filter *filter,int index)
{
	char row_addr[3] = { address_bus[3],address_bus[4],address_bus[5] };
	char column_addr[3] = { address_bus[6],address_bus[7],address_bus[8] };
	char RAS = address_bus[0];
	char CAS = address_bus[1];
	char WE = address_bus[2];

	int row_index = decode_ras_pins(row_addr);
	int n = index * (row_index + 1);
	bloom_filter_put(filter, &n, 4);
	
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
}

#endif