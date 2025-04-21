#pragma once
#include "common.h"
#include "list.h"	
#include "user.h"
#include "log.h"
#include "package.h"
#include "fore.h"
#include "lineseries.h"

void Mainpart(int year, int month, int day);

void drawAsciiChart(const double x[], const double y[], const double yPred[], int n);

void linearRegression(const double x[], const double y[], int n, double* a, double* b);

bool inputDateSafe(time_t* result, int year, int month, int day);

bool validateDate(int year, int month, int day);

void countPendingPackages(ListNode* head, time_t startDate, double* counts);

void WeeklyBriefly();

double calculateSumOfSquareResiduals(double estimatedValues[], double actualValues[], int count);

void linearRegression(const double x[], const double y[], int n, double* a, double* b);

void drawPart(double* values, double* estimated, int year, int month, int day);

void futuredata(int year, int month, int day);
