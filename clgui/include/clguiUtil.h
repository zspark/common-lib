#pragma once

#include "clguiComponentVariable.h"

namespace clgui {
	void copyAtoB(UniformComponentVariable& a,UniformComponentVariable& b);
	cl::uint GetUniqueId();
}