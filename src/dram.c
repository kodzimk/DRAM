
#define CHIP_IMPLEMENTATION
#include"chip.h"
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    bloom_filter* filter = bloom_filter_new_default(4096);

    Chip chip;
    init_chip(&chip);
    char address_bus[12] = { '1','1','0','0','0','0','0','0','0','0','0','0' };
    char data[8] = { '1','1','1','1','1','1','1','1' };
    write_data_to_chip(&chip, data, address_bus,filter);
    address_bus[3] = '1';
    write_data_to_chip(&chip, data, address_bus, filter);
    address_bus[4] = '1';
    write_data_to_chip(&chip, data, address_bus, filter);
    address_bus[5] = '1';
    write_data_to_chip(&chip, data, address_bus, filter);

    int index = 0;
    double cpu_time_used = 0;
    clock_t start;
    clock_t end;
    while (index < 2) {
        start = clock();
        refresh_chip(&chip, filter);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Took %f seconds to refresh: \n", cpu_time_used);


        start = clock();
        refresh_chip_my_way(&chip);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Took %f seconds to refresh my way!!!: \n", cpu_time_used);

        index++;
    }

    bloom_filter_free(filter);
    return 0;
}
