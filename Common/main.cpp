

#include "Application.h"


void main()
{
	cout << "welcome. mytools is starting, please wait...\n";
	Sleep(2000);

	Application app;
	app.initialise();
	app.run();
	app.shutdown();

	cout << "bye bye\n";
	Sleep(2000);
}