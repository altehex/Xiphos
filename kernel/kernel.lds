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
	/* https://www.redhat.com/zh/blog/linkers-warnings-about-executable-stacks-and-segments */
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
