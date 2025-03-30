// MPlEX = Multiplexers a logical component of DRAM for 8 row and 8 column
#ifndef MPLEX_H
#define MPLEX_H


char choose_bite(char bites[8],char control_lines[3]);

#endif

#ifdef MPLEX_IMPLEMENTATION

char choose_bite(char bites[8], char control_lines[3])
{
	if (control_lines[0] == '0' && control_lines[1] == '0' && control_lines[2] == '0') {
		return bites[0];
	}
	else if (control_lines[2] == '1' && control_lines[0] == '0' && control_lines[1] == '0') {
		return bites[1];
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

	return bites[byte_count];
}

#endif