// f42r.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"

int32 main(int32 argc, char* argv[])
{
	return Engine::Create(argc, argv)->Run();
}