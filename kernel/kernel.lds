
ENTRY(__start)
SECTIONS
{
	. = 0x00100000;
	IMG_BASE = . ;

	.text : 
	{
		*(.text)
	}

	.data : 
	{
		*(.data)
	}

	.bss :
	{
		*(COMMON)
		*(.bss)
	}
}
