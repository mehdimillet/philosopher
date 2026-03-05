/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 00:50:29 by memillet          #+#    #+#             */
/*   Updated: 2026/03/05 17:06:55 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
    {
        t_data  *args; 
        args = malloc(sizeof(t_data));
        if (!args)
            return (1);
        parsing(args, ac, av);
        
    }
    else
        printf("Invalide number of arguments\n");
    return (0);
}