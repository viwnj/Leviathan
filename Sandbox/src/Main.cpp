#include "SandboxApp.h"
#undef main


int main() {
	auto app = new SandboxApp();
	app->Run();
	delete app;
	return 0;
}