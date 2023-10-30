ENTRY(kinit);
SECTIONS
{
	kinit = 0x100000;
	.text : 
	{
		*(.init .init.*)
		*(.text .text.*)
		*(.libos .libos.*)
		*(.plt .plt.*)
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
OUTPUT_FORMAT("binary")
