#include <iostream>
#include <fstream>
#include "types.hpp" 

int main() {
	int w, t;
	std::filebuf fb;
	if (fb.open ("world.map",std::ios::in))
  {
	Map m();
	
    std::istream is(&fb);
	is >> m;
	is >> w;
	std::cout << w;
	is >> t;
	std::cout << t;
	fb.close();
	
	
    
  }
	
	return 0;
}