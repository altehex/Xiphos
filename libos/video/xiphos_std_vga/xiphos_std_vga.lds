SECTIONS
{
	.init :
	{
		*(.init.*)
	}
	.libos :
	{
		*(.libos.xstdvga) *(.libos) *(.libos.*)
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
