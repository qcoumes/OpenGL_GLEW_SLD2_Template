#ifndef OPENGL_UUID_HPP
#define OPENGL_UUID_HPP

#include <string>

namespace opengl::util {
    
    class Uuid {
        private:
            static unsigned int randomChar();
            
            static std::string randomHex(unsigned int len);
            
        public:
            static std::string uuid4();
    };
    
}

#endif // OPENGL_UUID_HPP
