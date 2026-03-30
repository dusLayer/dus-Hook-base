#pragma once
#include "../../Deps/spoof/returnspoof.hpp"
#include "../Offsets.h"
#include "../../includes.h"


class Example
{
private:
    void* ex_instance;

public:
    explicit Example(void* instance) : ex_instance(instance) {}



    void* GetInstance() const { return ex_instance; }


};