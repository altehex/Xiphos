SECTIONS
{
	.init :
	{
		*(.init.*)
	}
	.libos :
	{
		*(.libos.xstdpcie) *(.libos) *(.libos.*)
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
