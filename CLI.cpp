#include "CLI.h"
#include <iostream>
/******************
 * Function Name: start
 * Input: int i
 * Output: void
 * Function Operation: starts command i
 ******************/
void Cli::start(int i)
{

    if (i == 3)
    {
        c3->setK(c2->getK());
        c3->setTypdis(c2->getTypdis());
        c3->setf(c1->getf());
    }
    if (i == 4)
    {
        c44->setf(c1->getf());
    }
    if (i == 5)
    {
        c5->setf(c1->getf());
    }
    c[i - 1]->Execute();
}
/******************
 * Function Name: cli ctor
 * Input: defaultIO ptr
 * Output: cli
 * Function Operation: ctor, initializing array of pointers to commands
 ******************/
Cli::Cli(DefaultIO *s)
{
    t = s;
    c2 = new Command2(s);
    c1 = new Command1(s);
    c3 = new Command3(s);
    c44 = new Command4(s);
    c5 = new Command5(s);
    c[0] = c1;
    c[1] = c2;
    c[2] = c3;
    c[3] = c44;
    c[4] = c5;
}
/******************
 * Function Name: cli dtor
 * Input: none
 * Output:
 * Function Operation: deleting cli
 ******************/
Cli::~Cli()
{
    delete (c1);
    delete (c2);
    delete (c3);
    delete (c44);
    delete (c5);
}