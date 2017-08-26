#include "clUtil.h"
// #include <cstdlib>

namespace cl {
  /*
	void copyAtoB(clUniformVariable& a,clUniformVariable& b) {
		std::memcpy(reinterpret_cast<char*>(&b),reinterpret_cast<char*>(&a),sizeof(clUniformVariable));
	}
	*/

clB IsEndedWithSlash(std::string s){
  return s.find_last_of('/')==s.length()-1;
}
}
