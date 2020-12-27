#pragma once
extern const char *registers[4];

struct ValPtr;

void storeReg(int i);
void freeReg(int i);

void getReg(int i, ValPtr *_Who);

int getReg(ValPtr *_Who);


int nextlable();

void holdReg(int i);

void unholdReg(int i);