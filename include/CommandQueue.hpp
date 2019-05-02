/*
Copyright (c) 2017 InversePalindrome
Spacelapse - CommandQueue.hpp
InversePalindrome.com
*/


#pragma once

#include "Command.hpp"

#include <queue>


class CommandQueue
{
public:
    void push(const Command& command);
    Command pop();

    bool hasCommands() const;

private:
    std::queue<Command> commands;
};
