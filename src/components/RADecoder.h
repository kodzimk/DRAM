// RADecorder = Row address decoder a component of DRAM 
#ifndef DEMPLEX_H
#define DEMPLEX_H

int decode_ras_pins(char control_lines[3]);

#endif

#ifndef DEMPLEX_IMPLEMENTATION

int decode_ras_pins(char control_lines[3])
{
	if (control_lines[0] == '0' && control_lines[1] == '0' && control_lines[2] == '0') {
		return 1;
	}
	else if (control_lines[2] == '1' && control_lines[0] == '0' && control_lines[1] == '0') {
		return 0;
	}

	int row_addr = 0;

	if (control_lines[0] == '1') {
		row_addr += 4;
	}
	if (control_lines[1] == '1') {
		row_addr += 2;
	}
	if (control_lines[2] == '1')
	{
		row_addr += 1;
	}

	return row_addr;
}


#endif