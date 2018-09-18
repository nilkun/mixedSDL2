
#include "../headers/Perlin.h"
#include "../headers/Constants.h"
#include <iostream>
#include <vector>

int Perlin::octave;
float Perlin::scale;

Perlin::Perlin()
{
    nArraySize = SCREEN_WIDTH;
    initialNoise = new float[nArraySize];
    finalOutput = new float[nArraySize];
    octave = 8;
    scale = 2.0f;
    initializeArray1d();
    Perlin1D(scale, nArraySize, initialNoise, octave, finalOutput);

    nArraySizeX = SCREEN_WIDTH;
    nArraySizeY = SCREEN_HEIGHT;
    //2d
    try
    {
        initialNoise2d = new float[nArraySizeX * nArraySizeY];
    } catch(const std::bad_array_new_length &e) { std::cout << e.what() << " in initialNoise2d" << std::endl; }
    try
    {
        finalOutput2d = new float[nArraySizeX * nArraySizeY];
    } catch(const std::bad_array_new_length &e) { std::cout << e.what() << " in outputNoise2d" << std::endl; }

    initializeArray2d();
    // initialNoise2d[1] = 0.5f; // Set sea level
    seaLevel = 0.5f;
}

void Perlin::initializeArray1d()
{
    // new randomizer 
    nextNumber.seed(SDL_GetTicks());
    for(int i = 0; i < nArraySize; i++)
     initialNoise[i] = randomNumbers(nextNumber);
}

void Perlin::initializeArray2d() 
{
    nextNumber.seed(SDL_GetTicks());
    for(int i = 0; i < nArraySizeX * nArraySizeY; i++)
    {
        // if (i<nArraySizeX) initialNoise2d[i] = seaLevel;
        // else 
        initialNoise2d[i] = randomNumbers(nextNumber);
    } 
}

void Perlin::render1d(SDL_Renderer* renderer)
{
    Perlin1D(scale, nArraySize, initialNoise, octave, finalOutput);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    for(int i = 0; i < nArraySize; i++)
    {
        for(int j = SCREEN_HEIGHT / 2; j >= (float)(finalOutput[i] * SCREEN_HEIGHT / 2); j--)
        {
            SDL_RenderDrawPoint(renderer, i, j); 
        }
    }
}
void Perlin::render2d(SDL_Renderer* renderer)
{
    Perlin2D(scale, nArraySizeX, nArraySizeY, initialNoise2d, octave, finalOutput2d);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    for(int x = 0; x < nArraySizeX; x++)
    {
        for(int y = 0; y < nArraySizeY; y++)
        {
            double number = finalOutput2d[x + y * nArraySizeX];
            std::cout << "Setting color..." << number << std::endl;
            if(number >= average) 
            {
                int color = (float)(64 + 192 * (number - average)/(1-average));
                SDL_SetRenderDrawColor(renderer, 0, color, 0, 0);
            }
            else if(number < average)
            {
                int color = (float)(256 * number / average);
                SDL_SetRenderDrawColor(renderer, 0, 0, color, 0);
            }

            std::cout << "at x: " << x << " y: " << y << std::endl;
            SDL_RenderDrawPoint(renderer, x, y); 
        }
    }
}

void Perlin::Perlin1D(float scale, int nCount, float *fSeed, int nOctaves, float *fOutput)
{ // size of array, initial array, octaves, output
    for (int x = 0; x < nCount; x++)
    {
        float fNoise = 0.0f;        
        float fScaleAcc = 0.0f;
        float fScale = 1.0f;

        for (int o = 0; o < nOctaves; o++)
        {
            int nPitch = nCount >> o;
            int nSample1 = (x / nPitch) * nPitch;
            int nSample2 = (nSample1 + nPitch) % nCount;

            float fBlend = (float)(x - nSample1) / (float)nPitch;
            float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];
            fNoise += fSample * fScale;
            fScaleAcc += fScale;

            fScale = fScale / scale;
        }

        // Scale to seed range
        fOutput[x] = fNoise / fScaleAcc;
    }
}

void Perlin::Perlin2D(float scale, int nArraySizeX, int nArraySizeY, float *fSeed, int nOctaves, float *fOutput)
{ // size of array, initial array, octaves, output

    average = 0;
    for (int x = 0; x < nArraySizeX; x++)
    {
        for (int y = 0; y < nArraySizeY; y++)
        {
            float fNoise = 0.0f;        
            float fScaleAcc = 0.0f;
            float fScale = 1.0f;

            for (int o = 0; o < nOctaves; o++)
            {
                int nPitch = nArraySizeX >> o;

                int nSampleX1 = (x / nPitch) * nPitch;
                int nSampleY1 = (y / nPitch) * nPitch;

                int nSampleX2 = (nSampleX1 + nPitch) % nArraySizeX;
                int nSampleY2 = (nSampleY1 + nPitch) % nArraySizeX;

                float fBlendX = static_cast<float>(x - nSampleX1) / static_cast<float>(nPitch);
                float fBlendY = static_cast<float>(y - nSampleY1) / static_cast<float>(nPitch);
                
                float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nArraySizeX +nSampleX1] + fBlendX * fSeed[nSampleY1* nArraySizeX + nSampleX2];
                float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nArraySizeX +nSampleX1] + fBlendX * fSeed[nSampleY2* nArraySizeX + nSampleX2];
                fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
                fScaleAcc += fScale;

                fScale = fScale / scale;
            }

            // Scale to seed range
            fOutput[x + y * SCREEN_WIDTH] = fNoise / fScaleAcc;
            average += fOutput[x + y * SCREEN_WIDTH];
        }
    }
    average /= (nArraySizeX * nArraySizeY);
}