#pragma once

struct Tree {
    float x, y, z;
    float scale;
    float rotationY;
    int type;
    float colorOffset;
};

// Generates the tree coordinates and heights once at startup
void initForest();

// Draws the entire array of trees
void drawForest();