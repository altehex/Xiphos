SECTIONS
{
	.init.devman :
	{
		*(.init.*)
	}
	.subsys.devman :
	{
		*(.subsys) *(.subsys.*)
	}
	.libos :
	{
		*(.libos) *(.libos.*)
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
