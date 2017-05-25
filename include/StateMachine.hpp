/*
Copyright (c) 2017 InversePalindrome
Spacelapse - StateMachine.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFML/Window/Event.hpp>

#include <map>
#include <vector>
#include <memory>
#include <functional>


class StateMachine
{
public:
	enum class StateID { UndefinedState, SplashState, MenuState, PlayState, SpaceshipSelectionState, HighScoreState, PauseState, GameOverState };
	enum class Action { UndefinedAction, Push, Pop, Clear };

	StateMachine(State::Data data);

	void handleEvent(const sf::Event& event);
	void update(sf::Time deltaTime);
	void draw();

	template<typename T>
	void registerState(StateID stateID);

	void push(StateID stateID);
	void pop();
	void clear();

	bool hasStates() const;

private:
	struct PendingAction
	{
		PendingAction(Action action, StateID stateID);

		Action action;
		StateID stateID;
	};

	State::Data data;

	std::vector<std::unique_ptr<State>> states;
	std::vector<PendingAction> pendingActions;
	std::map<StateID, std::function<std::unique_ptr<State>()>> stateHolder;

	std::unique_ptr<State> selectState(StateID stateID);
	void applyPendingActions();
};


template<typename T>
void StateMachine::registerState(StateID stateID)
{
	this->stateHolder[stateID] = [&]() { return std::make_unique<T>(*this, data); };
}