#pragma once

#include <algorithm>
#include <new>
#include <iostream>
#include <fstream>
#include "vector.hpp"

struct TAvlNode
{
	TData key_;
	uint64_t val_;
	uint64_t h_;
	TAvlNode* l_;
	TAvlNode* r_;
	TAvlNode() : key_(), val_(), h_(1), l_(nullptr), r_(nullptr) {};
	TAvlNode(TData key, uint64_t val) : key_(key), val_(val), h_(1), l_(nullptr), r_(nullptr) {};
};

struct TAvl
{
	TAvlNode* root_;
	uint64_t Height(const TAvlNode* node) { return node != nullptr ? node->h_ : 0; }
	uint64_t Balance(const TAvlNode* node) { return Height(node->l_) - Height(node->r_); }
	void ReHeight(TAvlNode* node) {	node->h_ = std::max(Height(node->l_), Height(node->r_)) + 1; }
	TAvlNode* RotateLeft(TAvlNode*);
	TAvlNode* RotateRight(TAvlNode*);
	TAvlNode* RotateRightLeft(TAvlNode*);
	TAvlNode* RotateLeftRight(TAvlNode*);
	TAvlNode* ReBalance(TAvlNode*);
	TAvlNode* InsertPrint(TAvlNode*, TData, uint64_t, bool const&);
	TAvlNode* RemoveMin(TAvlNode*, TAvlNode*);
	TAvlNode* RemovePrint(TAvlNode*, TData,  bool const&);
	TAvlNode* Find(TAvlNode*, TData k);
	void TreeDelete(TAvlNode*);
	TAvl() : root_(nullptr) {};
	void InsPrint(TData k, uint64_t v) { root_ = InsertPrint(root_, std::move(k), v, false); }
	void DeletePrint(TData k) {	root_ = RemovePrint(root_, std::move(k), false); }
	TAvlNode* Find(TData k) { return Find(root_, std::move(k));	}
	~TAvl() { TreeDelete(root_); }
};

//Класс для работы с AVL деревом
struct TAvlFinal : public TAvl
{
	private:
		void Upper(TData&);
		void Save(std::ostream&, TAvlNode const*);
		TAvlNode* Load(std::istream&, TAvlNode const*);
		bool FileSave(TData&);
		bool FileLoad(TData&);
	public:
		void DInsert();
		void DRemove();
		void DFind(TData const&);
		void LoadSave();
};