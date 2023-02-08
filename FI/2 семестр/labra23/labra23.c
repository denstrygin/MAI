#include <stdio.h>
#include <string.h>

#include "bin_tree.h"
#include "vector.h"

#define INVALID 20
#define USAGE 21
#define PRINT 22
#define ADD 23
#define DEL 24
#define FUNC 25
#define QUIT 26

#define INV_CMD 10
#define INV_ARG 11
#define NO_ARG 12
#define ONE_ARG 13

void print_usage() {
	printf("USAGE:\n"
		"\t+---------------------+-------------------------------------------------+\n"
		"\t|     Команда         |  Описание                                       |\n"
		"\t|---------------------+-------------------------------------------------|\n"
		"\t|  help               |  показать инструкцию                            |\n"
		"\t|  print              |  напечатать список                              |\n"
		"\t|  add [word]         |  добавить элемент word                          |\n"
		"\t|  del [word]         |  удалить элемент word                           |\n"
		"\t|  func               |  вывод номера уровня с макс. количеством вершин |\n"
		"\t|  quit               |  выйти из программы                             |\n"
		"\t+---------------------+-------------------------------------------------+\n"
		"\t|  Использовать следующие слова: cat, dog, bag, ok,                     |\n"
		"\t|                                           slapp, ant, aunt, fuwn, hush|\n"
		"\t+-----------------------------------------------------------------------+\n"
		"\n");
	return;
}

words string_to_words(char* s, char* names[]) {
	words res = NONE;
	do {
		res++;
		if (!strcmp(s, names[res]))
			return res;
	} while (res != HUSH);
	return NONE;
}

void print_bin_tree(treeptr root, char* names[]) {
	if (root == NULL) {
		printf("Tree is empty\n");
	}
	else {
		print_tree(root, names);
	}
}

void add_to_tree(treeptr* root, words val) {
	if (val == NONE) {
		printf("error: invalid arguments\n");
	}
	else {
		tree_add(root, val);
	}
}

void remove_node_by_val(treeptr* root, words val) {
	if (val == NONE) {
		printf("error: invalid arguments\n");
	}
	else {
		treeptr* to_remove = find_node(root, val);
		if (root != NULL && *to_remove != NULL)
			remove_node(to_remove);
	}
}

bool fill_width_vector(treeptr t, int level, vector* v) {
	if (t == NULL) {
		return true;
	}

	if (v_get_size(v) == level) {
		if (!v_set_size(v, v_get_size(v) + 1)) {
			return false;
		}
	}

	v_set(v, level, v_get(v, level) + 1);

	return fill_width_vector(t->l, level + 1, v) && fill_width_vector(t->r, level + 1, v);
}

int find_max_width_level(treeptr root) {
	//возвращает номер уровня (начиная с 1), с макс числом вершин
	//если таких несколько, береться первый  
	vector v;
	v_init(&v);
	if (!fill_width_vector(root, 0, &v)) {
		printf("Memmory allocation error\n");
		return -1;
	}

	double max = -1;
	size_t i_max = 0;
	for (size_t i = 0; i < v_get_size(&v); ++i) {
		if (v_get(&v, i) > max) {
			max = v_get(&v, i);
			i_max = i;
		}
	}
	return i_max + 1;
}


int is_sep(int a) {
	return (a == ' ' || a == '\t');
}

int is_num(int a) {
	return ('0' <= a && a <= '9');
}

int clear_line(int c) {
	while (c != '\n' && c != EOF) {
		c = getchar();
	}

	return c == EOF;
}

