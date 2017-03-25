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
#include <ft_ls.h>
#include <string.h>
#include <libft.h>
#include <dirent.h>
#include <stdbool.h>
#include <errno.h>

int		g_flags;

/*
** TODO: listxattr() get extented attributes, what do i need them for?
** TODO: look into whatever S and T are in the permissions
** TODO: when username or groupname do
** TODO: handle file inputs
** TODO: handle st_rdev device shit
** TODO: only stat() in first directory
** NOTE: test on /dev/
*/
/*
static int		ls_args(t_list *valid_paths)
{
	int		retv;

	retv = 0;
	while (valid_paths)
	{
		ft_printf("%s:\n", (char*)valid_paths->content);
		if (ls_dir((char*)valid_paths->content))
			retv = 1;
		valid_paths = valid_paths->next;
		if (valid_paths)
			ft_putchar('\n');
	}
	return (retv);
}
*/
/*
static void		nothing(void *nothing)
{
	(void)(nothing);
}
*/
static _Bool	compare_names(void *entry1, void *entry2)
{
	if (ft_strcmp(((struct s_entry*)entry1)->name,
			((struct s_entry*)entry2)->name) > 0)
		return (true);
	return (false);
}

int				main(int argc, char **argv)
{
	int		flg_arg_cnt;
	t_list	*files;
	t_list	*dirs;
	int		ret;

	files = NULL;
	dirs = NULL;
	ret = 0;
	g_flags = 0;
	if (parse_flags(argc, argv, &flg_arg_cnt))
		return (0);
	if (g_flags & FLAG_NOSORT)
		g_flags = g_flags | FLAG_ALL;
	ret = open_paths(argc - flg_arg_cnt, argv + flg_arg_cnt, &files, &dirs);
	if (files)
		ft_printf("files!\n");
	if (dirs)
	{
		ft_printf("dirs!\n");
		ft_printf("first dir name: %s\n", ((struct s_entry*)dirs->content)->name);
	}
	lstsort(&files, &compare_names);
	//lstsort(&dirs, &compare_names);
	//if (flg_arg_cnt == argc)
	//	ret = ls_path(".") || ret;
	//else if (flg_arg_cnt + 1 == argc && (files || dirs))
	//	ret = ls_path(argv[flg_arg_cnt]) || ret;
	//else
		//ret = print_directory(files);
		ret = recurse_directories(dirs, true) || ret;
	lstdel(&files, &free_entry_mask);
	lstdel(&dirs, &free_entry_mask);
	return (ret);
}
