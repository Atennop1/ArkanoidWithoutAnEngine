#include <SDL.h>
#include <vector>

const int kWindowWidth = 1920;
const int kWindowHeight = 1080;

//----------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(kWindowWidth, kWindowHeight, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    std::vector<SDL_Point> vector;

    for (int _ = 0; _ < 300; _++)
        vector.push_back({ rand() % kWindowWidth, rand() % kWindowHeight });

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoints(renderer, vector.data(), static_cast<int>(vector.size()));

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    return 0;
}

//----------------------------------------------------------------------------------------------------
