#include <SFML/Graphics.hpp>
#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "Config.hpp"
#include "AnimSprite.hpp"
#include "ScreenManager.hpp"
#include "TestScreen.hpp"

int main()
{
	gui::ScreenManager screenM;

    screenM.loadScreen<gui::TestScreen>();

    return screenM.mainLoop();
}
