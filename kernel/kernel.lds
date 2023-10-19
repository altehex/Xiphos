OUTPUT_FORMAT("binary")
ENTRY(__start)
SECTIONS
{
	. = 0x100000;
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
