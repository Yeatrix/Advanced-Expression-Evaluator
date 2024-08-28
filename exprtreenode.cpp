#include "exprtreenode.h"
#include<iostream>
using namespace std;
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    if (t=="ADD" || t=="MUL" || t=="SUB" ||t=="DIV"){
        type=t;
        UnlimitedInt *m= new UnlimitedInt(1);
        UnlimitedRational *p= new UnlimitedRational(v,m);
        evaluated_value=p;
        val=nullptr;
        id="";
    }
    if (t=="VAL"){
        type=t;
        UnlimitedInt *m= new UnlimitedInt(1);
        UnlimitedRational *p= new UnlimitedRational(v,m);
        val=p;
        evaluated_value=val;
        id="";
    }
    if(t=="EQU"){
        type=t;
        UnlimitedInt *m= new UnlimitedInt(1);
        UnlimitedRational *p= new UnlimitedRational(v,m);
        evaluated_value=p;
        id="";
    }
    else{
        id=t;
        type="VAR";
        UnlimitedInt * m= v;
        UnlimitedInt *p= new UnlimitedInt("1");
        UnlimitedRational *t= new UnlimitedRational(m,p);
        evaluated_value=t;
        val=t;
    }
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational*v){
    if (t=="ADD" || t=="MUL" || t=="SUB" ||t=="DIV"){
        type=t;
        UnlimitedRational *p= v;
        evaluated_value=p;
        val=nullptr;
        id="";
    }
    else if (t=="VAL"){
        type=t;
        UnlimitedRational *p= v;
        val=p;
        evaluated_value=val;
        id="";
    }
    else if(t=="EQU"){
        type=t;
        UnlimitedRational *p= v;
        evaluated_value=p;
        id="";
    }
    else{
        id=t;
        type="VAR";
        evaluated_value=v;
        val=v;
    }
}


ExprTreeNode::~ExprTreeNode(){
    if (left!=nullptr){
        delete left;
    }
    if (right!=nullptr){
        delete right;
    }
    delete val;
}

