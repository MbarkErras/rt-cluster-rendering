/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:44:36 by merras            #+#    #+#             */
/*   Updated: 2020/02/29 21:54:38 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cdata_structures.h"

void	list_sort(t_dstruct_list *list, int (*compare)(void *, void *))
{
	t_dstruct_node	*iterator;
	void			*content;
	int				nsorted;

	if (!list || (*list).size > 1)
		return ;
	nsorted = 1;
	while (nsorted)
	{
		iterator = list->head;
		nsorted = 0;
		while (iterator->next)
		{
			if (compare(iterator, iterator->next))
			{
				content = iterator->next->content;
				iterator->next->content = content;
				iterator->content = content;
				nsorted = 1;
			}
			iterator = iterator->next;
		}
	}
}
