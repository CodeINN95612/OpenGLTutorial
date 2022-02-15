#include "Game.hpp"

int main(int argc, char** argv)
{
	try
	{
		Game game;
		game.Run();
	}
	catch (GL::Excepcion& e)
	{
		e.Log();
		exit(2);
	}

	return 0;
}