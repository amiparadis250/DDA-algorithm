#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;

class DDA {
private:
    float x, y, xIncrement, yIncrement;
    int steps;
    SDL_Renderer* renderer;

public:
    DDA(SDL_Renderer* ren, int x0, int y0, int x1, int y1)
        : renderer(ren), x(x0), y(y0)
    {
        int dx = x1 - x0;
        int dy = y1 - y0;
        steps = max(abs(dx), abs(dy));
        xIncrement = dx / static_cast<float>(steps);
        yIncrement = dy / static_cast<float>(steps);
    }

    void draw() {
        // Set line color to bright white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        for (int i = 0; i <= steps; ++i) {
            // Draw larger asterisk-like dots for the line
            SDL_Rect point = {static_cast<int>(round(x)) - 2, static_cast<int>(round(y)) - 2, 5, 5};
            SDL_RenderFillRect(renderer, &point);
            
            x += xIncrement;
            y += yIncrement;
        }
    }
};

void drawGrid(SDL_Renderer* renderer, int spacing) {
    // Set grid color to a more visible gray
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    
    // Draw the grid of dots with larger dots
    for (int x = spacing; x < 800; x += spacing) {
        for (int y = spacing; y < 600; y += spacing) {
            // Draw a small dot instead of a single pixel
            SDL_Rect dot = {x - 1, y - 1, 2, 2};
            SDL_RenderFillRect(renderer, &dot);
        }
    }
}

int main() {
    int x0, y0, x1, y1;
    cout << "Enter starting coordinates (x0 y0): ";
    cout << "\nEnter x0:";
    cin >> x0;
    cout << "\nEnter y0:";
    cin >> y0;
    cout << "\nEnter ending coordinates (x1 y1): ";
    cout << "\nEnter x1:";
    cin >> x1;
    cout << "\nEnter y1:";
    cin >> y1;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("DDA Line Drawing with Grid", 
                                         SDL_WINDOWPOS_UNDEFINED, 
                                         SDL_WINDOWPOS_UNDEFINED, 
                                         800, 600, 
                                         SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    // Main loop
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen with a very dark blue for better contrast
        SDL_SetRenderDrawColor(renderer, 0, 0, 20, 255);
        SDL_RenderClear(renderer);

        // Draw the grid
        drawGrid(renderer, 20);  // 20 pixels spacing between dots

        // Draw line using DDA
        DDA dda(renderer, x0, y0, x1, y1);
        dda.draw();

        // Update screen
        SDL_RenderPresent(renderer);

        // Cap to 60 FPS
        SDL_Delay(1000/60);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}