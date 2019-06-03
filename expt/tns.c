#include <stdio.h>
#include <stdlib.h>

#include <tox/tox.h>

int main(void)
{
	size_t i;
	uint8_t addr[TOX_ADDRESS_SIZE];
	char* nns="AABBCCDD";
	uint32_t ns;
	Tox* t;
	struct Tox_Options to;

	tox_options_default(&to);
	t=tox_new(&to, NULL);

	ns=tox_self_get_nospam(t);
	tox_self_get_address(t, addr);

	printf("current addr: ");
	for(i=0; i<TOX_ADDRESS_SIZE; i++)
		printf("%02X", addr[i]);
	putchar('\n');
	printf("current ns: %08X\n", ns);

	ns=strtoul(nns, NULL, 16);

	tox_self_set_nospam(t, ns);

	ns=tox_self_get_nospam(t);
	tox_self_get_address(t, addr);

	printf("current addr: ");
	for(i=0; i<TOX_ADDRESS_SIZE; i++)
		printf("%02X", addr[i]);
	putchar('\n');
	printf("current ns: %08X\n", ns);

	return 0;
}
