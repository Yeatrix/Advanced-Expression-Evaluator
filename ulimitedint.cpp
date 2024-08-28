/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include <iostream>
#include "ulimitedint.h"
using namespace std;
UnlimitedInt::UnlimitedInt(){}
UnlimitedInt::UnlimitedInt(string s){
    unlimited_int=new int [10000];
    string a=s;
    if (s[0]=='-'){
        sign=-1;
        size=s.length()-1;
        a.erase(0,1);
    }
    else if (s[0]=='0'){
        sign=0;
        size=1;
        unlimited_int[0]=0;
    }
    else{
        sign=1;
        size=a.length();
    }
    for (int i = 0; i < static_cast<int>(a.length()); i++) {        
        unlimited_int[i]=(static_cast<int>(a[i]-'0'));
    }
}
UnlimitedInt::UnlimitedInt(int i){
    string s=std::to_string(i);
    unlimited_int=new int [10000];
    string a=s;
    if (s[0]=='-'){
        sign=-1;
        size=s.length()-1;
        a.erase(0,1);
    }
    else if (s[0]=='0'){
        sign=0;
        size=1;
        unlimited_int[0]=0;
    }
    else{
        sign=1;
        size=a.length();
    }
    for (int i = 0; i < static_cast<int>(a.length()); i++) {
        unlimited_int[i]=(static_cast<int>(a[i]-'0'));
    }
}
UnlimitedInt::~UnlimitedInt(){
    delete [] unlimited_int;
}
int UnlimitedInt:: get_size(){
    return size;
}
int UnlimitedInt:: get_sign(){
    return sign;
}
int* UnlimitedInt::get_array(){
    return unlimited_int;
}
string UnlimitedInt::to_string(){
    string a="";
    for (int i=0; i<size; i++){
        a=a+static_cast<char>(unlimited_int[i]+'0');
    }
    if (sign==-1){
        a="-"+a;
    }
    return a;

}

int UnlimitedInt:: get_capacity(){
    return capacity;
}



UnlimitedInt* UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2){
    int size= i1->get_size();
    if (i2->get_size()>i1->get_size()){
        size= i2->get_size();
    }
    int *final=new int[size];
    for (int i=0; i<size; i++){
        final[i]=0;
    }
    int *arr1=i1->get_array();
    int *arr2=i2->get_array();
    for (int i=0; i<i1->get_size();i++){
        final[size+i-i1->get_size()]+=(i1->get_sign())*arr1[i];
    }
    for (int i=0; i<i2->get_size();i++){
        final[size+i-i2->get_size()]+=(i2->get_sign())*arr2[i];
    }
    int i=0;
    while (final[i]==0){
        i++;
        if (i==size){
            break;
        }
    }
    int *final2=new int [size-i];
    size=size-i;
    for (int j=0; j<size; j++){
        final2[j]=final[j+i];
    }
//    for (int i=0; i<size; i++){
//        cout<<final2[i];
//    }
    int *arr=final2;
    int n=0;
    if(arr[0]==0){
        UnlimitedInt* t=new UnlimitedInt("0");
        return t;
    }
    else if (arr[0]>0){
        n=1;
    }
    else{
        n=-1;
    }
    for (int i=size-1; i>=1; i--){
        if ((arr[i]*n)>=0){
            arr[i-1]+=(arr[i])/10;
            arr[i]=arr[i]%10;
        }
        else{
            arr[i]+=10*n;
            arr[i-1]-=n*1;
            arr[i-1]+=(arr[i])/10;
            arr[i]=arr[i]%10;
        }
    }
    string s="";
    int num=0;
    while (arr[num]==0){
        num++;
    }
    if (n*arr[num]>9){
        s=s+static_cast<char>((n*arr[0]/10)+'0');
    }
    for (int j=num; j<size; j++){
        s=s+static_cast<char>((n*arr[j]%10)+'0');
    }
    if (n==-1){
        s="-"+s;
    }
    UnlimitedInt* t=new UnlimitedInt(s);
    return t;
}
UnlimitedInt* UnlimitedInt::sub(UnlimitedInt*i1,UnlimitedInt*i2){
    string s=i2->to_string();
    if (i2->get_sign()==1){
        s="-"+s;
    }
    if (i2->get_sign()==-1){
        s.erase(0,1);
    }
    UnlimitedInt* i3=new UnlimitedInt(s);
    return (UnlimitedInt::add(i1,i3));
}


