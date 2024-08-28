#include "symtable.h"
#include <iostream>
using namespace std;
//

void insert2(string k , UnlimitedRational* v, SymEntry*root){
    if (k<root->key){
        if (root->left!=nullptr){
            insert2(k, v, root->left);}
        else{
            SymEntry* n = new SymEntry (k,v);
            root->left=n;
        }
    }
    else{
        if (root->right!=nullptr){
            insert2(k, v, root->right);
        }
        else{
            SymEntry*n=new SymEntry(k,v);
            root->right=n;
        }
    }
}

//
SymbolTable::SymbolTable(){}
SymbolTable::~SymbolTable(){
    if (root!=nullptr){
        if (root!=nullptr){
            delete root->left;
        }
        if (root->right){
            delete root->right;
        }
        delete root;
            
        }
    
    
}




void SymbolTable::insert(string k, UnlimitedRational* v){
    if (root!=nullptr){
        size++;
        insert2(k, v,root);
    }
    else{
        size++;
        root=new SymEntry(k,v);
    }
}

SymEntry *findmin(SymEntry * root){
    SymEntry *n = root;
    while (n->left!=nullptr){
        n=n->left;
    }
    return (n);
}

SymEntry *r1(SymEntry * root ,string data){
    if (root==nullptr){
        return (root);
    }
    else{
        if (root->key> data){
            root->left=r1 (root->left,data);
        }
        else if (root->key< data){
            root->right=r1(root->right,data);
        }
        else{
            if (root->left==nullptr){
                return (root->right);
            }
            else if (root->right==nullptr){
                return (root->left);
            }
            else{
                SymEntry *temp =findmin(root->right);
                root->val=temp->val;
                r1(root->right,temp->key);
                return (root);

            }
        }
    }
    return root;
}



void SymbolTable::remove(string k) {
    r1(root,k);
}



int SymbolTable::get_size(){
    return size;
}

UnlimitedRational* SymbolTable::search(string k){
    SymEntry* n;
    n=root;
    while (n!=nullptr){
        if (n->key==k){
            return (n->val);
        }
        else if (n->key<k){
            n=n->right;
        }
        else{
            n=n->left;
        }
    }
    return (nullptr);
}

SymEntry* SymbolTable::get_root(){
    return (root);
}
