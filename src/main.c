#include"Components/MPlex.h"
#include"Components/DEMPlex.h"
#include<stdio.h>

int main()
{
	char bites[8] = { '0','1','0','1','0','1','0','1' };
	char lines[3] = { '1','0','1' };
	choose_bite_addr('0', lines, bites);
	printf("%c\n", choose_bite(bites, lines));
	return 0;
}