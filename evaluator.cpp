#include "evaluator.h"
#include <iostream>
using namespace std;

Evaluator::Evaluator(){
    vector<ExprTreeNode *>v1;
    symtable=new SymbolTable;
    expr_trees=v1;
}

Evaluator::~Evaluator(){
    expr_trees.clear();
}

ExprTreeNode* parse1(vector<string> code, int left, int right, SymbolTable* s1){
    if ((right-left)==1){
        if (s1->search(code[left])==nullptr){
            // cout<<"e1";
            UnlimitedInt *i1= new UnlimitedInt(code[left]);
            UnlimitedInt *i2= new UnlimitedInt ("1");
            UnlimitedRational*r2 =new UnlimitedRational(i1,i2);
            ExprTreeNode* t1= new ExprTreeNode("VAL",r2);
            // cout<<"d1";
            return (t1);}
        else{
            // cout<<"e2";
            ExprTreeNode *t1 =new ExprTreeNode(code[left],s1->search(code[left]));
            // cout<<"d2";
            return (t1);
        }
    }
    else{
        int temp=0;
        for (int i = left + 1; i < static_cast<int>(code.size() - 1); i++) {
            if (code[i]=="("){
                temp++;
            }
            else if (code[i]==")"){
                temp--;
            }
            else if (code [i]=="+" && temp==0){
                // cout<<"e3";
                UnlimitedRational* t= new UnlimitedRational();
                ExprTreeNode* root= new ExprTreeNode("ADD",t);
                root->left=parse1(code, left+1, i, s1);
                root->right=parse1(code,i+1,right-1,s1);
                root->evaluated_value=UnlimitedRational:: add(root->left->evaluated_value, root->right->evaluated_value);
                root->val=UnlimitedRational:: add(root->left->evaluated_value, root->right->evaluated_value);
                // cout<<"d3";
                return root;
            }
            else if (code [i]=="-" && temp==0){
                UnlimitedRational* t= new UnlimitedRational();
                ExprTreeNode* root= new ExprTreeNode("SUB",t);
                root->left=parse1(code, left+1, i, s1);
                root->right=parse1(code,i+1,right-1,s1);
                root->evaluated_value=UnlimitedRational:: sub(root->left->evaluated_value, root->right->evaluated_value);
                root->val=UnlimitedRational:: sub(root->left->evaluated_value, root->right->evaluated_value);
                // cout<<"d4";
                return root;
            }
            else if (code [i]=="*" && temp==0){
                // cout<<"e5";
                UnlimitedRational* t= new UnlimitedRational();
                ExprTreeNode* root= new ExprTreeNode("MUL",t);
                root->left=parse1(code, left+1, i, s1);
                root->right=parse1(code,i+1,right-1,s1);
                root->evaluated_value=UnlimitedRational:: mul(root->left->evaluated_value, root->right->evaluated_value);
                root->val=UnlimitedRational:: mul(root->left->evaluated_value, root->right->evaluated_value);
                // cout<<"d5";
                return root;
            }
            else if (code [i]=="/" && temp==0){
                // cout<<"e6";
                UnlimitedRational* t= new UnlimitedRational();
                ExprTreeNode* root= new ExprTreeNode("DIV",t);
                root->left=parse1(code, left+1, i, s1);
                root->right=parse1(code,i+1,right-1,s1);
                root->evaluated_value=UnlimitedRational:: div(root->left->evaluated_value, root->right->evaluated_value);
                root->val=UnlimitedRational:: div(root->left->evaluated_value, root->right->evaluated_value);
                // cout<<"d6";
                return root;
            }
        }
        return nullptr;
    }
    return nullptr;
}

