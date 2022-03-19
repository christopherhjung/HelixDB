//
// Created by Christopher Jung on 19.03.22.
//

#pragma once
#include <string>
#include <iostream>

class Exception : public std::runtime_error {
public:
    explicit Exception(const std::string &message) : std::runtime_error(message){
        std::string exception_message = "Message :: " + message + "\n";
        std::cerr << exception_message;
    }

    explicit Exception(const std::string &&message) : std::runtime_error(std::forward<const std::string&&>(message)){
        std::string exception_message = "Message :: " + message + "\n";
        std::cerr << exception_message;
    }
};
