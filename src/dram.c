
#define CHIP_IMPLEMENTATION
#include"chip.h"

int main()
{
	Chip chip;

	init_chip(&chip);

	char address_bus[12] = { '1','1','0','0','0','0','0','0','0','0','0','0' };
	char data[8] = { '1','1','1','1','1','1','1','1' };
	write_data_to_chip(&chip, data, address_bus);

	for (size_t j= 0; j < 8; j++)
	{
			for (size_t k = 0; k < 8; k++)
			{
				printf("%c", chip.banks[0].memory[0].cells[j][k].capacitor);
			}printf("\n");
	}
	

	return 0;
}