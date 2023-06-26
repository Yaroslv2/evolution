#ifndef WINDOW_H
#define WINDOW_H

#include "window_state.h"

#include "loading_app_page.h"
#include "menu_page.h"
#include "settings_page.h"
#include "evolution.h"
#include "info_page.h"

class Window
{
public:
    Window();
    void start();
    ~Window();

private:
    float width;
    float height;
    LoadingAppPage *loadingAppPage;
    MenuPage *menuPage;
    SettingsPage *settingsPage;
    EvolutionPage *evolutionPage;
    InfoPage *infoPage;
    sf::RenderWindow *window;
    WindowState *state;
    sf::Font *font;

    sf::Color *botsColor;
};

#endif