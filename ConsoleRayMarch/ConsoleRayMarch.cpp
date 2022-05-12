// ConsoleRayMarch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include "SDFObjects.h"
#include "Vec3.h"
#include "Math.h"
#include <tuple>
#include <string>
#include <chrono>
#include<thread>
#include <functional>
using namespace std;
using namespace std;
using namespace std;


#define PI 3.14159265

namespace GraphicsSettings
{
    static int columns, rows;
}

const char characters[12] = {
    ' ', '.', ',', '-', '~', ':',';','!', '*', '#', '$', '@'
};

int frame = 0;
using namespace std::chrono;
milliseconds start = duration_cast<milliseconds>(
    system_clock::now().time_since_epoch()
    );

float SceneSDF(Vec3 p)
{
    float d;

    //Vec3 spherePos(0.0, 0.0, 0.0);
    //d = sdfSphere(p, spherePos, 0.5);

    

    //intersection of cube and sphere
    float time = (float)(duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        ) - start).count() / 1000.0;
    /*
    Vec3 cubeBound(0.35, 0.35, 0.35);
    Vec3 cubeOffset(0, 0, 0);
    d = sdfCube(p, cubeBound, cubeOffset,time, time, time);  
    */

    d = sdfTorus(p, 0.45, 0.25, time, time/4, 0);
    return d;
}

float RayMarch(Vec3 r0, Vec3 rhat)
{
    float dx;
    dx = 0;
    for (int i = 0; i < 100; i++) {
        Vec3 ad = rhat;
        ad.ScalarMultiply(dx);
        float ds = SceneSDF(r0 + ad);
        dx += ds;
        if (dx > 100 || ds < 0.01) break;
    }
    return dx;
}

float PixelToScreenCoord(int pixelNum, int totalPixels) 
{
    return 2 * (float)(pixelNum - totalPixels / 2) / (float)totalPixels;
}

void ClearScreen(int numChars) 
{
    for (int i = 0; i < numChars; i++) {
        cout << "\b";
    }
}

// sX, sY are given from -1 to 1
std::tuple<Vec3, Vec3> RayFromScreenCoord(float sX, float sY)
{
    Vec3 center(0, 0, 0);
    Vec3 cPos(0, 0, -1);

    Vec3 cNorm = center - cPos;
    cNorm.Normalize();

    float scaleX = 3;
    float scaleY = 1.4;

    //todo make sX / sY tangent to norm i.e. support other camera rotations....
    Vec3 cOffset(0.5 * scaleX * sX, 0.5 * scaleY * sY, 0);
    

    return std::make_tuple(cPos + cOffset, cNorm);
}
//luminance is provided [0,1]
char CharacterFromLuminance(float luminance) {
    int index = max(min(floor(luminance * sizeof(characters)), sizeof(characters)-1),0);
    return characters[index];
}


void RenderScreen(int columns, int rows) {
    int len = (columns) * (rows);
    string out;
    out.resize(len);
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            float sX = PixelToScreenCoord(x, columns);
            float sY = PixelToScreenCoord(y, rows);
            tuple<Vec3, Vec3> ray = RayFromScreenCoord(sX, sY);
            float march = RayMarch(std::get<0>(ray), std::get<1>(ray));
            float lum = 1 / march;
            lum = lum / 2;
            char put = CharacterFromLuminance(lum);

            out[y * (columns) + x] = put;
        }
        
    }
    cout << out;
    frame++;
}

void GraphicsLoop() {
    using namespace GraphicsSettings;
    ClearScreen(columns * rows);
    RenderScreen(columns, rows);
}

void RunTimer(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]() {
        while (true)
        {
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
        }).detach();
}

int main()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    using namespace GraphicsSettings;
    
    columns = max(csbi.srWindow.Right - csbi.srWindow.Left + 1, 1);
    rows = max(csbi.srWindow.Bottom - csbi.srWindow.Top + 1, 1);
    bool test = false;
    if (test) {
        cout << columns << "c " << rows << "r";
        float sX = PixelToScreenCoord(7, 28);
        float sY = PixelToScreenCoord(30, 120);
        cout << sX << " " << sY << "\n";
        tuple<Vec3, Vec3> ray = RayFromScreenCoord(sX, sY);
        Vec3 orig = std::get<0>(ray);
        Vec3 dir = std::get<1>(ray);
        cout << orig.x << "," << orig.y << "," <<orig.z<<"\n";
        cout << dir.x << "," << dir.y << "," << dir.z<<"\n";
        float march = RayMarch(orig, dir);
        cout << march << "\n";
        float lum = 1 / march;
        lum = lum / 2;
        cout << lum << "\n";
        cout << CharacterFromLuminance(lum);

    }

    float dt = 1000 / 20;
    RunTimer(GraphicsLoop, round(dt));
 
    while (true);
    /*while (!test) {
        ClearScreen(columns * rows);
        RenderScreen(columns, rows);
    }*/
}

