#include <algorithm>
#include <new>
#include <iostream>
#include <cctype>
#include <utility>
#include "vector.hpp"
#include "avl.hpp"

//Повороты
TAvlNode* TAvl::RotateLeft(TAvlNode* node)
{
	TAvlNode* new_node = node->r_;
	node->r_ = new_node->l_;
	new_node->l_ = node;
	ReHeight(node);
	ReHeight(new_node);
	return new_node;
}

TAvlNode* TAvl::RotateRight(TAvlNode* node)
{
	TAvlNode* new_node = node->l_;
	node->l_= new_node->r_;
	new_node->r_ = node;
	ReHeight(node);
	ReHeight(new_node);
	return new_node;
}

TAvlNode* TAvl::RotateRightLeft(TAvlNode* node)
{
	node->r_ = RotateRight(node->r_);
	return RotateLeft(node);
}

TAvlNode* TAvl::RotateLeftRight(TAvlNode* node)
{
	node->l_ = RotateLeft(node->l_);
	return RotateRight(node);
}

//Перебалансировка
TAvlNode* TAvl::ReBalance(TAvlNode* node)
{
	if (node == nullptr) { return nullptr; }
	ReHeight(node);
	uint64_t balance = Balance(node);
	if (balance == -2)
	{
		if (Balance(node->r_) == 1) { return RotateRightLeft(node); }
		return RotateLeft(node);
	}
	else if (balance == 2)
	{
		if (Balance(node->l_) == -1) { return RotateLeftRight(node); }
		return RotateRight(node);
	}
	return node;
}

//Вставка с печатью на экран
TAvlNode* TAvl::InsertPrint(TAvlNode* node, TData k, uint64_t v, bool const& benchmark_flag)
{
	if (node == nullptr)
	{
		try { node = new TAvlNode(k, v); }
		catch (std::exception& e)
		{
			if(!benchmark_flag) { std::cout << "ERROR: " << e.what() << "\n"; }
			return nullptr;
		}
		if(!benchmark_flag) {std::cout << "OK\n";}
		return node;
	}
	if (k < node->key_) { node->l_ = InsertPrint(node->l_, k, v, benchmark_flag); }
	else if (k > node->key_) { node->r_ = InsertPrint(node->r_, k, v, benchmark_flag); }
	else { std::cout << "Exist\n"; }
	return ReBalance(node);
}

//Удаление минимального
TAvlNode* TAvl::RemoveMin(TAvlNode* node, TAvlNode* tmp)
{
	if (tmp->l_ != nullptr) { tmp->l_ = RemoveMin(node, tmp->l_); }
	else
	{
		TAvlNode* r = tmp->r_;
		node->key_ = std::move(tmp->key_);
		node->val_ = tmp->val_;
		delete tmp;
		tmp = r;
	}
	return ReBalance(tmp);
}

//Удаление с печатью
TAvlNode* TAvl::RemovePrint(TAvlNode* node, TData k, bool const& benchmark_flag)
{
	if (node == nullptr)
	{
		if(!benchmark_flag) { std::cout << "NoSuchWord\n"; }
		return nullptr;
	}
	if (k < node->key_) {node->l_ = RemovePrint(node->l_, k, benchmark_flag); }
	else if (k > node->key_) { node->r_ = RemovePrint(node->r_, k, benchmark_flag);	}
	else
	{
		TAvlNode* l = node->l_;
		TAvlNode* r = node->r_;
		if (l == nullptr && r == nullptr)
		{
			delete node;
			if(!benchmark_flag) { std::cout << "OK\n"; }
			return nullptr;
		}
		if (r == nullptr)
		{
			delete node;
			if(!benchmark_flag) { std::cout << "OK\n"; }
			return l;
		}
		if (l == nullptr)
		{
			delete node;
			if(!benchmark_flag) { std::cout << "OK\n"; }
			return r;
		}
		node->r_ = RemoveMin(node, r);
		if(!benchmark_flag) { std::cout << "OK\n"; }
	}
	return ReBalance(node);
}

