#ifndef CHIP_H
#define CHIP_H

#define BANK_IMPLEMENTATION
#include"bank.h"

typedef struct {
	Bank banks[8];
}Chip;

void init_chip(Chip* chip);
void refresh_chip(Chip* chip);
char* read_data_from_chip(Chip* bank, char address_bus[12]);
void write_data_to_chip(Chip* chip, char* data, char address_bus[12]);

#endif

#ifdef CHIP_IMPLEMENTATION

void init_chip(Chip* chip)
{
	for (int i = 0; i < 8; i++)
	{
		init_bank(&chip->banks[i]);
	}
}

void refresh_chip(Chip* chip)
{
	for (size_t i = 0; i < 8; i++)
	{
		refresh_bank(&chip->banks[i]);
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
void write_data_to_chip(Chip* chip, char* data, char address_bus[12])
{
	char bank_addr[3] = { address_bus[9],address_bus[10],address_bus[11] };
	int bank_index = decode_ras_pins(bank_addr);
	printf("%d\n", bank_index);
	write_data_to_bank(&chip->banks[bank_index],data, address_bus);
}

#endif