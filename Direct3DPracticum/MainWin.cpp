#include "Apps.h"


int CALLBACK WinMain( 
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,		 
	int nShowCmd)			 
{
	return App{}.Go();
};