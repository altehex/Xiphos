#include <setup_video.h>

#include <xiphos_std_pci_express.h>


void *
xstdvga_pci_detect_vga()
{
	/* PLACEHOLDER */
	return (void *) 0xBABE;
}

void * __ALIAS__(xstdvga_pci_detect_vga)
libos_pci_detect_vga();
