ENTRY(xiphos_init);
SECTIONS
{
	init = 0x100000;
	.init_thunk : { *(.init.thunk) }
	.text : 
	{
		*(.text .text.*)
		*(.plt .plt.*)
	}
	. = ALIGN (4K); 
	/* init sections are omitted after initialization */
	.init.xiphos_init : { *(.init.xiphos_init) }
	.init :
	{
		*(.init .init.*)
	}
	
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
OUTPUT_FORMAT("binary")
