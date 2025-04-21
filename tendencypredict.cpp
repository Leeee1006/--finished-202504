#include"tendencypredict.h"

#define DAYS 14  /* 过去14天的历史数据 */
#define MAX_TRACKING_NUM 20
#define WIN_WIDTH 1000
#define WIN_HEIGHT 600
#define ORIGINX 100
#define ORIGINY 500
#define TOATALWIDTH 900
#define TOTALHEIGHT 480
#define UNITWIDTH 60
#define UNITHEIGHT 25

const int monthDays[2][15] =
{
	{0,31,28,31,30,31,30,31,31,30,31,30,31,31,28}, // 跨年处理
	{0,31,29,31,30,31,30,31,31,30,31,30,31,31,29} // 跨月处理
};

/* 简易线性回归: y = a + bx */
void countPendingPackages(ListNode* head, time_t startDate, double* counts) //ListNode*head相当于真正的头指针counts对应着每一天的包裹数量
{
	// 生成过去14天的时间范围（含输入日期的当天）
	time_t dayStarts[DAYS];
	struct tm start_tm;
	localtime_s(&start_tm, &startDate);
	//start_tm.tm_mday = 0;
	start_tm.tm_hour = 0;
	start_tm.tm_min = 0;
	start_tm.tm_sec = 0;
	mktime(&start_tm);
	startDate = mktime(&start_tm);

	for (int i = 0; i < 14; i++)
	{
		struct tm tmp = start_tm;
		tmp.tm_mday -= i;
		tmp.tm_hour = 0;
		tmp.tm_min = 0;
		tmp.tm_sec = 0;
		mktime(&tmp);  // 自动处理跨月/年
		dayStarts[i] = mktime(&tmp);
	}

	// 统计包裹
	for (ListNode* node = head; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		struct tm tm_pending;
		localtime_s(&tm_pending, &pkg->time.pending);

		// 转换为当天0点时间戳
		tm_pending.tm_hour = 0;
		tm_pending.tm_min = 0;
		tm_pending.tm_sec = 0;
		time_t pendingDay = mktime(&tm_pending);

		// 匹配统计范围
		for (int i = 0; i < DAYS; i++)
		{
			if (pendingDay == dayStarts[i])
			{
				counts[i] += 1.0;
				break;
			}
		}

	}

}
// 严格日期验证函数
bool validateDate(int year, int month, int day)
{
	// 基础范围校验
	if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31)
	{
		return false;
	}

	// 各月份天数验证
	int daysInMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		daysInMonth[2] = 29; // 闰年2月

	}

	return day <= daysInMonth[month];
}

bool inputDateSafe(time_t* result, int year, int month, int day)
{
	struct tm tm = { 0 };
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	//tm.tm_isdst = -1;

	*result = mktime(&tm);
	if (*result == -1) {
		fprintf(stderr, "错误：时间转换失败\n");
		return false;
	}

	// 验证转换结果与输入一致
	struct tm verify_tm;
	localtime_s(&verify_tm, result);
	if (verify_tm.tm_year + 1900 != year ||
		verify_tm.tm_mon + 1 != month ||
		verify_tm.tm_mday != day) {
		fprintf(stderr, "错误：日期自动调整无效\n");
		return false;
	}
	return true;
}

void linearRegression(const double x[], const double y[], int n, double* a, double* b)//一次函数算a,b系数
{
	double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumXX = 0.0;
	for (int i = 0; i < n; i++)
	{
		sumX += x[i];
		sumY += y[i];
		sumXY += x[i] * y[i];
		sumXX += x[i] * x[i];
	}
	double veragex = sumX / n;
	double veragey = sumY / n;
	double denominator = sumXX - veragex * veragex * n;
	if (denominator == 0.0)
	{
		*b = 0.0;
		*a = 0.0;
		return;
	}
	*b = (sumXY - n * veragex * veragey) / denominator;  // 斜率
	*a = (sumY - (*b) * sumX) / n;                 // 截距
}

void exponentialRegression(const double x[], const double y[], int n, double* a, double* b)//指数函数算a,b系数 
{
	linearRegression(x, y, n, a, b);
}

void  logarithmicRegression(const double x[], const double y[], int n, double* a, double* b)//对数函数算a,b ;y=a+blnx;
{
	double xdata[DAYS] = { };//t
	for (int i = 0; i < DAYS; i++)
	{
		xdata[i] = log(x[i]);
	}
	linearRegression(xdata, y, n, a, b);
}