int read_cmd(char* cmd, char* arg, int* is_eof) {
	int result = 0;
	int cmd_idx = 0;
	int arg_idx = 0;
	int state = 0;
	bool exit = false;
	int c;

	do {
		c = getchar();
		switch (state) {
		case 0: //начало команды, скипаем лишние пробелы
			if (is_num(c)) {
				exit = true;
				result = INV_CMD;
			}
			else if (!is_sep(c)) {
				state = 1;
				cmd[cmd_idx] = c;
				cmd_idx++;
			}
			break;

		case 1: //читаем саму команду
			if (is_num(c) || cmd_idx > 7) {
				exit = true;
				result = INV_CMD;
			}
			else if (is_sep(c)) {
				state = 2;
			}
			else if (c == '\n' || c == EOF) {
				result = NO_ARG;
			}
			else {
				cmd[cmd_idx] = c;
				cmd_idx++;
			}
			break;

		case 2: //перед arg
			if (is_num(c) || arg_idx > 7) {
				exit = true;
				result = INV_ARG;
			}
			else if (c == '\n' || c == EOF) {
				result = NO_ARG;
			}
			else if (!is_sep(c)) {
				state = 3;
				arg[arg_idx] = c;
				arg_idx++;
			}
			break;

		case 3: //читаем arg
			if (c == '\n' || c == EOF || is_sep(c)) {
				result = ONE_ARG;
			}
			else if (!is_num(c)) {
				arg[arg_idx] = c;
				arg_idx++;
			}
			else {
				exit = true;
				result = INV_ARG;
			}
			break;
		}
	} while (c != '\n' && c != EOF && !exit);

	*is_eof = clear_line(c);
	cmd[cmd_idx] = '\0';
	arg[arg_idx] = '\0';
	return result;
}

int cmd_parse(char* cmd) {
	if (!strcmp(cmd, "help"))
		return USAGE;
	if (!strcmp(cmd, "print"))
		return PRINT;
	if (!strcmp(cmd, "add"))
		return ADD;
	if (!strcmp(cmd, "del"))
		return DEL;
	if (!strcmp(cmd, "func"))
		return FUNC;
	if (!strcmp(cmd, "quit"))
		return QUIT;
	return INVALID;
}

void interactive_loop(treeptr* root, char* names[]) {
	int is_eof = 0;
	do {
		char cmd[8];
		char arg[8];
		int cmd_res = read_cmd(cmd, arg, &is_eof);
		int cmd_id = cmd_parse(cmd);

		// printf("---cmd: %s\n", cmd);
		// printf("---cmd_res: %d\n", cmd_res);
		// printf("---arg: %s\n", arg);
		// printf("---is_eof: %d\n", is_eof);
		// printf("---cmd_parse: %d\n", cmd_id);

		if (cmd_res == INV_CMD) { //проверяем синтаксическую корректность введенной команды
			printf("error: invalid command\n");
		}
		else if (cmd_res == INV_ARG) {
			printf("error: invalid arguments\n");
		}
		else if (cmd_res != 0) {//затем "смысловую" корректность, 0 сохраняется для пустых строк и тд тп
			switch (cmd_id) {
			case INVALID:
				printf("error: invalid command\n");
				break;
			case USAGE:
				if (cmd_res == NO_ARG)
					print_usage();
				else
					printf("error: no arguments expected\n");
				break;
			case PRINT:
				if (cmd_res == NO_ARG)
					print_bin_tree(*root, names);
				else
					printf("error: no arguments expected\n");
				break;
			case ADD:
				if (cmd_res == ONE_ARG)
					add_to_tree(root, string_to_words(arg, names));
				else
					printf("error: 1 argument expected\n");
				break;
			case DEL:
				if (cmd_res == ONE_ARG)
					remove_node_by_val(root, string_to_words(arg, names));
				else
					printf("error: 1 argument expected\n");
				break;
			case FUNC:
				if (cmd_res == NO_ARG)
					printf("Level: %d\n", find_max_width_level(*root));
				else
					printf("error: no argument expected\n");
				break;
			case QUIT:
				if (cmd_res == NO_ARG)
					is_eof = 1;
				else
					printf("error: no arguments expected\n");
				break;
			}
		}
		//printf("\n");
	} while (!is_eof);

	return;
}

int main(int argc, char const* argv[]) {
	char* names[] = {
		"cat",
		"dog",
		"bag",
		"ok",
		"slapp",
		"ant",
		"aunt",
		"fuwn",
		"hush",
	};
	print_usage();
	treeptr root = NULL;
	interactive_loop(&root, names);
	delete_tree(&root);
	return 0;
}
