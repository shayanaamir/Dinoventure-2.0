#pragma once

struct Animation
{
    int index;
    int frames;
    int speed; //for our animation
    Animation(){}
    Animation(int i, int f, int s)  //setter fn
    {
        index = i;
        frames = f;
        speed = s;
    }
};