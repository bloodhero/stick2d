#include "MyBootstrap.h"

#include <stick2d.h>
#include <Core/EntryPoint.h>


stick2d::Bootstrap* stick2d::createBootstrap()
{
	return new MyBootstrap;
}
