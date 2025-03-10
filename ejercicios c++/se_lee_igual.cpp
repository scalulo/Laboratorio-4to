#include <iostream>
using namespace std;

int main(){
    string palabra;
    string cadenaalrevez="";

     cout<<"ingrese la palabra: "<<endl;
    cin>>palabra;
     int largo1=palabra.size();
   
    while(largo1>=0){
    largo1=largo1-1;
    cadenaalrevez=cadenaalrevez+palabra[largo1];
    
    }
    cout<<cadenaalrevez<<endl;
    if(cadenaalrevez==palabra){
    cout<<"se lee igual"<<endl;
    }
    else{
        cout<<"se lee distinto"<<endl;
    }
    }
