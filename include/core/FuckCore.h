#pragma once
#include <deque>
#include <string>
#include <map>


namespace BrainFuck {
    class FuckCore{
    public:
        FuckCore();
        ~FuckCore();

        void reset_memory();

        void run_simple_string(const std::string& code);

    private:
        std::string current_code;
        decltype(current_code.cbegin()) code_ptr;

        std::deque<char> memory;
        decltype(memory.begin()) memory_ptr;

        std::map<decltype(current_code.cbegin()),decltype(current_code.cbegin())> while_left_to_right_map;
        std::map<decltype(current_code.cbegin()),decltype(current_code.cbegin())> while_right_to_left_map;

    private:
        void move_right();
        void move_left();
        void increase();
        void decrease();
        void input();
        void output();
        void while_begin();
        void while_end();

        decltype(current_code.cbegin()) find_right_bracket(decltype(current_code.cbegin()) pre_bracket);
        decltype(current_code.cbegin()) find_left_bracket(decltype(current_code.cbegin()) right_bracket);

        //会执行一些清理工作
        void set_current_code(const std::string& code);

        bool next_command();
        void run_current_code_from_begin();

        void jump_to_line_end();
    };
}
