#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;

class MidpointCircle {
private:
    int centerX, centerY, radius;
    SDL_Renderer* renderer;

public:
    MidpointCircle(SDL_Renderer* ren, int x, int y, int r)
        : renderer(ren), centerX(x), centerY(y), radius(r) {}

    void drawCircle() {
        int x = 0;
        int y = radius;
        int p = 1 - radius; 

        // Draw the initial octant points
        drawCirclePoints(x, y);

        while (x < y) {
            x++;
            if (p < 0) {
                p += 2 * x + 1;
            } else {
                y--;
                p += 2 * (x - y) + 1;
            }
            drawCirclePoints(x, y);
        }
    }

private:
    void drawCirclePixel(int x, int y) {

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, x, y);
        SDL_RenderDrawPoint(renderer, x+1, y);
        SDL_RenderDrawPoint(renderer, x, y+1);
        SDL_RenderDrawPoint(renderer, x+1, y+1);
    }

    void drawCirclePoints(int x, int y) {
        // Draw pixels in all 8 octants
        drawCirclePixel(centerX + x, centerY + y);
        drawCirclePixel(centerX - x, centerY + y);
        drawCirclePixel(centerX + x, centerY - y);
        drawCirclePixel(centerX - x, centerY - y);
        drawCirclePixel(centerX + y, centerY + x);
        drawCirclePixel(centerX - y, centerY + x);
        drawCirclePixel(centerX + y, centerY - x);
        drawCirclePixel(centerX - y, centerY - x);
    }
};

void drawGridDots(SDL_Renderer* renderer, int width, int height, int spacing) {
    // Set the color for grid dots (dim gray)
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    
    // Draw the grid dots
    for (int x = 0; x < width; x += spacing) {
        for (int y = 0; y < height; y += spacing) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

int main(int argc, char* argv[]) {
    // Window dimensions
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int DOT_SPACING = 20; 
    
    int centerX, centerY, radius;
    
    cout << "Enter center coordinates (x y): \n";
    cout << "Enter center x: ";
    cin >> centerX;
    cout << "Enter center y: ";
    cin >> centerY;
    cout << "Enter radius: ";
    cin >> radius;
    
    // Scale coordinates to match grid spacing
    centerX = centerX * DOT_SPACING;
    centerY = centerY * DOT_SPACING;
    radius = radius * DOT_SPACING;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }
    
    // Create window
    SDL_Window* window = SDL_CreateWindow("Midpoint Circle Algorithm with Grid",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        
    if (window == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }
    
    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }
    
    bool quit = false;
    SDL_Event e;
    
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Draw grid dots
        drawGridDots(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, DOT_SPACING);
        
        // Draw circle
        MidpointCircle circle(renderer, centerX, centerY, radius);
        circle.drawCircle();
        
        // Present renderer
        SDL_RenderPresent(renderer);
        
        // Add a small delay
        SDL_Delay(16); // ~60fps
    }
    
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}