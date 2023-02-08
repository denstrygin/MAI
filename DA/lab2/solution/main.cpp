#include <iostream>
#include "vector.hpp"
#include "avl.hpp"

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TData cmd;
	TAvlFinal avl;

	while (std::cin >> cmd)
	{
		if (cmd[0] == '+') { avl.DInsert();	}
		else if (cmd[0] == '-') { avl.DRemove(); }
		else if (cmd[0] == '!' && cmd.Size() == 1) { avl.LoadSave(); }
		else { avl.DFind(std::move(cmd)); }
	}

	return 0;
}