/* 绘制ASCII折线图，o表示实际值，x表示预测值 */
void drawAsciiChart(const double x[], const double y[], const double yPred[], int n)
{
	/* 找最大y值，用于设置图表高度 */
	double maxY = y[0];
	for (int i = 1; i < n; i++)
	{
		if (y[i] > maxY)
		{
			maxY = y[i];
		}
		if (yPred[i] > maxY)
		{
			maxY = yPred[i];
		}
	}
	int height = (int)maxY + 1;
	double minY = y[0];
	for (int i = 1; i < n; i++)
	{
		if (y[i] < minY)
		{
			minY = y[i];
		}
		if (yPred[i] < minY)
		{
			minY = yPred[i];
		}
	}
	int lowest = (int)minY - 1;

	/* 从上往下打印每一行 */
	for (int row = height; row >= lowest; row--)
	{
		printf("%3d | ", row);
		/* 每列对应一个数据点 */
		for (int col = 0; col < n; col++)
		{
			int actual = (int)(y[col] + 0.5);
			int pred = (int)(yPred[col] + 0.5);
			if (row == actual && row == pred)
			{
				printf("*  ");  /* 重合 */
			}
			else if (row == actual)
			{
				printf("o  ");  /* 实际值 */
			}
			else if (row == pred)
			{
				printf("x  ");  /* 预测值 */
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}

	/* 打印X轴刻度 */
	printf("    +");
	for (int i = 0; i < n; i++)
	{
		printf("---");
	}
	printf("\n      ");
	for (int i = 0; i < n; i++)
	{
		printf("%-2.0f ", x[i]);
	}
	printf("\n");
}

double calculateSumOfSquareResiduals(double estimatedValues[], double actualValues[], int count) //计算残差平方
{
	double sum = 0;
	for (int i = 0; i < count; i++)
	{
		sum += (actualValues[i] - estimatedValues[i]) * (actualValues[i] - estimatedValues[i]);
	}
	return sum;
}

void drawPart(double* values, double* estimated,int year,int month,int day)
{
	cleardevice();
	// 修改 drawChartView 调用中的字符串参数以匹配 LPCTSTR 类型  
	int unitValue = drawChartView(values, DAYS, ORIGINX, ORIGINY, TOATALWIDTH, TOTALHEIGHT, UNITWIDTH, UNITHEIGHT, _T("时间/天"), _T("数量/个"), _T("从今日起前14天的入库包裹数"));
	drawLineSeries(values, unitValue, DAYS, ORIGINX, ORIGINY, UNITWIDTH, UNITHEIGHT, GREEN);
	drawSplineSeries(estimated, unitValue, DAYS, ORIGINX, ORIGINY, UNITWIDTH, UNITHEIGHT, RED);
	
	struct button* p4 = button(850, 550, "返回");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p4);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p4, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 3:
		free(p4);
		nextwindow(year,month,day);
		break;
	default:
		break;
	}
}

