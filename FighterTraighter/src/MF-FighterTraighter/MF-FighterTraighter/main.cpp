#include "App.h"
#include <stdexcept>
int main(int argi, char* argc[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // check for memory leaks
	try{
	App app;
	app.run();
	}
	catch (exception e) {
		std::cout << e.what() << std::endl;
	}
	catch(...){
		std::cout << "EXCEPTION" << std::endl;
	}
	return 0;
}