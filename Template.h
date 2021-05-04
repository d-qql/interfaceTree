//
// Created by Дмитрий on 12.05.2020.
//


#ifndef INTERFACETREE_TEMPLATE_H
#define INTERFACETREE_TEMPLATE_H
#include "Container.h"
#include <iostream>
#include <string>
using namespace std;
template<typename T>
class tree;
template<typename T>
class treeElem
{
private:
    T id;
    unsigned char height;
    treeElem<T>* left;
    treeElem<T>* right;
public:
    friend class tree<T>;
    treeElem(const T& k);
    ~treeElem();
    };

template<typename T>
class tree: public Container<T>{
private:
    treeElem<T>* root;
    unsigned char height(treeElem<T>* p);
    int balancefactor(treeElem<T>* p);
    void fixheight(treeElem<T>* p);
    treeElem<T>* rotateright(treeElem<T>* p);
    treeElem<T>* rotateleft(treeElem<T>* q);
    treeElem<T>* balance(treeElem<T>* p);
    treeElem<T>* _insert(treeElem<T>* p, const T& k);
    treeElem<T>* findmin(treeElem<T>* p);
    treeElem<T>* removemin(treeElem<T>* p);
    treeElem<T>* _remove(treeElem<T>* p, const T& k);
    void _print_tree(treeElem<T>* root);
    void _Print(treeElem<T> *q, long n);
    treeElem<T>* _findElem(treeElem<T>* root, const T& id) const;
    void _DeleteAll(treeElem<T> *root);
public:
    tree();
   ~tree();
    void insert(const T& value);
    bool exists(const T& value) const;
    void remove(const T& value);

    // И этот тоже, хотя к нему потом ещё вернёмся
    void print();
    void DeleteAll();
    void PrintLikeATree();
};

#endif //INTERFACETREE_TEMPLATE_H
