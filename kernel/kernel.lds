
ENTRY(__start)
SECTIONS
{
	IMG_BASE = .;

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
