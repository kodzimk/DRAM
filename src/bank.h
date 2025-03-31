#ifndef BANK_H
#define BANK_H

#define SEGMENT_IMPLEMENTATION
#include"segment.h"
#include<stdio.h>

typedef struct {
	Memory_Array memory[8];
}Bank;

void print(Bank* bank);
void init_bank(Bank *bank);
void refresh_bank(Bank* bank, bloom_filter* filter, int index);
void refresh_bank_my_solution(Bank* bank);
char* read_data_from_bank(Bank* bank,char address_bus[12]);
void write_data_to_bank(Bank* bank,char* data,char address_bus[12], bloom_filter* filter, int bank_index);

#endif

#ifdef BANK_IMPLEMENTATION

void init_bank(Bank* bank)
{
	for (int i = 0; i < 8; i++)
	{
		init_cells(&bank->memory[i]);
	}
}

void print(Bank* bank)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j= 0; j < 8; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				printf("%c", bank->memory[i].cells[j][k].capacitor);
			}
		   printf("\n");
		}
		printf("------------\n");
	}
}

void refresh_bank(Bank* bank, bloom_filter* filter, int index)
{
	for (int i = 0; i < 8; i++)
	{
		refresh_cells(&bank->memory[i],filter,(i + 1) * index);
	}
}

void refresh_bank_my_solution(Bank* bank)
{
	for (int i = 0; i < 8; i++)
	{
		refresh_cells_my_way(&bank->memory[i]);
	}
}

// address_bus[0] = RAS
// address_bus[1] = CAS
// address_bus[2] = WE
// address_bus[3 - 5] = row address
// address_bus[6 - 8] = column address
char* read_data_from_bank(Bank* bank, char address_bus[12])
{
	char* data = malloc(sizeof(char) * 9);
	for (int i = 0; i < 8; i++)
	{
		data[i] = read_bit_from_cell(&bank->memory[i], address_bus);
	}

	return data;
}

void write_data_to_bank(Bank* bank, char* data, char address_bus[12],bloom_filter *filter,int bank_index)
{
	for (int i = 0; i < 8; i++)
	{
		write_bit_to_cell(&bank->memory[i], address_bus,data[i],filter,i * bank_index);
	}
}

#endif