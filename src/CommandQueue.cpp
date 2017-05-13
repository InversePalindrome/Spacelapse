/*
Copyright (c) 2017 InversePalindrome
Spacelapse - CommandQueue.cpp
InversePalindrome.com
*/


#include "CommandQueue.hpp"


void CommandQueue::push(const Command& command)
{
	this->commands.push(command);
}

Command CommandQueue::pop()
{
	auto command = this->commands.front();

	this->commands.pop();

	return command;
}

bool CommandQueue::hasCommands() const
{
	return !this->commands.empty();
}