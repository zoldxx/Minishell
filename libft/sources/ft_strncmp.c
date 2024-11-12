/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:43:37 by tgeorge           #+#    #+#             */
/*   Updated: 2023/05/03 16:00:22 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2 [i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int	main(void)
// {
// 	char	s1[] = "test\200";
// 	char	s2[] = "test\0";
// 	unsigned int	sizemax;

// 	sizemax = 6;
// 	printf("ft_strncmp = %d\n", ft_strncmp(s1, s2, sizemax));
// 	printf("strncmp = %d", strncmp(s1, s2, sizemax));
// }
