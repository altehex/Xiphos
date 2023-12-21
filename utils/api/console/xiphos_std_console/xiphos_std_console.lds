SECTIONS
{
	.init :
	{
		*(.init.*)
	}
	.api :
	{
		*(.api.xstdcon) *(.api) *(.api.*)
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
