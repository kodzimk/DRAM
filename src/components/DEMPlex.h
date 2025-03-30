// DEMPlEX = Demultiplexers a logical component of DRAM 
#ifndef DEMPLEX_H
#define DEMPLEX_H

void choose_bite_addr(char bit, char control_lines[3], char* bites);

#endif

#ifdef DEMPLEX_IMPLEMENTATION

void choose_bite_addr(char bit, char control_lines[3],char* bites)
{
	if (control_lines[0] == '0' && control_lines[1] == '0' && control_lines[2] == '0') {
		bites[0] = bit;
	}
	else if (control_lines[2] == '1' && control_lines[0] == '0' && control_lines[1] == '0') {
		bites[1] = bit;
	}

	int byte_count = 0;

	if (control_lines[0] == '1') {
		byte_count += 4;
	}
	if (control_lines[1] == '1') {
		byte_count += 2;
	}
	if (control_lines[2] == '1')
	{
		byte_count += 1;
	}

	bites[byte_count] = bit;
}

#endif