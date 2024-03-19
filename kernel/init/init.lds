ENTRY(xiphos_init_thunk);
SECTIONS
{
	.init.thunk : { *(.init.thunk) }
	.init.xiphos_init : { *(.init.xiphos_init) }
	.init :
	{
		*( .init.*)
	}
	/* https://www.redhat.com/zh/blog/linkers-warnings-about-executable-stacks-and-segments */
	. = ALIGN (4K); 

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
