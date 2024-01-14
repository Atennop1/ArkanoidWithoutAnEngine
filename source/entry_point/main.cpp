#include "application/application.h"

int main(int argc, char *argv[])
{
    auto application = new Application();
    application->Activate();

    free(application);
    return 0;
}
