
ENTRY(__start)
SECTIONS
{
	. = 0xFFFFFFFFFFE00000;

	.text : 
	{
		*(.text)
	}

	.data : 
	{
		*(.data .data.*)
		*(.rodata .rodata.*)
	}

	.bss :
	{
		*(COMMON)
		*(.bss)
	}
}
