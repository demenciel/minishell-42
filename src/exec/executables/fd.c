/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:51:47 by acouture          #+#    #+#             */
/*   Updated: 2023/08/09 13:52:32 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Opens a file to read
 * @param fd1 The file to be open
 * @return The value of fd. Returns STDOUT if no file. Returns
	-1 if error opening file
*/
int	open_rd_fd(char *fd1)
{
	int	fd;

	fd = 0;
	if (!fd1)
		return (0);
	fd = open(fd1, O_RDONLY);
	if (fd < 0)
	{
		fd_error(fd1);
		return (-1);
	}
	return (fd);
}

/**
 * @brief Create a file to read
 * @param fd1 The file to be open
 * @return The value of fd. Returns STDOUT if no file. Returns
	-1 if error opening file
*/
int	create_rd_fd(char *fd1)
{
	int	fd;

	fd = 0;
	if (!fd1)
		return (0);
	fd = open(fd1, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (fd < 0)
	{
		fd_error(fd1);
		return (-1);
	}
	return (fd);
}

/**
 * @brief Create a file to read and append content
 * @param fd1 The file to be open
 * @return The value of fd. Returns STDOUT if no file. Returns
	-1 if error opening file
*/
int	append_rd_fd(char *fd1)
{
	int	fd;

	fd = 0;
	if (!fd1)
		return (0);
	fd = open(fd1, O_RDWR | O_CREAT | O_APPEND, 00644);
	if (fd < 0)
	{
		fd_error(fd1);
		return (-1);
	}
	return (fd);
}