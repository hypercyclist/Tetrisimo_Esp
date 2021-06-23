#include "Game.h"

// Project start file.
void setup()
{
    std::shared_ptr<Game> tetrisimoEsp = std::make_shared<Game>();
    tetrisimoEsp->start();
}

void loop()
{
}