#include "lineseries.h"

int drawChartView( double values[], int count, int originX, int originY, int totalWidth, int totalHeight, int unitWidth, int unitHeight, LPCTSTR labelX, LPCTSTR labelY, LPCTSTR title)
{
   setlinecolor(BLACK);
   settextcolor(BLACK);
   settextstyle(20,0,"consolas");
   // 绘制标题
   outtextxy(originX + totalWidth / 2 - 100, originY - totalHeight - 20, title);
   // 绘制坐标轴
   line(originX, originY, originX + totalWidth, originY);
   line(originX, originY, originX, originY - totalHeight);
   // 绘制箭头
   line(originX + totalWidth - 10, originY - 5, originX + totalWidth, originY);
   line(originX + totalWidth - 10, originY + 5, originX + totalWidth, originY);
   line(originX - 5, originY - totalHeight + 10, originX, originY - totalHeight);
   line(originX + 5, originY - totalHeight + 10, originX, originY - totalHeight);
   // 绘制坐标轴标签
   outtextxy(originX + totalWidth - 40, originY + 10, labelX);
   outtextxy(originX - 70, originY - totalHeight, labelY);
   // 计算数据最大值
   int maxValue = 1;
   for (int i = 0; i < count; i++)
   {
       if ((int)values[i] + 1 > maxValue)
       {
           maxValue = (int)values[i] + 1;
       }
   }
   // 计算单位纵值
   int unitValue = ((maxValue * unitHeight + totalHeight - 1) / totalHeight * 3 + 1) / 2;
   setlinecolor(LIGHTGRAY);
   // 绘制横向网格线
   for (int i = 0; i < count; i++)
   {
       int x = originX + (i + 1) * unitWidth;
       line(x, originY, x, originY - totalHeight);
   }
   // 绘制纵向网格线
   for (int i = 0; (i + 2) * unitHeight < totalHeight; i++)
   {
       int y = originY - (i + 1) * unitHeight;
       line(originX, y, originX + totalWidth, y);
   }
   setlinecolor(BLACK);
   // 绘制x轴刻度
   for (int i = 0; i < count; i++)
   {
       int x = originX + (i + 1) * unitWidth;
       line(x, originY, x, originY - 5);
       TCHAR str[10];
       _stprintf_s(str, _T("%2d"), i + 1);
       outtextxy(x - 12, originY + 10, str);
   }
   // 绘制y轴刻度
   for (int i = 0; (i + 2) * unitHeight < totalHeight; i++)
   {
       int y = originY - (i + 1) * unitHeight;
       line(originX, y, originX + 5, y);
	   TCHAR str[10];
	   _stprintf_s(str, _T("%6d"), (i + 1) * unitValue);
       outtextxy(originX - 60, y - 10, str); 
   }
   return unitValue;
}

void drawLineSeries(double values[], int unitValue, int count, int originX, int originY, int unitWidth, int unitHeight, COLORREF color)
{
	// 描点
	setfillcolor(color);
	for (int i = 0; i < count; i++)
	{
		int x = originX + (i + 1) * unitWidth;
		int y = (int)(originY - unitHeight * values[i] / unitValue);
		fillcircle(x, y, 4);
	}
	// 绘制折线
	setlinecolor(color);
	setlinestyle(PS_SOLID, 2);
	for (int i = 0; i < count - 1; i++)
	{
		int x1 = originX + (i + 1) * unitWidth;
		int y1 = (int)(originY - unitHeight * values[i] / unitValue);
		int x2 = originX + (i + 2) * unitWidth;
		int y2 = (int)(originY - unitHeight * values[i + 1] / unitValue);
		line(x1, y1, x2, y2);
	}
}

void drawSplineSeries(double values[], int unitValue, int count, int originX, int originY, int unitWidth, int unitHeight, COLORREF color)
{
	// 绘制曲线
	setlinecolor(color);
	setlinestyle(PS_SOLID,2);
	for (int i = 0; i < count - 1; i++)
	{
		int x1 = originX + (i + 1) * unitWidth;
		int y1 = (int)(originY - unitHeight * values[i] / unitValue);
		int x2 = originX + (i + 2) * unitWidth;
		int y2 = (int)(originY - unitHeight * values[i + 1] / unitValue);
		line(x1, y1, x2, y2);
	}
}

