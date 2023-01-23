#include "CLI.h"
#include <iostream>
void Cli::start(int i){
    if(i==3)
    {
        c3->setK(c2->getK());
        c3->setTypdis(c2->getTypdis());
        c3->setf(c1->getf());
    }
    c[i-1]->Execute();
}

Cli::Cli(DefaultIO* s)
{
 t=s;
 c2=new Command2(s);
 c1=new Command1(s);
 c3=new Command3(s);
c[0]=c1;
c[1]=c2;
c[2]=c3;

}

Cli::~Cli(){
    free(c[1]);
    free(c[0]);
    free(c[2]);
}