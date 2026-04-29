#ifndef BAD_INPUT_H
#define BAD_INPUT_H

#include <cstring>
#include <exception>

class bad_input : public std::exception {
public:
    explicit bad_input(const char* in_message) : message(nullptr) {
        if (in_message != nullptr) {
            message = new char[std::strlen(in_message) + 1];
            std::strcpy(message, in_message);
        }
    }

    bad_input(const bad_input& other) : message(nullptr) {
        if (other.message != nullptr) {
            message = new char[std::strlen(other.message) + 1];
            std::strcpy(message, other.message);
        }
    }

    bad_input& operator=(const bad_input& other) {
        if (this != &other) {
            delete[] message;
            message = nullptr;
            if (other.message != nullptr) {
                message = new char[std::strlen(other.message) + 1];
                std::strcpy(message, other.message);
            }
        }
        return *this;
    }

    ~bad_input() noexcept override {
        delete[] message;
    }

    const char* what() const noexcept override {
        return message != nullptr ? message : "bad input";
    }

private:
    char* message;
};

#endif // BAD_INPUT_H
