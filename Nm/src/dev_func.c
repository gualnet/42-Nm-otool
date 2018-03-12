#include "ft_nm.h"

void print_symtab_command(void *sym_cmd)
{
	ft_printf("\nPRINT_SIMTAB_COMMAND\n");
	struct symtab_command *sym;

	sym = (struct symtab_command*)sym_cmd;

	ft_printf("cmd : [%x]\n", sym->cmd);
	ft_printf("cmdsize : [%d]\n", sym->cmdsize);
	ft_printf("symoff : [%d]\n", sym->symoff);
	ft_printf("nsyms : [%d]\n", sym->nsyms);
	ft_printf("stroff : [%d]\n", sym->stroff);
	ft_printf("strsize : [%d]\n", sym->strsize);
	ft_printf("----- ----- ----- -----\n\n", sym->strsize);
}