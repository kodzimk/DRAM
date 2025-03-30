#include<stdio.h>

#define SEGMENT_IMPLEMENTATION
#include"segment.h"

int main()
{
	Memory_Array arr;
	init_cells(&arr);

	char address_bus[9] = { '1','1','1' ,'1','0','1', '0','1','1' };
	char address_bus2[9] = { '1','1','1' ,'1','0','1', '0','1','0' };
	char data = '1';
	write_bit_to_cell(&arr, address_bus, data);
	printf("%c\n", read_bit_from_cell(&arr, address_bus2));

	return 0;
}