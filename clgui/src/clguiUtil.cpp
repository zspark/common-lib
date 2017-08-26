#include "clguiUtil.h"
#include <cstdlib>

static cl::uint s_uNextUniqueId = 0;
namespace clgui {
	void copyAtoB(UniformComponentVariable& a,UniformComponentVariable& b) {
		std::memcpy(reinterpret_cast<char*>(&b),reinterpret_cast<char*>(&a),sizeof(UniformComponentVariable));
	}

	cl::uint GetUniqueId() {
	  s_uNextUniqueId++;
	  return s_uNextUniqueId;
	}
	
}
