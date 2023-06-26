#ifndef WINDOW_STATE_H
#define WINDOW_STATE_H

class WindowState
{
public:
    enum class State
    {
        LOADING_APP,
        MENU,
        EVOLUTION,
        SETTINGS,
        INFO,
        CLOSE,
    };
    WindowState();
    void setState(WindowState::State);
    WindowState::State getState();
    ~WindowState();

private:
    State state;
};

#endif