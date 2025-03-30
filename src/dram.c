
#define CHIP_IMPLEMENTATION
#include"chip.h"
#include<time.h>
#include<math.h>

Chip chip;

int main(void)
{
    init_chip(&chip);

    int index = 0;
    while (index < 1) {
        clock_t start = clock();
        refresh_chip(&chip);
        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Took %f seconds to refresh \n", cpu_time_used);
        index++;
    }
}
