// dllmain.cpp : Определяет точку входа для приложения DLL.

#define _USE_MATH_DEFINES
#include "pch.h"
#include "dllmain.h"
#include <math.h>
#include <iostream>
#include <cstdarg>


using namespace std;


extern "C" __declspec(dllexport) const char* FName()
{
    return "f24";
}

double Safonov_arcth(double x, double tb_epsilon) {
    int n = 1;
    long double result = x, last = result, curr = result * (-9) * x * x / 2;
    do
    {
        result += curr;
        n++;
        last = curr;
        curr *= -9 * x * x / ((2*n) * (2*n-1));
    } while ((fabs(fabs(curr) - fabs(last))) >= tb_epsilon);
    return result;
}

double myf_3530902_20001(double x, double tb_epsilon, double a) {
    return Safonov_arcth(x, tb_epsilon);
}

double myf_math(double x, double a) {
    return x * cos(3*x);
}



extern "C" __declspec(dllexport) void calculator(SafonovInfoType infoTable, void* output_line_Safonov(SafonovInfoType infoTable, ColorSaf My_color, ...), ...) {
    if (infoTable == Table1Saf) {
        va_list argumentsForFunction;
        va_start(argumentsForFunction, output_line_Safonov);
        double x_start = va_arg(argumentsForFunction, double);
        double x_end = va_arg(argumentsForFunction, double);
        double x_del = va_arg(argumentsForFunction, double);
        double tb_epsilon = va_arg(argumentsForFunction, double);
        double a = va_arg(argumentsForFunction, double);
        va_end(argumentsForFunction);
        table1_processing(infoTable, output_line_Safonov, x_start, x_end, x_del, tb_epsilon, a);
    }
    else if (infoTable == Table2Saf) {
        va_list arguments;
        va_start(arguments, output_line_Safonov);
        double x_ideal = va_arg(arguments, double);
        double a = va_arg(arguments, double);
        va_end(arguments);
        table2_processing(infoTable, output_line_Safonov, x_ideal, a);
    }
}


void table1_processing(SafonovInfoType infoTable, void* output_line_Safonov(SafonovInfoType infoTable, ColorSaf My_color, ...), ...) {
    va_list argumentsForFunction;
    va_start(argumentsForFunction, output_line_Safonov);
    double x_start = va_arg(argumentsForFunction, double);
    double x_end = va_arg(argumentsForFunction, double);
    double x_del = va_arg(argumentsForFunction, double);
    double tb_epsilon = va_arg(argumentsForFunction, double);
    double a = va_arg(argumentsForFunction, double);
    va_end(argumentsForFunction);

    double f_row, f_math, delta;
    int LineCount = 1;

    for (double x = x_start; (x_start < x_end ? x < x_end : x > x_end) && !IsEqual(x_start, x_end); x += x_del) {
        if (fabs(x - x_end) >= numeric_limits<double>::epsilon()) {
            x = double_round(x);
            f_row = myf_3530902_20001(x, tb_epsilon, a);
            f_math = myf_math(x, a);
            delta = sqrt(abs(f_row * f_row - f_math * f_math));
            if (isnan(delta) || isinf(delta) || (abs(x) > 10)) {
                output_line_Safonov(ErrorSaf, color, ++LineCount, x);
            }
            else {
                output_line_Safonov(infoTable, color, ++LineCount, x, f_row, f_math, delta);
            }
        }
    }
    f_row = myf_3530902_20001(x_end, tb_epsilon, a);
    f_math = myf_math(x_end, a);
    delta = sqrt(abs(f_row * f_row - f_math * f_math));
    if (isnan(delta) || isinf(delta) || (abs(x_end) > 10)) {
        output_line_Safonov(ErrorSaf, color, LineCount++, x_end);
    }
    else {
        output_line_Safonov(infoTable, color, LineCount++, x_end, f_row, f_math, delta);
    }
}

void table2_processing(SafonovInfoType infoTable, void* output_line_Safonov(SafonovInfoType infoTable, ColorSaf My_color, ...), ...) {
    va_list arguments;
    va_start(arguments, output_line_Safonov);
    double x_ideal = va_arg(arguments, double);
    double a = va_arg(arguments, double);
    va_end(arguments);
    double f_row, delta;
    double f_math = myf_math(x_ideal, a);
    int LineCount = 1;
    for (double tb_epsilon = 0.1; tb_epsilon >= 0.0000001; tb_epsilon /= 10) {
        f_row = myf_3530902_20001(x_ideal, tb_epsilon, a);
        delta = sqrt(abs(f_row * f_row - f_math * f_math));
        if (!isnan(delta) && !isinf(delta) && (abs(x_ideal) < 10)) {
            output_line_Safonov(infoTable, color, ++LineCount, tb_epsilon, f_row, f_math, delta);
        }
        else {
            output_line_Safonov(ErrorSaf, color, ++LineCount, tb_epsilon);
        }
    }
}

bool IsEqual(double lhs, double rhs) {
    return fabs(lhs - rhs) < numeric_limits<double>::epsilon();
}

double double_round(double x) {
    return (double)round(10000000 * x) / 10000000;
}

