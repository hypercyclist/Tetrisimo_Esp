#include "../Game.h"

// Project start file.
int main()
{
    std::shared_ptr<Game> tetrisimoEsp = std::make_shared<Game>();
    tetrisimoEsp->start();
}