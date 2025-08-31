

#include "Game.h"

int main()
{
    Game game = Game();
	if (game.Start() != 0)

    while (!glfwWindowShouldClose(game.GetWindow()))
    {
		game.Run();
    }

	game.Cleanup();

    return 0;
}