#include "application/application.hpp"

int main(int argc, char *argv[])
{
    auto application = arkanoid::Application();
    application.Activate();
    return 0;
}
