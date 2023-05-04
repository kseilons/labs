#pragma once 

#include "pch.h"
enum SafonovInfoType {
    Table1Saf,
    Table2Saf,
    ErrorSaf
};

struct ColorSaf {
    int textSaf;
    int bgSaf;
};

ColorSaf color = { 12,3 };

typedef void(*FCallback)(SafonovInfoType type, ColorSaf c, ...);

extern "C" __declspec(dllexport) const char* FName();
extern "C" __declspec(dllexport) void calculator(SafonovInfoType, void*(SafonovInfoType infoTable, ColorSaf My_color, ...), ...);

void table1_processing(SafonovInfoType, void*(SafonovInfoType infoTable, ColorSaf My_color, ...), ...);
void table2_processing(SafonovInfoType, void*(SafonovInfoType infoTable, ColorSaf My_color, ...), ...);

double Safonov_arcth(double, double);
double myf_3530902_20001(double, double, double);
double myf_math(double, double);


bool IsEqual(double, double);
double double_round(double);