//Поиск
TAvlNode* TAvl::Find(TAvlNode* node, TData k)
{
	if (node == nullptr) { return nullptr; }
	for (TAvlNode* iter = node; iter != nullptr; )
	{
		if (k < iter->key_) { iter = iter->l_; }
		else if (k > iter->key_) { iter = iter->r_;	}
		else { return iter;	}
	}
	return nullptr;
}

void TAvl::TreeDelete(TAvlNode* node)
{
	if (node != nullptr)
	{
		TreeDelete(node->l_);
		TreeDelete(node->r_);
		delete node;
	}
}
//Приводим к верхнему регистру
void TAvlFinal::Upper(TData& str)
{
	size_t size = str.Size();
	for (size_t i = 0; i < size; ++i) { str[i] = std::toupper(str[i]);	}
}

//Сохранение
void TAvlFinal::Save(std::ostream& os, TAvlNode const* node)
{
	if (node == nullptr) { return; }
	size_t k_size = node->key_.Size();
	os.write((char*)(&k_size), sizeof(k_size));
	os.write(node->key_.Data(), k_size);
	os.write((char*)&node->val_, sizeof(node->val_));

	bool hasLeft = node->l_ != nullptr;
	bool hasRight = node->r_ != nullptr;

	os.write((char*)(&hasLeft), sizeof(hasLeft));
	os.write((char*)(&hasRight), sizeof(hasRight));
	if (hasLeft) { Save(os, node->l_); }
	if (hasRight) {	Save(os, node->r_);	}
}

//Загрузка
TAvlNode* TAvlFinal::Load(std::istream& is, TAvlNode const* node)
{
	(void)(node);
	TAvlNode* root = nullptr;
	size_t k_size;
	is.read((char*)(&k_size), sizeof(k_size));
	if (is.gcount() == 0) {	return root; }
	char* key = new char[k_size + 1];
	key[k_size] = '\0';
	is.read(key, k_size);
	uint64_t val;
	is.read((char*)(&val), sizeof(val));

	bool hasLeft = false;
	bool hasRight = false;

	is.read((char*)(&hasLeft), sizeof(hasLeft));
	is.read((char*)(&hasRight), sizeof(hasRight));

	root = new TAvlNode();
	root->key_.Move(key);
	root->val_ = val;

	if (hasLeft) { root->l_ = Load(is, root); }
	else { root->l_ = nullptr; }
	if (hasRight) {	root->r_ = Load(is, root); }
	else { root->r_ = nullptr; }

	return root;
}

//Сохранение в файл
bool TAvlFinal::FileSave(TData& fileName)
{
	std::ofstream os(fileName.Data(), std::ios::binary | std::ios::out);
	if (os) { Save(os, root_); }
	else { return false; }
	os.close();
	return true;
}

//Загрузка из файла
bool TAvlFinal::FileLoad(TData& fileName)
{
	std::ifstream is(fileName.Data(), std::ios::binary | std::ios::in);
	if (is)
	{
		TreeDelete(root_);
		root_ = Load(is, nullptr);
	}
	else { return false; }
	is.close();
	return true;
}

//Публичные методы для вставки, удаления, поиска, сохранения/загрузки
void TAvlFinal::DInsert()
{
	TData key;
	uint64_t value = 0;
	std::cin >> key >> value;
	Upper(key);
	InsPrint(std::move(key), value);
}

void TAvlFinal::DRemove()
{
	TData key;
	std::cin >> key;
	Upper(key);
	DeletePrint(std::move(key));
}

void TAvlFinal::DFind(TData const& k)
{
	TData key(k);
	Upper(key);
	TAvlNode* res = Find(std::move(key));
	if (res != nullptr) { std::cout << "OK: " << res->val_ << "\n"; }
	else { std::cout << "NoSuchWord\n";	}

}

void TAvlFinal::LoadSave()
{
	TData cmd;
	TData fileName;
	std::cin >> cmd >> fileName;
	if (cmd[0] == 'S')
	{
		if (!FileSave(fileName))
		{
			std::cout << "ERROR: can't open file\n";
			return;
		}
	}
	else
	{
		if (!FileLoad(fileName))
		{
			std::cout << "ERROR: can't open file\n";
			return;
		}
	}
	std::cout << "OK\n";
}