//
//extern "C" __declspec(dllexport) const char* FName()
//{
//    return "f24";
//}
//
//double Safonov_arcth(double x, double tb_epsilon) {
//    int n = 1;
//    long double result = x, last = result, curr = result * (-9) * x * x / 2;
//    do
//    {
//        result += curr;
//        n++;
//        last = curr;
//        curr *= -9 * x * x / ((2*n) * (2*n-1));
//    } while ((fabs(fabs(curr) - fabs(last))) >= tb_epsilon);
//    return result;
//}
//
//double myf_3530902_20001(double x, double tb_epsilon, double a) {
//    return Safonov_arcth(x, tb_epsilon);
//}
//
//double myf_math(double x, double a) {
//    return x * cos(3*x);
//}
//
//
//
//extern "C" __declspec(dllexport) void calculator(SafonovInfoType infoTable, void* output_line_Safonov(SafonovInfoType infoTable, ColorSaf My_color, ...), ...) {
//    if (infoTable == Table1Saf) {
//        va_list argumentsForFunction;
//        va_start(argumentsForFunction, output_line_Safonov);
//        double x_start = va_arg(argumentsForFunction, double);
//        double x_end = va_arg(argumentsForFunction, double);
//        double x_del = va_arg(argumentsForFunction, double);
//        double tb_epsilon = va_arg(argumentsForFunction, double);
//        double a = va_arg(argumentsForFunction, double);
//        va_end(argumentsForFunction);
//        table1_processing(infoTable, output_line_Safonov, x_start, x_end, x_del, tb_epsilon, a);
//    }
//    else if (infoTable == Table2Saf) {
//        va_list arguments;
//        va_start(arguments, output_line_Safonov);
//        double x_ideal = va_arg(arguments, double);
//        double a = va_arg(arguments, double);
//        va_end(arguments);
//        table2_processing(infoTable, output_line_Safonov, x_ideal, a);
//    }
//}
//
//
//void table1_processing(SafonovInfoType infoTable, void* output_line_Safonov(SafonovInfoType infoTable, ColorSaf My_color, ...), ...) {
//    va_list argumentsForFunction;
//    va_start(argumentsForFunction, output_line_Safonov);
//    double x_start = va_arg(argumentsForFunction, double);
//    double x_end = va_arg(argumentsForFunction, double);
//    double x_del = va_arg(argumentsForFunction, double);
//    double tb_epsilon = va_arg(argumentsForFunction, double);
//    double a = va_arg(argumentsForFunction, double);
//    va_end(argumentsForFunction);
//
//    double f_row, f_math, delta;
//    int LineCount = 1;
//
//    for (double x = x_start; (x_start < x_end ? x < x_end : x > x_end) && !IsEqual(x_start, x_end); x += x_del) {
//        if (fabs(x - x_end) >= numeric_limits<double>::epsilon()) {
//            x = double_round(x);
//            f_row = myf_3530902_20001(x, tb_epsilon, a);
//            f_math = myf_math(x, a);
//            delta = sqrt(abs(f_row * f_row - f_math * f_math));
//            if (isnan(delta) || isinf(delta)) {
//                output_line_Safonov(ErrorSaf, color, ++LineCount, x);
//            }
//            else {
//                output_line_Safonov(infoTable, color, ++LineCount, x, f_row, f_math, delta);
//            }
//        }
//    }
//    f_row = myf_3530902_20001(x_end, tb_epsilon, a);
//    f_math = myf_math(x_end, a);
//    delta = sqrt(abs(f_row * f_row - f_math * f_math));
//    if (isnan(delta) || isinf(delta)) {
//        output_line_Safonov(ErrorSaf, color, LineCount++, x_end);
//    }
//    else {
//        output_line_Safonov(infoTable, color, LineCount++, x_end, f_row, f_math, delta);
//    }
//}
//
//void table2_processing(SafonovInfoType infoTable, void* output_line_Safonov(SafonovInfoType infoTable, ColorSaf My_color, ...), ...) {
//    va_list arguments;
//    va_start(arguments, output_line_Safonov);
//    double x_ideal = va_arg(arguments, double);
//    double a = va_arg(arguments, double);
//    va_end(arguments);
//    double f_row, delta;
//    double f_math = myf_math(x_ideal, a);
//    int LineCount = 1;
//    for (double tb_epsilon = 0.1; tb_epsilon >= 0.0000001; tb_epsilon /= 10) {
//        f_row = myf_3530902_20001(x_ideal, tb_epsilon, a);
//        delta = sqrt(abs(f_row * f_row - f_math * f_math));
//        if (!isnan(delta) && !isinf(delta)) {
//            output_line_Safonov(infoTable, color, ++LineCount, tb_epsilon, f_row, f_math, delta);
//        }
//        else {
//            output_line_Safonov(ErrorSaf, color, ++LineCount, tb_epsilon);
//        }
//    }
//}
//
//bool IsEqual(double lhs, double rhs) {
//    return fabs(lhs - rhs) < numeric_limits<double>::epsilon();
//}
//
//double double_round(double x) {
//    return (double)round(10000000 * x) / 10000000;
//}
//
//

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

