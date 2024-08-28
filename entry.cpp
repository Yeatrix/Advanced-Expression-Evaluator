#include "entry.h"
#include <iostream>
using namespace std;
SymEntry::SymEntry(){}
SymEntry::~SymEntry(){
    if (this->left){
        delete left;}
    if (this->right){
        delete right;}
    delete val;
}
SymEntry::SymEntry(string k, UnlimitedRational*v){
    key=k;
    val=v;
    left=nullptr;
    right=nullptr;
}

