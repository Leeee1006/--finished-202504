#include "common.h"

// @brief ����ͼ����ͼ
// @return ��λ��ֵ
int drawChartView( double values[], int count, int originX, int originY, int totalWidth, int totalHeight, int unitWidth, int unitHeight, LPCTSTR labelX, LPCTSTR labelY, LPCTSTR title);

// ��������
void drawLineSeries(double values[], int unitValue, int count, int originX, int originY, int unitWidth, int unitHeight, COLORREF color);

// ��������
void drawSplineSeries(double values[], int unitValue, int count, int originX, int originY, int unitWidth, int unitHeight, COLORREF color);
