#include "../headers/window_state.h"

WindowState::WindowState() : state(WindowState::State::LOADING_APP) {}

WindowState::~WindowState() {}

void WindowState::setState(WindowState::State newState)
{
    state = newState;
}

WindowState::State WindowState::getState()
{
    return state;
}