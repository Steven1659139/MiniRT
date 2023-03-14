#include "../../include/miniRT.h"

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}
void	parse(int argc, char **argv, t_dlist *l)
{
	if (argc != 2)
		error_exit("Bad number of arguments");
	valid_file(argv[1]);
	split(argv[1], l);
	print_objects(l);
}

void	valid_file(char *file)
{
	int		fd =  open(file, O_RDONLY);
	char	c;

	if (fd == -1)
		error_exit("File do not exist");
	if (read(fd, &c, 1) == -1)
		error_exit("File is a directory");
	if (!ft_gnl(fd))
		error_exit("File is empty");
	file = ft_strrchr(file, '.');
	if (ft_strncmp(file, ".rt", 4))
		error_exit("Doit être un fichier '.rt'");
	close(fd);
}

void	split(char *file, t_dlist *l)
{
	int	fd = open(file, O_RDONLY);
	char *str = ft_gnl(fd);
	char **args;

	while (str)
	{
		args = ft_split(str, ' ');
		valid_element(args, l);
		str = ft_gnl(fd);
	}
	close(fd);
}

void	valid_element(char **elem, t_dlist *l)
{
	if (ft_strcmp(elem[0], "A"))
		dlist_add_back(l, object_A(elem));
	else if (ft_strcmp(elem[0], "C"))
		dlist_add_back(l, object_C(elem));
	else if (ft_strcmp(elem[0], "L"))
		dlist_add_back(l, object_L(elem));
	else if (ft_strcmp(elem[0], "sp"))
		dlist_add_back(l, object_sp(elem));
	else if (ft_strcmp(elem[0], "pl"))
		dlist_add_back(l, object_pl(elem));
	else if (ft_strcmp(elem[0], "cy"))
		dlist_add_back(l, object_cy(elem));
	else
		error_exit("Invalid element");
}




//A, C, L, sp, pl, cy