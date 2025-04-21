#include "common.h"

// @brief 绘制图表视图
// @return 单位纵值
int drawChartView( double values[], int count, int originX, int originY, int totalWidth, int totalHeight, int unitWidth, int unitHeight, LPCTSTR labelX, LPCTSTR labelY, LPCTSTR title);

// 绘制折线
void drawLineSeries(double values[], int unitValue, int count, int originX, int originY, int unitWidth, int unitHeight, COLORREF color);

// 绘制曲线
void drawSplineSeries(double values[], int unitValue, int count, int originX, int originY, int unitWidth, int unitHeight, COLORREF color);
