#include "../cpptk.h"
#include <iostream>

using namespace Tk;
//using namespace std;

void sayHello()
{
	std::cout << "Hello C++/Tk!" << std::endl;
}

int main(int, char *argv[])
{
     try
     {
          init(argv[0]);
          
          button(".b") -text("Say Hello") -command(sayHello);
          pack(".b") -padx(20) -pady(6);
          
          runEventLoop();
     }
     catch (std::exception const &e)
     {
		 std::cerr << "Error: " << e.what() << '\n';
     }
}
