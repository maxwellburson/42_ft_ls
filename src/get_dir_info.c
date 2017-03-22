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
#include <stdio.h>
#include <libft.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <errno.h>

static char				*directory_append(char *dir_path, char *name)
{
	size_t	l;
	char	*path;
	char	*ptr;

	l = ft_strlen(dir_path) + ft_strlen(name) + 1;
	if (!(path = (char*)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	path[l] = '\0';
	ptr = ft_strplace(path, dir_path);
	ptr[1] = '/';
	ft_strplace(ptr + 2, name);
	return (path);
}

static int				get_passwd(struct s_entry *entry)
{
	struct passwd		*passwd;

	errno = 0;
	if (NULL == (passwd = getpwuid(entry->status->st_uid)))
	{
		if (errno)
			perror("error on getpwid() in get_passwd");
		else
			ft_printf("getwid() in get_passwd: uid not found\n");
		return (-1);
	}
	if (NULL == (entry->passwd = ft_memdup(passwd, sizeof(struct passwd))))
	{
		perror("malloc error in get_passwd");
		return (-1);
	}
	return (0);
}

static int				get_group(struct s_entry *entry)
{
	struct group		*group;

	errno = 0;
	if (NULL == (group = getgrgid(entry->status->st_gid)))
	{
		if (errno)
			perror("error on getgrgid() in get_group");
		else
			ft_printf("getgrgid() in get_group: uid not found\n");
		return (-1);
	}
	if (NULL == (entry->group = ft_memdup(group, sizeof(struct group))))
	{
		perror("malloc error in get_group");
		return (-1);
	}
	return (0);
}

static struct s_entry	*build_entry(struct dirent *entry_raw, char *dir_path)
{
	struct s_entry	*entry;

	if (NULL == (entry = (struct s_entry*)malloc(sizeof(struct s_entry))))
	{
		perror("malloc error in build_entry");
		return (NULL);
	}
	ft_bzero(entry, sizeof(struct s_entry));
	if ((NULL == (entry->dirent = ft_memdup(entry_raw, sizeof(struct dirent))))
		|| (!(entry->path = directory_append(dir_path, entry_raw->d_name)))
		|| (NULL == (entry->status = malloc(sizeof(struct stat))))
		|| (-1 == stat(entry->path, entry->status)))
	{
		perror("error in build_entry()");
		free_entry(entry);
		return (NULL);
	}
	if (get_passwd(entry)
		|| get_group(entry))
	{
		free_entry(entry);
		return (NULL);
	}
	return (entry);
}

t_list					*get_dir_info(char *path)
{
	DIR				*dirp;
	struct dirent	*dir_cur;
	t_list			*dir_lst;
	struct s_entry	*entry;

	dir_lst = NULL;
	if ((dirp = opendir(path)) == NULL)
	{
		ft_printf("ls: cannot access '%s': %s\n", path, strerror(errno));
		return (NULL);
	}
	errno = 0;
	while ((dir_cur = readdir(dirp)))
	{
		if (errno || (NULL == (entry = build_entry(dir_cur, path))))
		{
			perror("error in recurse_me");
			lstdel(&dir_lst, &free);
			return (NULL);
		}
		lstadd(&dir_lst, lstnew(entry));
	}
	closedir(dirp);
	return (dir_lst);
}
