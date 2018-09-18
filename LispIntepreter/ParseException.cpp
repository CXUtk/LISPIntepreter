//
// Created by Chen Xujie on 9/13/18.
//

#include "ParseException.h"

const char *ParseException::what() const _NOEXCEPT {
    static char buffer[4096];
    sprintf(buffer, "[PARSE ERROR: %s]\n%s\n", _title.c_str(), _msg.c_str());
	
    return buffer;
}