void Evaluator::parse(vector<string> code){
    // cout<<"c3";
    UnlimitedRational *r1= new UnlimitedRational();
    ExprTreeNode*root= new ExprTreeNode("EQU",r1);
    ExprTreeNode*r2= new ExprTreeNode(code[0],r1);
    root->left= r2;
    // cout<<"c4";
    root->right=parse1(code, 2, code.size(), symtable);
    // cout<<"c4";
    root->val=root->right->evaluated_value;
    // cout<<"c4";
    root->evaluated_value=root->right->evaluated_value;
    // cout<<"c4";
    expr_trees.push_back(root);
    symtable->insert(code[0], root->evaluated_value);
    // cout<<"c5";
    return ;
}
void Evaluator::eval(){}
//
int main(){
//    input:
//ap1:=4
//ap2:=(ap1-(4/3))
//ap3:=(ap2+(4/5))
//ap4:=(ap3-(4/7))
//ap5:=(ap4+(4/9))
//ap6:=(ap5-(4/11))
//ap7:=(ap6+(4/13))
//    output:
//    4/3
//    8/3
//    4/5
//    52/15
//    4/7
//    304/105
//    4/9
//    1052/315
//    4/11
//    10312/3465
//    4/13
//    147916/45045
    
//pow1:=13
//pow2:=((2*42)/(pow1*pow1))
//pow3:=((3*42)/(pow2*pow2))
//pow4:=((4*42)/(pow3*pow3))
//pow5:=((5*42)/(pow4*pow4))
//    84/1
//    169/1
//    84/169
//    126/1
//    7056/28561
//    28561/56
//    168/1
//    815730721/3136
//    526848/815730721
//    210/1
//    277568815104/665416609183179841
//    3327083045915899205/6608781312

    
//a:=2
//b:=(a*3)
//c:=((a+b)*5)
//d:=(((a-1)*7)+((b+c)/2))
//e:=((a*c)+((b*d)*4))
//f:=((e/2)+((c-d)*a))

//    6/1
//    8/1
//    40/1
//    1/1
//    7/1
//    46/1
//    23/1
//    30/1
//    80/1
//    180/1
//    720/1
//    800/1
//    400/1
//    10/1
//    20/1
//    420/1

//a:=5
//b:=((a+3)*2)
//c:=(((a+b)*3)-7)
//d:=((a/6)*(b/c))
//e:=d
//f:=(e+5)

//    8/1
//    16/1
//    21/1
//    63/1
//    56/1
//    5/6
//    2/7
//    5/21
//    110/21

    
//v:=(13+(2/51))
//g:=(2*v)
//x:=(g+6)
//y:=x

    
//
//    2/51
//    665/51
//    1330/51
//    1636/51

    
//    Evaluator E;
//    vector<std::string> v1 = {"ap1", ":=", "4"};
//    vector<std::string> v2 = {"ap2", ":=", "(", "ap1", "-", "(", "4", "/", "3", ")", ")"};
//    vector<std::string> v3 = {"ap3", ":=", "(", "ap2", "+", "(", "4", "/", "5", ")", ")"};
//    vector<std::string> v4 = {"ap4", ":=", "(", "ap3", "-", "(", "4", "/", "7", ")", ")"};
//    vector<std::string> v5 = {"ap5", ":=", "(", "ap4", "+", "(", "4", "/", "9", ")", ")"};
//    vector<std::string> v6 = {"ap6", ":=", "(", "ap5", "-", "(", "4", "/", "11", ")", ")"};
//    vector<std::string> v7 = {"ap7", ":=", "(", "ap6", "+", "(", "4", "/", "13", ")", ")"};
//    E.parse(v1);
//    cout<<v2[0];  
//    E.parse(v2);
//    E.parse(v3);
//    E.parse(v4);
//    E.parse(v5);
//    E.parse(v6);
//    E.parse(v7);
//    cout<<E.symtable->search("ap1")->get_p_str()<<endl;
//    cout<<E.symtable->search("ap1")->get_q_str()<<endl;
//    cout<<E.symtable->search("ap2")->get_q_str();
//    cout<<E.symtable->search("ap2")->get_p_str();
   
    
    //    84/1
    //    169/1
    //    84/169
    //    126/1
    //    7056/28561
    //    28561/56
    //    168/1
    //    815730721/3136
    //    526848/815730721
    //    210/1
    //    277568815104/665416609183179841
    //    3327083045915899205/6608781312

    
    
//    Evaluator E;
//    vector<std::string> v1 = {"pow1", ":=", "13"};
//    vector<std::string> v2 = {"pow2", ":=", "(", "(", "2", "*", "42", ")", "/", "(", "pow1", "*", "pow1", ")", ")"};
//    vector<std::string> v3 = {"pow3", ":=", "(", "(", "3", "*", "42", ")", "/", "(", "pow2", "*", "pow2", ")", ")"};
//    vector<std::string> v4 = {"pow4", ":=", "(", "(", "4", "*", "42", ")", "/", "(", "pow3", "*", "pow3", ")", ")"};
//    vector<std::string> v5 = {"pow5", ":=", "(", "(", "5", "*", "42", ")", "/", "(", "pow4", "*", "pow4", ")", ")"};
//    E.parse(v1);
//    E.parse(v2);
//    E.parse(v3);
//    E.parse(v4);
//    E.parse(v5);
//    cout<<E.expr_trees[0]->val->get_frac_str()<<endl;
//    cout<<E.expr_trees[1]->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[1]->right->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[1]->right->type<<endl;
//    cout<<E.expr_trees[1]->right->right->type<<endl;
//    cout<<E.expr_trees[1]->right->left->type<<endl;
//    cout<<E.expr_trees[1]->right->right->right->type<<endl;
//    cout<<E.expr_trees[2]->type<<endl;
//    cout<<E.expr_trees[2]->right->type<<endl;
//    cout<<E.expr_trees[2]->right->right->type<<endl;
//    cout<<E.expr_trees[2]->right->left->type<<endl;
//    cout<<E.expr_trees[2]->right->left->left->type<<endl;
//    cout<<E.expr_trees[2]->right->left->right->type<<endl;
//    cout<<E.expr_trees[2]->right->right->left->type<<endl;
//    cout<<E.expr_trees[2]->right->right->right->type<<endl;
//    cout<<E.expr_trees[2]->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->right->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->left->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->left->left->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->left->right->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->right->left->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->right->right->evaluated_value->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->val->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->val->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->right->val->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->left->val->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->left->left->val->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->left->right->val->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->right->left->val->get_frac_str()<<endl;
//    cout<<E.expr_trees[2]->right->right->right->val->get_frac_str()<<endl;
//    cout<<E.symtable->search("pow3")->get_frac_str()<<endl;
//    cout<<E.symtable->search("pow2")->get_frac_str()<<endl;
//    cout<<E.symtable->search("pow1")->get_frac_str()<<endl;
    






//    Evaluator E;
//    vector<std::string> v1 = {"a", ":=", "2"};
//    vector<std::string> v2 = {"b", ":=", "(", "a", "*", "3", ")"};
//    vector<std::string> v3 = {"c", ":=", "(", "(", "a", "+", "b", ")", "*", "5", ")"};
//    vector<std::string> v4 = {"d", ":=", "(", "(", "(", "a", "-", "1", ")", "*", "7", ")", "+", "(", "(", "b", "+", "c", ")", "/", "2", ")", ")"};
//    vector<std::string> v5 = {"e", ":=", "(", "(", "a", "*", "c", ")", "+", "(", "(", "b", "*", "d", ")", "*", "4", ")", ")"};
//    std::vector<std::string> v6 = {"f", ":=", "(", "(", "e", "/", "2", ")", "+", "(", "(", "c", "-", "d", ")", "*", "a", ")", ")"};
//    E.parse(v1);
//    E.parse(v2);
//    E.parse(v3);
//    E.parse(v4);
//    E.parse(v5);
//    E.parse(v6);
//    cout<<E.symtable->search("f")->get_p_str();
    
//    Evaluator E;
//    vector<std::string> v1 = {"a", ":=", "5"};
//    vector<std::string> v2 = {"b", ":=", "(", "(", "a", "+", "3", ")", "*", "2", ")"};
//    vector<std::string> v3 = {"c", ":=", "(", "(", "(", "a", "+", "b", ")", "*", "3", ")", "-", "7", ")"};
//    vector<std::string> v4 = {"d", ":=", "(", "(", "a", "/", "6", ")", "*", "(", "b", "/", "c", ")", ")"};
//    vector<std::string> v5 = {"e", ":=", "d"};
//    vector<std::string> v6 = {"f", ":=", "(", "e", "+", "5", ")"};
//    E.parse(v1);
//    E.parse(v2);
//    E.parse(v3);
//    E.parse(v4);
//    E.parse(v5);
//    E.parse(v6);
//    cout<<E.symtable->search("f")->get_p_str();
    
        
//    Evaluator E;
//    vector<std::string> v1 = {"v", ":=", "(", "13", "+", "(", "2", "/", "51", ")", ")"};
//    vector<std::string> v2 = {"g", ":=", "(", "2", "*", "v", ")"};
    
//    vector<std::string> v3 = {"x", ":=", "(", "(","1", "/", "1",")","/","(","5", "/", "0",")" ")"};
//    vector<std::string> v4 = {"y", ":=", "x"};

//
//    E.parse(v3);
//    cout<<E.symtable->search("x")->get_p_str();
//    cout<<E.symtable->search("x")->get_q_str();
//    cout<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->evaluated_value->get_frac_str());
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->type)<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->type)<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->evaluated_value->get_frac_str())<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->left->type)<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->right->type)<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->right->evaluated_value->get_frac_str())<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->right->left->evaluated_value->get_frac_str())<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->right->left->type)<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->right->right->type)<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->right->right->evaluated_value->get_frac_str())<<endl;
//    cout<<(E.expr_trees[E.expr_trees.size()-1]->right->right->right->val->get_frac_str())<<endl;
//    E.parse(v2);
    
//    E.parse(v3);
//    E.parse(v4);
//    cout<<E.symtable->search("y")->get_p_str();
//    UnlimitedInt* i1=new UnlimitedInt("2983792");
//    UnlimitedInt* i2=new UnlimitedInt("2");
//    cout<<UnlimitedInt::div(i1, i2)->to_string();
   return 0;
}
