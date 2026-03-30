#pragma once
#include "../../Deps/kiero/minhook/include/MinHook.h"
#include "Example_Hooks.h"
#include <stdio.h>


void HookingManager() {

	ExExample_Hooks();

	printf("\nSuccessfully Hooked!\n");
}