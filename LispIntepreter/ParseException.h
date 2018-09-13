//
// Created by Chen Xujie on 9/13/18.
//

#ifndef LISPINTEPRETER_PARSEEXCEPTION_H
#define LISPINTEPRETER_PARSEEXCEPTION_H
#include <stdexcept>
#include <string>
#include <utility>

class ParseException : public std::exception {
public:
    ParseException(std::string title, std::string msg): _title(std::move(title)), _msg(std::move(msg)){}
    const char* what() const _NOEXCEPT override;
private:
    std::string _title;
    std::string _msg;
};


#endif //LISPINTEPRETER_PARSEEXCEPTION_H
