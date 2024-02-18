#include "private.h"

PrvFields::PrvFields(){
    ifstream prv("../res/prv");
    cout << "Eeooeoe" <<endl;
    if (prv.is_open()) {
        std::string line;
        int i =0;
        while (std::getline(prv, line)) {
            flds[i] = line;
            i++;
        }  
        prv.close();
    }
};

void PrvFields::print(){
    for(int i=0; i<=flds.length-1; i++){
        cout <<  i+1 <<": " << flds[i] << endl;
    }
};

string PrvFields::get(string fld){
    return "dd";
};