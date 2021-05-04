#include "Template.h"


template<typename T>
    treeElem<T>::treeElem(const T& k): id(k), height(1), left(NULL), right(NULL){}

template<typename T>
    treeElem<T>::~treeElem(){};


template<typename T>
    unsigned char tree<T>::height(treeElem<T>* p)
    {
        return p?p->height:0;
    }
template<typename T>
    int tree<T>::balancefactor(treeElem<T>* p)
    {
        return height(p->right)-height(p->left);
    }
template<typename T>
    void tree<T>::fixheight(treeElem<T>* p)
    {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl>hr?hl:hr)+1;
    }
template<typename T>
    treeElem<T>* tree<T>::rotateright(treeElem<T>* p)
    {
        if(p==root){
            root=p->left;
        }
        treeElem<T>* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }
template<typename T>
    treeElem<T>* tree<T>::rotateleft(treeElem<T>* q)
    {
        if(q == root){
            root=q->right;
        }
        treeElem<T>* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }
template<typename T>
    treeElem<T>* tree<T>::balance(treeElem<T>* p)
    {
        fixheight(p);
        if( balancefactor(p)==2 )
        {
            if( balancefactor(p->right) < 0 )
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if( balancefactor(p)==-2 )
        {
            if( balancefactor(p->left) > 0  )
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p;
    }
template<typename T>
    treeElem<T>* tree<T>::_insert(treeElem<T>* p, const T& k)
    {
        if( !p ) return new treeElem<T>(k);
        if( k<p->id )
            p->left = _insert(p->left,k);
        else
            p->right = _insert(p->right,k);
        return balance(p);
    }
template<typename T>
    treeElem<T>* tree<T>::findmin(treeElem<T>* p)
    {
        return p->left?findmin(p->left):p;
    }
template<typename T>
    treeElem<T>* tree<T>::removemin(treeElem<T>* p)
    {
        if( p->left==NULL )
            return p->right;
        p->left = removemin(p->left);
        return balance(p);
    }
template<typename T>
    treeElem<T>* tree<T>::_remove(treeElem<T>* p, const T& k)
    {
        if( !p ) return NULL;
        if( k < p->id )
            p->left = _remove(p->left,k);
        else if( k > p->id )
            p->right = _remove(p->right,k);
        else //  k == p->id
        {
            treeElem<T>* q = p->left;
            treeElem<T>* r = p->right;
            delete p;
            if( !r ) return q;
            treeElem<T>* min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }
template<typename T>
    void tree<T>::_print_tree(struct treeElem<T>* root) {
        if(root->left != NULL)
            _print_tree(root->left);
        cout << "Value = " << root->id <<endl;
        if(root->right != NULL)
            _print_tree(root->right);

    }
template<typename T>
    void tree<T>::_Print(treeElem<T> *q, long n)
    {
        long i;
        if (q)
        {
            _Print(q->right, n+5);
            for (i = 0; i < n; i++)
                cout<<" ";
            cout<<q->id<<endl;
            _Print(q->left, n+5);
        }
    }
template<typename T>
    treeElem<T>* tree<T>::_findElem(treeElem<T>* root, const T& id)const{
    if(root==NULL) return NULL;
        if(id<root->id){
            return _findElem(root->left, id);
        }
        if(id>root->id){
            return _findElem(root->right, id);
        }
        return root;
    }
template<typename T>
    void tree<T>::_DeleteAll(treeElem<T> *root)
    {
        if(root==NULL) return;
        if (root->left!=NULL)
        {
            _DeleteAll(root->left);
        }
        if (root->right!=NULL)
        {
            _DeleteAll(root->right);
        }

        delete root;

    }
template<typename T>
    tree<T>::tree(): root(NULL) {}
template<typename T>
    tree<T>::~tree(){
        _DeleteAll(root);
    };
template<typename T>
    void tree<T>::insert(const T& value){
        root = _insert(root, value);
    }
template<typename T>
    bool tree<T>::exists(const T& value) const{
        if(_findElem(root, value)==NULL){ return false;} else return true;
    }
template<typename T>
    void tree<T>::remove(const T& value){
        root = _remove(root, value);
    }

    // И этот тоже, хотя к нему потом ещё вернёмся
template<typename T>
    void tree<T>::print(){
        _print_tree(root);
    }
template<typename T>
    void tree<T>::DeleteAll() {
        _DeleteAll(root);
    }
template<typename T>
    void tree<T>::PrintLikeATree(){
        _Print(root, root->height);
    }

    template class tree<int>;
template class tree<string>;
