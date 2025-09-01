

#include "Game.h"
#include <GLFW/glfw3.h>

float getDeltaTime()
{
    static float lastTime = static_cast<float>(glfwGetTime());
    float currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime;
}



int main()
{
    Game game = Game();
    if (game.Start() != 0) { return -1; }

    while (!glfwWindowShouldClose(game.GetWindow()))
    {
        float deltaTime = getDeltaTime();
		game.Run(deltaTime);
    }

	game.Cleanup();

    return 0;
}