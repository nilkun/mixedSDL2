#ifndef PERLIN_H_
#define PERLIN_H_
// #include <vector>
#include <SDL2/SDL.h>
#include <random>

/* we need an array of size x, to store the initial random array, and then an array to store the results */

class Perlin 
{
    float *initialNoise = nullptr;
    float *finalOutput = nullptr;
    int nArraySize;

    std::mt19937 nextNumber;
    std::uniform_real_distribution<double> randomNumbers{0.0,1.0};
    
    // 2d
    int nArraySizeX;
    int nArraySizeY;
    
    float *finalOutput2d;
    float seaLevel;

public:

    float average;
    float *initialNoise2d;
    static int octave;
    static float scale;
    Perlin();
    void initializeArray1d();
    void initializeArray2d();
    void render1d(SDL_Renderer* renderer);
    void render2d(SDL_Renderer* renderer);
    void Perlin1D(float scale,
                int nCount, 
                float *fSeed, 
                int nOctaves, 
                float *fOutput);
    void Perlin2D(float scale,
                int nArraySizeX,
                int nArraySizeY, 
                float *fSeed, 
                int nOctaves, 
                float *fOutput);
};
#endif