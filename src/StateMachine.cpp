/*
Copyright (c) 2017 InversePalindrome
Spacelapse - StateMachine.cpp
InversePalindrome.com
*/


#include "StateMachine.hpp"


StateMachine::StateMachine(State::Data data) :
	data(data),
	states(),
	pendingActions(),
	stateHolder()
{
}

void StateMachine::handleEvent(const sf::Event& event)
{
	if (this->hasStates())
	{
		this->states.back()->handleEvent(event);
	}

	this->applyPendingActions();
}

void StateMachine::update(sf::Time deltaTime)
{
	if (this->hasStates())
	{
		this->states.back()->update(deltaTime);
	}

	this->applyPendingActions();
}

void StateMachine::draw()
{
	if (this->hasStates())
	{
		this->states.back()->draw();
	}
}

void StateMachine::push(StateID stateID)
{
	this->pendingActions.push_back(PendingAction(Action::Push, stateID));
}

void StateMachine::pop()
{
	this->pendingActions.push_back(PendingAction(Action::Pop, StateID::UndefinedState));
}

void StateMachine::clear()
{
	this->pendingActions.push_back(PendingAction(Action::Clear, StateID::UndefinedState));
}

bool StateMachine::hasStates() const
{
	return !this->states.empty();
}

StateMachine::PendingAction::PendingAction(Action action, StateID stateID) :
	action(action),
	stateID(stateID)
{
}

std::unique_ptr<State> StateMachine::selectState(StateID stateID)
{
	return this->stateHolder.find(stateID)->second();
}

void StateMachine::applyPendingActions()
{
	for (const auto& pendingAction : this->pendingActions)
	{
		switch (pendingAction.action)
		{
		case Action::Push:
			this->states.push_back(this->selectState(pendingAction.stateID));
			break;
		case Action::Pop:
			this->states.pop_back();
			break;
		case Action::Clear:
			this->states.clear();
			break;
		}
	}

	this->pendingActions.clear();
}