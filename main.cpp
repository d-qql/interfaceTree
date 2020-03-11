#include <iostream>

using namespace std;
class tree;
class treeElem{
private:
    int id;
    unsigned char height;
    treeElem* left;
    treeElem* right;


public:
    friend tree;
    treeElem(int k): id(k), left(NULL), right(NULL), height(1) {}

};


class Container
{
public:
    // Виртуальные методы, должны быть реализованы вашим контейнером
    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;

    // И этот тоже, хотя к нему потом ещё вернёмся
    virtual void print() = 0;

    // Виртуальный деструктор (пока просто поверьте, что он нужен)
    virtual ~Container() { };
};

class tree: public Container{
private:
    treeElem* root;

    unsigned char height(treeElem* p)
    {
        return p?p->height:0;
    }

    int balancefactor(treeElem* p)
    {
        return height(p->right)-height(p->left);
    }

    void fixheight(treeElem* p)
    {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl>hr?hl:hr)+1;
    }

    treeElem* rotateright(treeElem* p)
    {
        if(p==root){
            root=p->left;
        }
        treeElem* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }

    treeElem* rotateleft(treeElem* q)
    {
        if(q == root){
            root=q->right;
        }
        treeElem* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }

    treeElem* balance(treeElem* p)
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
    treeElem* _insert(treeElem* p, int k)
    {
        if( !p ) return new treeElem(k);
        if( k<p->id )
            p->left = _insert(p->left,k);
        else
            p->right = _insert(p->right,k);
        return balance(p);
    }
    treeElem* findmin(treeElem* p)
    {
        return p->left?findmin(p->left):p;
    }

    treeElem* removemin(treeElem* p)
    {
        if( p->left==NULL )
            return p->right;
        p->left = removemin(p->left);
        return balance(p);
    }

    treeElem* _remove(treeElem* p, int k)
    {
        if( !p ) return NULL;
        if( k < p->id )
            p->left = _remove(p->left,k);
        else if( k > p->id )
            p->right = _remove(p->right,k);
        else //  k == p->id
        {
            treeElem* q = p->left;
            treeElem* r = p->right;
            delete p;
            if( !r ) return q;
            treeElem* min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }

    void _print_tree(struct treeElem* root) {
        if(root->left != NULL)
            _print_tree(root->left);
        cout << "Value = " << root->id <<endl;
        if(root->right != NULL)
            _print_tree(root->right);

    }
    void _Print(treeElem *q, long n)
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
    treeElem* _findElem(treeElem* root, int id){
        if(id<root->id){
            if(root->height==1) return NULL;
            return _findElem(root->left, id);

        }
        if(id>root->id){
            if(root->height==1) return NULL;
            return _findElem(root->right, id);
        }
        return root;
    }
    void _DeleteAll(treeElem *root)
    {
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

public:
    tree(): root(NULL) {}
    ~tree(){
        _DeleteAll(root);
    };
     void insert(int value){
         root = _insert(root, value);
    }
    bool exists(int value){
        if(_findElem(root, value)==NULL){ return false;} else return true;
    }
    void remove(int value){
        root = _remove(root, value);
    }

    // И этот тоже, хотя к нему потом ещё вернёмся
    void print(){
        _print_tree(root);
    }

    void DeleteAll() {
        _DeleteAll(root);
    }
    void PrintLikeATree(){
        _Print(root, root->height);
    }

};

int main()
{
    Container* c = new tree();

    for(int i = 1; i < 10; i++)
        c->insert(i*i);
    c->print();
    if(!c->exists(111))
        cout << "Search for value 111: not found" << endl;

    delete c;
    return 0;
}