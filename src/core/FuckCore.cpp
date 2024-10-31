#include "core/FuckCore.h"

#include <algorithm>

#include "core/Error.h"

BrainFuck::FuckCore::FuckCore(){
    reset_memory();
    set_current_code("");
}

BrainFuck::FuckCore::~FuckCore() {
}

void BrainFuck::FuckCore::reset_memory() {
    memory.clear();
    memory.push_back(0);
    memory_ptr=memory.begin();
}

void BrainFuck::FuckCore::run_simple_string(const std::string &code) {
    current_code=code;
    run_current_code_from_begin();
}

void BrainFuck::FuckCore::move_right() {
    if(memory_ptr==memory.end()-1) {
        memory.push_back(0);
        memory_ptr=memory.end()-1;
    }
    else {
        ++memory_ptr;
    }
}

void BrainFuck::FuckCore::move_left() {
    if(memory_ptr==memory.begin()) {
        memory.push_front(0);
        memory_ptr=memory.begin();
    }
    else {
        --memory_ptr;
    }
}

void BrainFuck::FuckCore::increase() {
    (*memory_ptr)++;
}

void BrainFuck::FuckCore::decrease() {
    (*memory_ptr)--;
}

void BrainFuck::FuckCore::input() {
    *memory_ptr=getchar();
}

void BrainFuck::FuckCore::output() {
    putchar(*memory_ptr);
}

void BrainFuck::FuckCore::while_begin() {
    if(*memory_ptr==0) {
        auto find_ret=while_left_to_right_map.find(code_ptr);
        if(find_ret!=while_left_to_right_map.end()) {
            code_ptr=find_ret->second;//跳转的]的下一条
        }
        else {
            code_ptr=find_right_bracket(code_ptr);
        }
    }
}

void BrainFuck::FuckCore::while_end() {
    if(*memory_ptr!=0) {
        auto find_ret=while_left_to_right_map.find(code_ptr);
        if(find_ret!=while_left_to_right_map.end()) {
            code_ptr=find_ret->second;//跳转的[的下一条
        }
        else {
            code_ptr=find_left_bracket(code_ptr);
        }
    }
}

decltype(BrainFuck::FuckCore::current_code.cbegin()) BrainFuck::FuckCore::find_right_bracket(decltype(current_code.cbegin()) left_bracket) {
    int bracket_count=1;
    auto i=left_bracket+1;
    for(;i!=current_code.cend();i++) {
        if(*i=='[') {
            bracket_count++;
        }
        else if(*i==']') {
            bracket_count--;
        }
        if(bracket_count==0) {
            while_left_to_right_map[left_bracket]=i;
            return i;
        }
    }
    if(i==current_code.cend()) {
        throw UnpairedLeftBracket();
    }
}

decltype(BrainFuck::FuckCore::current_code.cbegin()) BrainFuck::FuckCore::find_left_bracket(decltype(current_code.cbegin()) right_bracket) {
    int bracket_count=1;
    auto i=std::make_reverse_iterator(right_bracket)+1;
    for(;i!=current_code.crend();i++) {
        if(*i==']') {
            bracket_count++;
        }
        else if(*i=='[') {
            bracket_count--;
        }
        if(bracket_count==0) {
            while_right_to_left_map[right_bracket]=i.base()-1;
            return i.base()-1;
        }
    }
    if(i==current_code.crend()) {
        throw UnpairedRightBracket();
    }
}

void BrainFuck::FuckCore::set_current_code(const std::string &code) {
    while_left_to_right_map.clear();
    while_right_to_left_map.clear();
    current_code=code;
}

bool BrainFuck::FuckCore::next_command() {
    if(code_ptr==current_code.end())return false;

    const char current_char=*code_ptr;
    if(isspace(current_char)) {
        goto interprete_end;
    }


    // bool add_code_ptr=true;
    switch (current_char) {
        case '>': {
            move_right();
            break;
        }
        case '<': {
            move_left();
            break;
        }
        case '+': {
            increase();
            break;
        }
        case '-': {
            decrease();
            break;
        }
        case '.': {
            output();
            break;
        }
        case ',': {
            input();
            break;
        }
        case '[': {
            while_begin();
            // add_code_ptr=false;
            break;
        }
        case ']': {
            while_end();
            // add_code_ptr=false;
            break;
        }
        case '#': {
            jump_to_line_end();
            break;
        }
        default:
            throw UnsupportedChar(*code_ptr);
    }

    interprete_end:

    ++code_ptr;
    return true;
}

void BrainFuck::FuckCore::run_current_code_from_begin() {
    code_ptr=current_code.cbegin();
    while(next_command()) {
    }
}

void BrainFuck::FuckCore::jump_to_line_end() {
    while(code_ptr!=current_code.end()) {
        if(*code_ptr=='\r'&&code_ptr+1!=current_code.end()&&*(code_ptr+1)=='\n') {
            code_ptr=code_ptr+1;
            return;
        }
        else if(*code_ptr=='\n') {
            return;
        }
        ++code_ptr;
    }
}
