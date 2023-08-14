/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:10:33 by acouture          #+#    #+#             */
/*   Updated: 2023/08/11 15:25:16 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoin_f(char *s1, const char *s2)
{
	char			*join_str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if ((!s1 && s2) || s1 == NULL)
		return ((char *)s2);
	join_str = malloc(((ft_strlen(s1) + 1) + ft_strlen(s2)) * sizeof(char));
	if (!join_str)
		return (NULL);
	while (s1[i])
	{
		join_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join_str[i] = s2[j];
		i++;
		j++;
	}
	join_str[i] = '\0';
	free(s1);
	return (join_str);
}

char	*f_copy(char *temp, t_meta *ms)
{
	int		start;
	char	*prov;
	char	*txt;
	int		i;

	i = 0;
	txt = NULL;
	while (temp[i])
	{
		start = i;
		while (temp[i] && temp[i] != 36)
			i++;
		if (txt != NULL)
		{
			prov = ft_substr(temp, start, (i - start));
			txt = ft_strjoin_f(txt, prov);
			prov = f_freenull(prov);
		}
		else
			txt = ft_substr(temp, start, (i - start));
		if (temp[i] && temp[i] == 36)
			txt = f_copy_doll(&i, temp, txt, ms);
	}
	return (txt);
}
