#include "mainMenuState.h"

MainMenu::MainMenu(std::shared_ptr<RenderWindow> wind, std::stack<std::shared_ptr<State>> s) : State(wind, s) {

}

MainMenu::~MainMenu() {
}