UnlimitedInt* UnlimitedInt::mul(UnlimitedInt*i1, UnlimitedInt*i2){
    int size=i1->get_size()+i2->get_size()-1;
    int *final=new int[size];
    for (int i=0; i<size; i++){
        final[i]=0;
    }
    for (int i=0; i<i1->get_size();i++){
        for (int j=0; j<i2->get_size();j++){
            final[i+j]+=i1->get_array()[i]*i2->get_array()[j];
        }
    }
    int n=i1->get_sign()*i2->get_sign();
    if (n==0){
        UnlimitedInt* t=new UnlimitedInt("0");
        return t;
    }
    int i=0;
    while (final[i]==0){
        i++;
        if (i==size){
            break;
        }
    }
    int *final2=new int [size-i];
    size=size-i;
    for (int j=0; j<size; j++){
        final2[j]=final[j+i];
    }
    int *arr=final2;
    for (int i=size-1; i>=1; i--){
            arr[i-1]+=(arr[i])/10;
            arr[i]=arr[i]%10;
    }
    string s;
    if (arr[0]>9){
        s=s+static_cast<char>((arr[0]/10)+'0');
    }
    for (int j=0; j<size; j++){
        s=s+static_cast<char>((arr[j]%10)+'0');
    }
    if (n==-1){
        s="-"+s;
    }
    UnlimitedInt* t=new UnlimitedInt(s);
    return t;
}

bool campare(string i1,string i2){
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
string quotient(string i1, string i2){
    UnlimitedInt*n=new UnlimitedInt(i2);
    for (int i=0; i<=9;i++){
        UnlimitedInt*m=new UnlimitedInt(i);
        if (campare(UnlimitedInt::mul(n,m)->to_string(), i1)){
            return (to_string(i-1));
            }
        }
    return (to_string(9));
}

string reminder(string i1, string i2){
    UnlimitedInt* q= new UnlimitedInt(quotient(i1, i2));
    UnlimitedInt* t=new UnlimitedInt(i1);
    UnlimitedInt* t1=new UnlimitedInt(i2);
    UnlimitedInt* p= new UnlimitedInt("0");
    string s= UnlimitedInt::sub(UnlimitedInt::mul(t1,q),t)->to_string();
    s.erase(0,1);
    return s;
}

 UnlimitedInt* UnlimitedInt::div(UnlimitedInt*i1, UnlimitedInt*i2){
    string a=i1->to_string();
    string b=i2->to_string();
    if (i1->get_sign()==-1){
        a.erase(0,1);
    }
    if (i2->get_sign()==-1){
        b.erase(0,1);
    }
    int i=0;
    string temp="";
    string result="";
    int r=0;
     while (i < static_cast<int>(a.length())){
        if (campare(b, temp)){
            if (temp!="" || a[i]!='0'){
                temp=temp+a[i];}
            i++;
            r++;
            if (r>1&& result!=""){
                result=result+"0";
            }
        }
        else{
            result=result+quotient(temp,b);
            temp=reminder(temp,b);
            r=0;
        }
    }
     if (temp==""){
         temp="0";
     }
    result=result+quotient(temp,b);
    temp=reminder(temp,b);
    i++;
    int n=i1->get_sign()*i2->get_sign();
    if (n==-1 ){
        if (result!="0"){
            result="-"+result;}
        UnlimitedInt* t1= new UnlimitedInt("-1");
        UnlimitedInt*pr= new UnlimitedInt(result);
        if (temp!=""){
            pr=UnlimitedInt::add(pr,t1);}
        return pr;
    }
    UnlimitedInt*pr= new UnlimitedInt(result);
    return pr;
}


UnlimitedInt* UnlimitedInt::mod(UnlimitedInt*i1, UnlimitedInt*i2){
    UnlimitedInt *ques= div(i1,i2);
    UnlimitedInt* result= UnlimitedInt::sub(i1,mul(i2,ques));
    return result;
}


bool same(UnlimitedInt*i1, UnlimitedInt*i2){
    if (i1->get_size()==i2->get_size()){
        for (int i=0; i<i1->get_size(); i++){
            if (i1->get_array()[i]!=i2->get_array()[i]){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

UnlimitedInt* hcf(UnlimitedInt*i1,UnlimitedInt*i2){
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
        if (campare(i1->to_string(), i2->to_string())){
            return (hcf(UnlimitedInt::mod(i1,i2),i2));
        }
        else{
            return (hcf(i1,UnlimitedInt::mod(i2,i1)));
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


// int main(){
//     UnlimitedInt*i1= new UnlimitedInt("0");
//     cout<<i1->get_size();
//     UnlimitedInt*i2=new UnlimitedInt("67");
//     cout<<UnlimitedInt::add(i1,i2)->to_string();
//     // cout<<reminder("23","40");
//     // UnlimitedInt*i1= new UnlimitedInt("23");
//     // UnlimitedInt *i2=new    UnlimitedInt("40");
//     // cout<<UnlimitedInt::div(i1,i2)->to_string();
// }
