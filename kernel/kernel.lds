OUTPUT_FORMAT("binary")
ENTRY(kinit)
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
