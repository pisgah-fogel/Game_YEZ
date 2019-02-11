#include "Config.hpp"
#include "Log.hpp"

/*
 * Utilisez le fichier config.yez suivant:
 *
 * string a = /test/test
 * int b = 0b0110
 * int c = 0xdead
 * int d_test = 12349
 * float e = 89.65
 */


int main()
{
	LOG("Test %s",utils::Config::getInstance()->getString("a").c_str());
	LOG("Test %d",utils::Config::getInstance()->getInt("b"));
	LOG("Test %d",utils::Config::getInstance()->getInt("c"));
	LOG("Test %d",utils::Config::getInstance()->getInt("d_test"));
	LOG("Test %f",utils::Config::getInstance()->getFloat("e"));
	return 0;
}
