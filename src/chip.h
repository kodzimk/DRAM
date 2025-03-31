#ifndef CHIP_H
#define CHIP_H

#define BANK_IMPLEMENTATION
#include"bank.h"

typedef struct {
	Bank banks[16];
}Chip;

void init_chip(Chip* chip);
void refresh_chip(Chip* chip, bloom_filter* filter);
void refresh_chip_my_way(Chip* chip);
char* read_data_from_chip(Chip* bank, char address_bus[12]);
void write_data_to_chip(Chip* chip, char* data, char address_bus[12], bloom_filter* filter);

#endif

#ifdef CHIP_IMPLEMENTATION

void init_chip(Chip* chip)
{
	for (int i = 0; i < 16; i++)
	{
		init_bank(&chip->banks[i]);
	}
}

void refresh_chip(Chip* chip, bloom_filter* filter)
{
	for (size_t i = 0; i < 16; i++)
	{
		refresh_bank(&chip->banks[i],filter,i + 1);
	}
}

void refresh_chip_my_way(Chip* chip)
{
	for (size_t i = 0; i < 16; i++)
	{
		refresh_bank_my_solution(&chip->banks[i]);
	}
}


// address_bus[0] = RAS
// address_bus[1] = CAS
// address_bus[2] = WE
// address_bus[3 - 5] = row address
// address_bus[6 - 8] = column address
// address_bus[9 - 11] = bank address

char* read_data_from_chip(Chip* chip, char address_bus[12])
{
	char bank_addr[3] = { address_bus[9],address_bus[10],address_bus[11] };
	int bank_index = decode_ras_pins(bank_addr);
	printf("%d\n", bank_index);

	return read_data_from_bank(&chip->banks[bank_index], address_bus);
}
void write_data_to_chip(Chip* chip, char* data, char address_bus[12],bloom_filter *filter)
{
	char bank_addr[3] = { address_bus[9],address_bus[10],address_bus[11] };
	int bank_index = decode_ras_pins(bank_addr);
	write_data_to_bank(&chip->banks[bank_index],data, address_bus,filter,bank_index);
}

#endif