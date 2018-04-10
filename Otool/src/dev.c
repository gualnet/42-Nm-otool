
#include "ft_otool.h"

void	print_offset(t_vault *vault, void *ptr)
{
	void	*start;
	if (vault->fat_dump != NULL && vault->ar_dump == NULL && vault->o_dump == NULL)
		start = (vault->fat_dump);
	else if (vault->fat_dump == NULL && vault->ar_dump != NULL && vault->o_dump == NULL)
		start = (vault->ar_dump);
	else if (vault->fat_dump == NULL && vault->ar_dump == NULL && vault->o_dump != NULL)
		start = (vault->o_dump);
	else
		start = 0;
	ft_printf("\n\033[36moffset[%x]\033[00m\n", ptr - start,ptr - start);
}