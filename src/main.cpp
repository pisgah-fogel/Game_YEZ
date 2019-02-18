#include <SFML/Graphics.hpp>
#include "RessourcesManager.hpp"
#include "Log.hpp"
#include "Config.hpp"
#include "AnimSprite.hpp"
#include "ScreenManager.hpp"

int main()
{
	gui::ScreenManager screenM;

    return screenM.mainLoop();
}
