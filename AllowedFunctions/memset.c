/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:27:38 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 11:10:39 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*new;

	new = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*(new + i) = (unsigned char) c;
		i++;
	}
	return (s);
}

// int	main(void)
// {
// 	unsigned char	s[20];
// 	int				c;
// 	unsigned int	n;
// 	unsigned int	i;

// 	i = 0;
// 	c = 65;
// 	n = 10;
// 	ft_memset(s, c, n);
// 	while (i < n)
// 	{
// 		write(1, &s[i], 1);
// 		i++;
// 	}
// }
// int main(void)
// {
// 	int arr[] = {1, 2, 3, 4};          
// 	size_t n = 8;                       
// 	ft_memset(arr, 1, n);             
// 	unsigned char *bytes = (unsigned char *)arr;
// 	for (size_t i = 0; i < sizeof(arr); i++)
// 		printf("%02x ", bytes[i]);
// }