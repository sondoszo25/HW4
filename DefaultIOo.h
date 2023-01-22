#ifndef  DefaultIOo.h 
#define  DefaultIOo.h 
#include <string>
#include <stdbool.h>



class DefaultIO{
protected:
bool stat=true;
int sock;
public:
DefaultIO();
virtual std::string read()=0;
virtual void write(std::string s)=0;
bool getflag();
};

class SocketIO : public DefaultIO{
public:
SocketIO(int sockk);
std::string read()override;
void write(std::string s)override;
};


#endif