/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 21:09:07 by mburson           #+#    #+#             */
/*   Updated: 2017/01/04 21:09:09 by mburson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libft.h>
#include <ft_ls.h>
#include <dirent.h>
#include <stdint.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <stdlib.h>
#include <stdbool.h>

int				print_short(t_list *dir_lst)
{
	struct s_entry	*entry;

	while (dir_lst)
	{
		entry = dir_lst->content;
		if (entry->name[0] == '.' && !(g_flags & FLAG_ALL))
		{
			dir_lst = dir_lst->next;
			continue ;
		}
		if (g_flags & FLAG_ONEPERLN)
			ft_printf("%s\n", entry->name);
		else
			ft_printf("%-16s", entry->name);
		dir_lst = dir_lst->next;
	}
	if ((g_flags & FLAG_ONEPERLN) == false)
		ft_putchar('\n');
	return (0);
}

int				print_directory(t_list *dir_lst)
{
	if (g_flags & FLAG_LONG)
	{
		if (print_long(dir_lst))
			return (-1);
	}
	else
	{
		if (print_short(dir_lst))
			return (-1);
	}
	return (0);
}
