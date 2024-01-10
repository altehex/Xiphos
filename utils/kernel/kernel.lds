ENTRY(xiphos_init);
SECTIONS
{
	kinit = 0x100000;
	.text : 
	{
		*(.init .init.*)
		*(.text .text.*)
		*(.plt .plt.*)
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
