#include "ulimitedrational.h"
using namespace std;
#include <iostream>


bool campare1(string i1,string i2){
    if (i1.length()>i2.length()){
        return true;
    }
    else if (i2.length()>i1.length()){
        return false;
    }
    for (int i = 0; i < static_cast<int>(i1.length()); i++) {
        if ((i1[i])>(i2[i])){
            return true;
        }
        else if (i1[i] < i2[i]) {
                    return false;
        }
    }
    return false;
}

UnlimitedInt* hcf1(UnlimitedInt*i1,UnlimitedInt*i2){
    if (i1->get_sign()==0 || i2->get_sign()==0){
        UnlimitedInt*h= new UnlimitedInt("0");
        return h;
    }
    if (i1->get_sign()==-1){
        string a=i1->to_string();
        a.erase(0,1);
        i1=new UnlimitedInt(a);
    }
    if (i2->get_sign()==-1){
        string a=i2->to_string();
        a.erase(0,1);
        i2=new UnlimitedInt(a);
    }
    if (!(UnlimitedInt::mod(i1,i2)->to_string()=="0") && !(UnlimitedInt::mod (i2,i1)->to_string()=="0")){
        if (campare1(i1->to_string(), i2->to_string())){
            return (hcf1(UnlimitedInt::mod(i1,i2),i2));
        }
        else{
            return (hcf1(i1,UnlimitedInt::mod(i2,i1)));
        }
    }
    else{
        if (UnlimitedInt::mod(i2,i1)->to_string()=="0"){
            return (i1);
        }
        else{
            return (i2);
        }
    }
}




UnlimitedRational::UnlimitedRational(){
    
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    p=num;
    q=den;
}
UnlimitedRational::~UnlimitedRational(){
    delete  p;
    delete  q;
}
UnlimitedInt* UnlimitedRational::get_p(){
    return (p);
}
UnlimitedInt* UnlimitedRational::get_q(){
    return (q);
}
string UnlimitedRational::get_p_str(){
    return(p->to_string());
}
string UnlimitedRational::get_q_str(){
    return q->to_string();
}
string UnlimitedRational::get_frac_str(){
    string a="";
    a+=get_p_str();
    a+="/";
    a+=get_q_str();
    return (a);
}
UnlimitedRational* UnlimitedRational::add(UnlimitedRational*i1, UnlimitedRational*i2){
    UnlimitedInt*num= UnlimitedInt::add(UnlimitedInt:: mul(i1->get_p(),i2->get_q()),UnlimitedInt::mul(i1->get_q(),i2->get_p()));
    UnlimitedInt*den=UnlimitedInt::mul(i1->get_q(),i2->get_q());
    UnlimitedInt*h= hcf1(num, den);
    if (h->get_sign()!=0){
        num=UnlimitedInt::div(num,h);
        den=UnlimitedInt::div(den,h);
    }
    if (num->get_sign()==-1 && den->get_sign()==-1){
        string a=num->to_string();
        a.erase(0,1);
        num=new UnlimitedInt(a);
        string b=den->to_string();
        b.erase(0,1);
        den=new UnlimitedInt(b);
    }
    if (num->get_sign()==1&& den->get_sign()==-1){
        string a=num->to_string();
        a="-"+a;
        num= new UnlimitedInt(a);
        string b=den->to_string();
        b.erase(0,1);
        den=new UnlimitedInt(b);
    }
    UnlimitedRational* n= new UnlimitedRational(num,den);
    return (n);
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational*i1,UnlimitedRational*i2){
    string a=i2->get_p_str();
    if (i2->get_p()->get_sign()==-1){
        a.erase(0,1);
    }
    else{
        a="-"+a;
    }
    UnlimitedInt* p=new UnlimitedInt(a);
    UnlimitedRational*i3= new UnlimitedRational(p,i2->get_q());
    return (UnlimitedRational::add(i1,i3));
}


UnlimitedRational* UnlimitedRational::mul(UnlimitedRational*i1,UnlimitedRational*i2){
    if (i1->get_q_str()=="0" || i2->get_q_str()=="0"){
        UnlimitedInt*i1 =new UnlimitedInt("0");
        UnlimitedRational * r1= new UnlimitedRational(i1,i1);
        return (r1);
    }
    UnlimitedInt*num=UnlimitedInt::mul(i1->get_p(),i2->get_p());
    UnlimitedInt*den=UnlimitedInt::mul(i1->get_q(),i2->get_q());
    UnlimitedInt*h= hcf1(num, den);
    if (h->get_sign()!=0){
        num=UnlimitedInt::div(num,h);
        den=UnlimitedInt::div(den,h);
    }
    if (num->get_sign()==-1 && den->get_sign()==-1){
        string a=num->to_string();
        a.erase(0,1);
        num=new UnlimitedInt(a);
        string b=den->to_string();
        b.erase(0,1);
        den=new UnlimitedInt(b);
    }
    if (num->get_sign()==1&& den->get_sign()==-1){
        string a=num->to_string();
        a="-"+a;
        num= new UnlimitedInt(a);
        string b=den->to_string();
        b.erase(0,1);
        den=new UnlimitedInt(b);
    }
    UnlimitedRational* n= new UnlimitedRational(num,den);
    return (n);
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational*i1,UnlimitedRational*i2){
    if (i1->get_p_str()=="0" || i2->get_p_str()=="0" || i2->get_p_str()=="0"){
        UnlimitedInt*i1 =new UnlimitedInt("0");
        UnlimitedRational * r1= new UnlimitedRational(i1,i1);
        return (r1);
    }
    UnlimitedInt*num=UnlimitedInt::mul(i1->get_p(),i2->get_q());
    UnlimitedInt*den=UnlimitedInt::mul(i1->get_q(),i2->get_p());
    UnlimitedInt*h= hcf1(num, den);
    if (h->get_sign()!=0){
        num=UnlimitedInt::div(num,h);
        den=UnlimitedInt::div(den,h);
    }
    if (num->get_sign()==-1 && den->get_sign()==-1){
        string a=num->to_string();
        a.erase(0,1);
        num=new UnlimitedInt(a);
        string b=den->to_string();
        b.erase(0,1);
        den=new UnlimitedInt(b);
    }
    if (num->get_sign()==1&& den->get_sign()==-1){
        string a=num->to_string();
        a="-"+a;
        num= new UnlimitedInt(a);
        string b=den->to_string();
        b.erase(0,1);
        den=new UnlimitedInt(b);
    }
    UnlimitedRational* n= new UnlimitedRational(num,den);
    return (n);
}


// int main(){
//    UnlimitedInt* i1=new UnlimitedInt("5");
//    UnlimitedInt* i2=new UnlimitedInt("0");
//    UnlimitedInt* i3=new UnlimitedInt("6");
//    UnlimitedInt* i4=new UnlimitedInt("3");
//    UnlimitedRational* r1 =new UnlimitedRational(i1,i2);
//    UnlimitedRational* r2=new UnlimitedRational(i3,i4);
// //    cout<<UnlimitedRational::add(r1, r1)->get_frac_str()->;
//    return 0;
// }

