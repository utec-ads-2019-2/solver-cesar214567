#include <iostream>
#include "nodo.h"
#include <stack> 
#include <string>
#include <vector> 
#include <cmath>
#include <map>
using namespace std; 
int get_numero(string palabra,int &start, int end){
    int i=start;
    vector<int> temporal;
    int int_temporal;
    while(i<end && isdigit(palabra[i])){
        int_temporal=palabra[i]-'0';
        temporal.push_back(int_temporal);
        i++;
        
    }
    int_temporal=0;
    for (int j=0;j<temporal.size();j++){
        int_temporal=int_temporal+temporal[j]*pow(10,temporal.size()-1-j);
    }
    start=i;
    return int_temporal;
}

int get_valor_de_string(char cosa){
    switch(cosa){
        case '+':return 1;
        case '-':return 1;
        case '*':return 2;
        case '/':return 2;
        case '^':return 3;
        case '(':return 1;
        case ')':return 1;
        default: return 10;



    }
}


vector<string> ordenacion_inicial(string palabra){
    stack<string> stackk;
    vector<string> devolucion;
    int i=0;
    if(palabra[0]=='('){
        i++;
    }
    while (palabra[i]!='\n' && i<palabra.size()){
        if (!isdigit(palabra[i])){
            if(stackk.empty() ){
                string temporal="";
                temporal+=palabra[i];
                stackk.push(temporal);
                i++;
            }else{
                if (palabra[i]==')'){
                }
                if(get_valor_de_string(stackk.top()[0])>=get_valor_de_string(palabra[i]) || palabra[i]=='(' || palabra[i]==')'){
                    if(palabra[i]=='('){
                        while(stackk.size()!=1 && !stackk.empty()){
                            devolucion.push_back(stackk.top());
                            stackk.pop();
                        }
                        break;
                    }else{
                        while (!stackk.empty()){
                            if(get_valor_de_string(stackk.top()[0])>=get_valor_de_string(palabra[i])){
                            devolucion.push_back(stackk.top());
                            stackk.pop();
                            }else{
                                break;
                            }
                        }
                    }
                    
                }
                string temporal="";
                temporal+=palabra[i];
                if (palabra[i]=='(' || palabra[i]==')'){
                    i++;
                }else{
                    stackk.push(temporal);
                    i++;
                }
                
                    
                   



            }
            
        }else{
            string temporal=to_string(get_numero(palabra,i,palabra.size()));
            devolucion.push_back(temporal);
        }
    }
    while (!stackk.empty()){
        string temporal="";
        temporal+=stackk.top();
        devolucion.push_back(temporal);
        stackk.pop();
    }
    for (int i=0;i<devolucion.size();i++){
        cout<<devolucion[i]<<endl;
    }
    return devolucion;
}

double get_valor_de_palabra(string palabra){
    stack<double> stackk;
    vector<string> resultado=ordenacion_inicial(palabra);
    map<string,int> mapa;
    for (int i=0;i<resultado.size();i++){
        if (isdigit(resultado[i][0]) && resultado[i][0]!='\n'){
            stackk.push(stoi(resultado[i]));
        }else{
            if(resultado[i][0]-'A'>=0 && resultado[i][0]-'A'!=29){
                string letra="";
                letra+=resultado[i][0];
                const string temporal=letra;
                if (mapa.find(temporal)!=mapa.end()){
                    stackk.push(mapa[letra]);
                }else{
                    cout<<"ingrese el valor de "<<resultado[i][0]<<endl;
                    int valor;
                    cin>>valor;
                    stackk.push(valor);
                    mapa[temporal]=valor;
                }
            }else{
                if(resultado[i][0]!='\n'){
                    int temporal=stackk.top();
                    stackk.pop();
                    
                    switch(resultado[i][0]){
                        case '+':{
                            temporal=stackk.top()+temporal;
                            stackk.pop();
                            stackk.push(temporal);
                            break;
                        }
                        case '-':{
                            temporal=stackk.top()-temporal;
                            stackk.pop();
                            stackk.push(temporal);
                            break;
                        }
                        case '*':{
                            temporal=stackk.top()*temporal;
                            stackk.pop();
                            stackk.push(temporal);
                            break;
                        }
                        case '/':{
                            temporal=stackk.top()/temporal;
                            stackk.pop();
                            stackk.push(temporal);
                            break;
                        }
                        case '^':{
                            temporal=pow(stackk.top(),temporal);
                            stackk.pop();
                            stackk.push(temporal);
                        break;
                        }
                    }
                }
            }
            
            
        }

    }
    
    return stackk.top();
}



int main(){
    string palabra;
    double value=0;
    cin>>palabra;
    value=get_valor_de_palabra(palabra);
    cout<<value<<endl;
}