ENTRY(kinit);
SECTIONS
{
	.init :
	{
		*(.init.kinit .init.*)
		*(.api .api.*)
		*(.libos .libos.*)
		*(.plt .plt.*)
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
