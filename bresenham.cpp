#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;

class BRESENHAM {
private:
    int x, y, dx, dy, X1, Y1;
    int pk;
    SDL_Renderer* renderer;

public:
    BRESENHAM(SDL_Renderer* ren, int x0, int y0, int x1, int y1)
        : renderer(ren), x(x0), y(y0), X1(x1), Y1(y1)
    {
        dx = abs(x1 - x0);
        dy = abs(y1 - y0);
        pk = 2 * dy - dx;
    }
    
    void drawBRESENHAMLine() {
        int stepX = (X1 > x) ? 1 : -1;
        int stepY = (Y1 > y) ? 1 : -1;
        
        bool steep = dy > dx;
        if (steep) {
            swap(x, y);
            swap(X1, Y1);
            swap(dx, dy);
            swap(stepX, stepY);
        }
        
        int currentX = x;
        int currentY = y;
        
        for (int i = 0; i <= dx; ++i) {
            if (steep) {
                drawLinePixel(currentY, currentX);
            } else {
                drawLinePixel(currentX, currentY);
            }
            
            if (pk < 0) {
                pk += 2 * dy;
            } else {
                currentY += stepY;
                pk += 2 * (dy - dx);
            }
            currentX += stepX;
        }
    }

private:
    void drawLinePixel(int x, int y) {
        // Draw asterisks for the line (white color, double asterisk)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, x, y);
        SDL_RenderDrawPoint(renderer, x+1, y);
        SDL_RenderDrawPoint(renderer, x, y+1);
        SDL_RenderDrawPoint(renderer, x+1, y+1);
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
    const int DOT_SPACING = 20; // Space between dots
    
    int x0, y0, x1, y1;
    
    cout << "Enter starting coordinates (x0 y0): ";
    cout << "\nEnter x0: ";
    cin >> x0;
    cout << "Enter y0: ";
    cin >> y0;
    cout << "Enter ending coordinates (x1 y1): ";
    cout << "\nEnter x1: ";
    cin >> x1;
    cout << "Enter y1: ";
    cin >> y1;
    
    // Scale coordinates to match grid spacing
    x0 = x0 * DOT_SPACING;
    y0 = y0 * DOT_SPACING;
    x1 = x1 * DOT_SPACING;
    y1 = y1 * DOT_SPACING;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }
    
    // Create window
    SDL_Window* window = SDL_CreateWindow("Bresenham Line Drawing with Grid",
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
        
        // Draw line
        BRESENHAM line(renderer, x0, y0, x1, y1);
        line.drawBRESENHAMLine();
        
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