void Mainpart(int year, int month, int day)
{
	time_t startDate;
	if (!inputDateSafe(&startDate, year, month, day))
	{
		fprintf(stderr, "日期输入无效\n");
		return; // 修改为void函数的返回类型
	}
	struct tm start_tm = {};
	localtime_s(&start_tm, &startDate);
	//start_tm.tm_mday = 1;
	start_tm.tm_hour = 0;
	start_tm.tm_min = 0;
	start_tm.tm_sec = 0;
	mktime(&start_tm);
	startDate = mktime(&start_tm);
	// 执行统计
	/* 本月的入库数(示例)，可扩展到出库数与滞留件数 */
	double counts[DAYS] = { 0.0 };
	countPendingPackages(getPackages()->head->next, startDate, counts);
	/* x代表第几天 */
	double xData[DAYS] = { };
	for (int i = 0; i < DAYS; i++)
	{
		xData[i] = i + 1;
	}
	/* 线性回归求斜率b与截距a */
	/*这里如果是一次函数需要执行的内容*/
	//1.一次函数 2.指数函数 3.对数函数
	//1.
	double a1 = 0.0, b1 = 0.0;
	linearRegression(xData, counts, DAYS, &a1, &b1);
	double yPred[DAYS];
	for (int i = 0; i < DAYS; i++) {
		yPred[i] = a1 + b1 * xData[i];
	}
	double r1 = calculateSumOfSquareResiduals(yPred, counts, DAYS);
	double a2 = 0.0, b2 = 0.0;
	exponentialRegression(xData, counts, DAYS, &a2, &b2);
	double yPred0[DAYS];//t
	double yPred1[DAYS];//y
	for (int i = 0; i < DAYS; i++) {
		yPred0[i] = a2 + b2 * xData[i];
		yPred1[i] = exp(yPred0[i]);
	}
	double r2 = calculateSumOfSquareResiduals(yPred1, counts, DAYS);
	double a3 = 0.0, b3 = 0.0;
	logarithmicRegression(xData, counts, DAYS, &a3, &b3);
	double yPred3[DAYS];//y
	for (int i = 0; i < DAYS; i++)
	{
		yPred3[i] = a3 + b3 * log(xData[i]);
	}
	double r3 = calculateSumOfSquareResiduals(yPred3, counts, DAYS);
	//@比较部分@
	double temp = 0.0;
	temp = min(min(r1, r2), r3);
	//根据得到的最小残差和匹配对应的操作
	if (temp == r1)//一次函数操作
	{
		drawPart(counts, yPred,year,month,day);
	}
	if (temp == r2)//指数函数操作
	{
		drawPart(counts, yPred1,year, month, day);
	}
	if (temp == r3)//对数函数操作
	{
		drawPart(counts, yPred3, year, month, day);
	}
}
void futuredata(int year, int month, int day)
{
	time_t startDate;
	if (!inputDateSafe(&startDate, year, month, day))
	{
		fprintf(stderr, "日期输入无效\n");
		return; // 修改为void函数的返回类型
	}
	struct tm start_tm = {};
	localtime_s(&start_tm, &startDate);
	//start_tm.tm_mday = 1;
	start_tm.tm_hour = 0;
	start_tm.tm_min = 0;
	start_tm.tm_sec = 0;
	mktime(&start_tm);
	startDate = mktime(&start_tm);
	double counts[DAYS] = { 0.0 };
	countPendingPackages(getPackages()->head->next, startDate, counts);
	double xData[DAYS] = { };
	for (int i = 0; i < DAYS; i++)
	{
		xData[i] = i + 1;
	}
	//1.
	double a1 = 0.0, b1 = 0.0;
	linearRegression(xData, counts, DAYS, &a1, &b1);
	double yPred[DAYS];
	for (int i = 0; i < DAYS; i++) {
		yPred[i] = a1 + b1 * xData[i];
	}
	double r1 = calculateSumOfSquareResiduals(yPred, counts, DAYS);
	double a2 = 0.0, b2 = 0.0;
	exponentialRegression(xData, counts, DAYS, &a2, &b2);
	double yPred0[DAYS];//t
	double yPred1[DAYS];//y
	for (int i = 0; i < DAYS; i++) {
		yPred0[i] = a2 + b2 * xData[i];
		yPred1[i] = exp(yPred0[i]);
	}
	double r2 = calculateSumOfSquareResiduals(yPred1, counts, DAYS);
	double a3 = 0.0, b3 = 0.0;
	logarithmicRegression(xData, counts, DAYS, &a3, &b3);
	double yPred3[DAYS];//y
	for (int i = 0; i < DAYS; i++)
	{
		yPred3[i] = a3 + b3 * log(xData[i]);
	}
	double r3 = calculateSumOfSquareResiduals(yPred3, counts, DAYS);
	//@比较部分@
	double temp = 0.0;
	temp = min(min(r1, r2), r3);
	//根据得到的最小残差和匹配对应的操作
	if (temp == r1) // 一次函数操作
	{
		printf("回归方程(入库 y) = %+.2lf %+.2lf * x\n", a1, b1);
		buildWindow();
		double sumNextWeek = 0.0;
		for (int day = 1; day <= 7; day++)
		{
			double predValue = a1 + b1 * (DAYS + day);
			sumNextWeek += predValue;
			label(400, 50 + 50 * day, predValue);
		}
		label(50, 450, "下一周入库总量预测");
		label(400, 450, sumNextWeek);
	}
	if (temp == r2) // 指数函数操作
	{
		printf("回归方程(入库 y) = %+.2lf * e^(%+.2lf * x)\n", a2, b2);
		buildWindow();
		double sumNextWeek = 0.0;
		for (int day = 1; day <= 7; day++)
		{
			double predValue = a2 * (exp(b2 * (DAYS + day)));
			sumNextWeek += predValue;
			label(400, 50 + 50 * day, predValue);
		}
		label(50, 450, "下一周入库总量预测");
		label(400, 450, sumNextWeek);
	}
	if (temp == r3) // 对数函数操作
	{
		printf("回归方程(入库 y) = %+.2lf * lnx %+.2lf\n", b3, a3);
		buildWindow();
		double sumNextWeek = 0.0;
		for (int day = 1; day <= 7; day++)
		{
			double predValue = a3 + b3 * log(DAYS + day);
			sumNextWeek += predValue;
			label(400, 50 + 50 * day, predValue);
		}
		label(50, 450, "下一周入库总量预测");
		label(400, 450, sumNextWeek);
	}
	struct button* p3 = button(850, 550, "返回");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 3:
		free(p3);
		nextwindow(year, month, day);
		break;
	default:
		break;
	}

}
void WeeklyBriefly()
{
	ListNode* head = getPackages()->head->next;//头指针
	ListNode* p = head;
	long long packagestatecount[8] = { 0 };
	long double allmoney = 0.0;
	//显示寄件数

	time_t startDate;
	time(&startDate);
	struct tm start_tm = {};
	localtime_s(&start_tm, &startDate);
	//start_tm.tm_mday = 1;
	start_tm.tm_hour = 0;
	start_tm.tm_min = 0;
	start_tm.tm_sec = 0;
	mktime(&start_tm);
	startDate = mktime(&start_tm);
	// 生成过去一周时间范围（含输入日期的当天）
	time_t dayStarts[7];
	struct tm start_t;
	localtime_s(&start_t, &startDate);
	//start_t.tm_mday = 0;
	start_t.tm_hour = 0;
	start_t.tm_min = 0;
	start_t.tm_sec = 0;
	mktime(&start_t);
	startDate = mktime(&start_t);

	for (int i = 0; i < 7; i++)
	{
		struct tm tmp = start_t;
		tmp.tm_mday -= i;
		tmp.tm_hour = 0;
		tmp.tm_min = 0;
		tmp.tm_sec = 0;
		mktime(&tmp);  // 自动处理跨月/年
		dayStarts[i] = mktime(&tmp);
	}
	for (; p != NULL; p = p->next)
	{
		Package* pkg = (Package*)p->data;
		struct tm tm_pending;
		localtime_s(&tm_pending, &pkg->time.pending);

		// 转换为当天0点时间戳
		tm_pending.tm_hour = 0;
		tm_pending.tm_min = 0;
		tm_pending.tm_sec = 0;
		time_t pendingDay = mktime(&tm_pending);

		// 匹配统计范围
		for (int i = 0; i <= 7; i++)
		{
			if (pendingDay == dayStarts[i])
			{
				if (pkg->packageState == Ordered)
				{
					packagestatecount[0]++;
				}
				if (pkg->packageState == Shipped)
				{
					packagestatecount[1]++;
				}
				if (pkg->packageState == Pending)
				{
					packagestatecount[2]++;
				}
				if (pkg->packageState == Delivered)
				{
					packagestatecount[3]++;
				}
				if (pkg->packageState == Refused)
				{
					packagestatecount[4]++;
				}
				if (pkg->packageState == Canceled)
				{
					packagestatecount[5]++;
				}
				if (pkg->packageState == Misdelivered)
				{
					packagestatecount[6]++;
				}
				if (pkg->packageState == DamagedLost)
				{
					packagestatecount[7]++;
				}
				allmoney += (long double)(pkg->shippingFee) * 0.1;
				break;
			}
		}
	}
	label(50, 50, "已下单包裹数："); label(400, 50, packagestatecount[0]);
	label(50, 100, "已寄出包裹数："); label(400, 100, packagestatecount[1]);
	label(50, 150, "待收件包裹数："); label(400, 150, packagestatecount[2]);
	label(50, 200, "已收件包裹数："); label(400, 200, packagestatecount[3]);
	label(50, 250, "被拒收包裹数："); label(400, 250, packagestatecount[4]);
	label(50, 300, "被取消包裹数："); label(400, 300, packagestatecount[5]);
	label(50, 350, "被误取包裹数："); label(400, 350, packagestatecount[6]);
	label(50, 400, "损坏丢失包裹数："); label(400, 400, packagestatecount[7]);
	label(50, 450, "驿站盈利总和："); label(400, 450, allmoney);
}
