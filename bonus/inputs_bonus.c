/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:18:40 by jvacaris          #+#    #+#             */
/*   Updated: 2021/09/21 20:18:42 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
static int	countandcheckbs(char *str)
{
	int		n;
	int		a;

	a = 0;
	n = 0;
	while (str[a])
	{
		while (str[a] == ' ' || str[a] == '\n')
			a++;
		if (str[a] == '-' || str[a] == '+')
			a++;
		if (ft_isdigit(str[a]))
		{
			while (ft_isdigit(str[a]))
				a++;
			n++;
			if ((str[a] != ' ' && str[a] != '\n') && str[a])
				exit (0);
		}
		else if (str[a])
			exit (0);
		while ((str[a] == ' ' || str[a] == '\n') && str[a])
			a++;
	}
	return (n);
}

t_par	putthingsinmaptwo(t_par par, char *full_line, int y, int *p)
{
	int	x;

	x = 0;
	while (x < par.somx)
	{
		if (full_line[*p] == '\n')
			(*p)++;
		while (full_line[*p] == ' ')
			(*p)++;
		par.map[x][y] = ft_atoi(&full_line[(*p)++]);
		if (par.map[x][y] > par.highest)
			par.highest = par.map[x][y];
		if (par.map[x][y] < par.lowest)
			par.lowest = par.map[x][y];
		while (ft_isdigit(full_line[*p]))
			(*p)++;
		x++;
	}
	return (par);
}

t_par	putthingsinmap(t_par par, char	*full_line)
{
	int	y;
	int	p;

	y = 0;
	p = 0;
	par.highest = -2147483648;
	par.lowest = 2147483647;
	while (y < par.somy)
	{
		par = putthingsinmaptwo(par, full_line, y, &p);
		y++;
	}
	return (par);
}
*/
static t_par	doingsomecallocs(t_par par)
{
	int	fd;

	par.map = ft_calloc(sizeof(int *), par.somx);
	par.mapx = ft_calloc(sizeof(int *), par.somx);
	par.mapy = ft_calloc(sizeof(int *), par.somx);
	fd = 0;
	while (fd < par.somx)
	{
		par.map[fd] = ft_calloc(sizeof(int), par.somy);
		par.mapx[fd] = ft_calloc(sizeof(int), par.somy);
		par.mapy[fd] = ft_calloc(sizeof(int), par.somy);
		fd++;
	}
	return (par);
}

t_par	doingsplits(t_par par, char *full_line)
{
	char	**first_split;
	char	**second_split;
	int		x;
	int		y;

	y = 0;
	x = 0;
	first_split = ft_split(full_line, '\n');
	par.somx = 0;
	while (first_split[y] != NULL)
	{
		second_split = ft_split(first_split[y], ' ');
		while (second_split[x] != NULL)
			x++;
		if (x > par.somx)
			par.somx = x;
		y++;
	}
	par.somy = y;
	par = doingsomecallocs(par);
	x = 0;
	y = 0;
	while (y < par.somy)
	{
		x = 0;
		second_split = ft_split(first_split[y], ' ');
		while (second_split[x] != NULL)
		{
			if (!ft_isdigit(second_split[x][0]))
				par.map[x][y] = 0;
			else
				par.map[x][y] = ft_atoi(second_split[x]);
			x++;
		}
		while (x < par.somx)
			par.map[x++][y] = 0;
		y++;
	}
	return (par);
}

t_par	createstruct(char **argv)
{
	int		fd;
	char	*linetoadd;
	char	*full_line;
	t_par	par;

	fd = open(argv[1], 0);
	full_line = ft_calloc(1, 1);
	par.somy = 0;
	while (get_next_line(fd, &linetoadd) > 0)
	{
		full_line = ft_strjoin(full_line, "\n");
		full_line = ft_strjoin(full_line, linetoadd);
		par.somy++;
	}
	if (linetoadd[1] == ' ')
		par.somy++;
	full_line = ft_strjoin(full_line, "\n");
	full_line = ft_strjoin(full_line, linetoadd);
	full_line = ft_strjoin(full_line, "\n\0");
	par = doingsplits(par, full_line);
	par.soa = TX / (sqrt(2.0) * 1.1 * ((par.somx / 2) + (par.somy / 2)));
	par.angle = 6.0;
	par.pcx = 0;
	par.pcy = 0;
	return (par);
}
