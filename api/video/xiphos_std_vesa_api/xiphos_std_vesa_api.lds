SECTIONS
{
	.init :
	{
		*(.init.*)
	}
	. = ALIGN(4K);

	.data : 
	{
		*(.data .data.*)
	}

	.rodata :
	{
		*(.rodata .rodata.*)
	}

	.bss :
	{
		*(COMMON)
		*(.bss)
	}
}
