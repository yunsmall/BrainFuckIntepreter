#pragma once
#include <stdexcept>

namespace BrainFuck
{
    class UnsupportedChar : public std::invalid_argument
    {
    public:
        explicit UnsupportedChar(char c): std::invalid_argument(std::string("unsupported char ") + c)
        {
        };
        virtual ~UnsupportedChar() override = default;
    };

    class UnpairedBracket:public std::logic_error {
    public:
        explicit UnpairedBracket(const std::string& __arg) :
            logic_error(__arg) {
        }

        virtual ~UnpairedBracket() = default;
    };

    class UnpairedRightBracket:public UnpairedBracket {
    public:
        explicit UnpairedRightBracket(const std::string& __arg="未匹配的右括号") :
            UnpairedBracket(__arg) {
        }
        virtual ~UnpairedRightBracket() = default;
    };

    class UnpairedLeftBracket:public UnpairedBracket {
    public:
        explicit UnpairedLeftBracket(const std::string& __arg="未匹配的左括号") :
            UnpairedBracket(__arg) {
        }
        virtual ~UnpairedLeftBracket() = default;
    };
}
