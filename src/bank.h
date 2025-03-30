#ifndef BANK_H
#define BANK_H

#define SEGMENT_IMPLEMENTAION
#include"segment.h"

typedef struct {
	Memory_Array memory[8];
}Bank;

void init_bank(Bank *bank);
char* read_data_from_bank(Bank* bank,char address_bus[9]);
void write_data_to_bank(Bank* bank,char* data,char address_bus[9]);

#endif

#ifdef BANK_IMPLEMENTATION

void init_bank(Bank* bank)
{
	for (int i = 0; i < 8; i++)
	{
		init_cells(&bank->memory[i]);
	}
}

// address_bus[0] = RAS
// address_bus[1] = CAS
// address_bus[2] = WE
// address_bus[3 - 5] = row address
// address_bus[6 - 8] = column address
char* read_data_from_bank(Bank* bank, char address_bus[9])
{
	char data[8];
	for (int i = 0; i < 8; i++)
	{
		data[i] = read_bit_from_cell(&bank->memory[i], address_bus);
	}

	return data;
}

void write_data_to_bank(Bank* bank, char* data, char address_bus[9])
{
	for (int i = 0; i < 8; i++)
	{
		write_bit_to_cell(&bank->memory[i], address_bus,data[i]);
	}
}

#endif