#include "Space.h"
#include "Menu.h"

#define   _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


void test()
{
	Space space;
	Menu menu;	
	menu.start(space);
}

int main()
{
	test();
	//memory leaks
	cout<<_CrtDumpMemoryLeaks();
	return 0;
}

