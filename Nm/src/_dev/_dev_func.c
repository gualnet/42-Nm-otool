#include "ft_nm.h"

void print_symtab_command(void *sym_cmd)
{
	ft_printf("\nPRINT_SIMTAB_COMMAND\n");
	struct symtab_command *sym;

	sym = (struct symtab_command*)sym_cmd;

	ft_printf("adress : [%p]\n", sym);
	ft_printf("cmd : [%x]\n", sym->cmd);
	ft_printf("cmdsize : [%d]\n", sym->cmdsize);
	ft_printf("symoff : [%d]\n", sym->symoff);
	ft_printf("nsyms : [%d]\n", sym->nsyms);
	ft_printf("stroff : [%d]\n", sym->stroff);
	ft_printf("strsize : [%d]\n", sym->strsize);
	ft_printf("----- ----- ----- -----\n\n", sym->strsize);
}

void	print_lc_lst(t_vault *vault)
{
	ft_printf("\nPRINT_LC_LST\n");
	
	uint i = 0;
	struct mach_header_64	*header;
	header = vault->header;
	void		*save;
	
	save = (void*)vault->lc_lst;	
	while (i < header->ncmds)
	{
		ft_printf("[%d]vault->lc_lst->cmd [%x]\n", i, vault->lc_lst->lc->cmd);
		ft_printf("vault->lc_lst->cmdsize [%x]\n", vault->lc_lst->lc->cmdsize);
		i++;
		if(vault->lc_lst->next == NULL)
			break;
		vault->lc_lst = vault->lc_lst->next;
	}
	vault->lc_lst = save;	
}