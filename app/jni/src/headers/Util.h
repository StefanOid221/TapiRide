#ifndef UTIL_H
#define UTIL_H
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void createObstacle();

void savePointsRecord(int points);

int retrievePointsRecord();

void createFile();

#endif