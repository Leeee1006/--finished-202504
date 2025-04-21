#include"tendencypredict.h"

#define DAYS 14  /* ��ȥ14�����ʷ���� */
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
	{0,31,28,31,30,31,30,31,31,30,31,30,31,31,28}, // ���괦��
	{0,31,29,31,30,31,30,31,31,30,31,30,31,31,29} // ���´���
};

/* �������Իع�: y = a + bx */
void countPendingPackages(ListNode* head, time_t startDate, double* counts) //ListNode*head�൱��������ͷָ��counts��Ӧ��ÿһ��İ�������
{
	// ���ɹ�ȥ14���ʱ�䷶Χ�����������ڵĵ��죩
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
		mktime(&tmp);  // �Զ��������/��
		dayStarts[i] = mktime(&tmp);
	}

	// ͳ�ư���
	for (ListNode* node = head; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		struct tm tm_pending;
		localtime_s(&tm_pending, &pkg->time.pending);

		// ת��Ϊ����0��ʱ���
		tm_pending.tm_hour = 0;
		tm_pending.tm_min = 0;
		tm_pending.tm_sec = 0;
		time_t pendingDay = mktime(&tm_pending);

		// ƥ��ͳ�Ʒ�Χ
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
// �ϸ�������֤����
bool validateDate(int year, int month, int day)
{
	// ������ΧУ��
	if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31)
	{
		return false;
	}

	// ���·�������֤
	int daysInMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		daysInMonth[2] = 29; // ����2��

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
		fprintf(stderr, "����ʱ��ת��ʧ��\n");
		return false;
	}

	// ��֤ת�����������һ��
	struct tm verify_tm;
	localtime_s(&verify_tm, result);
	if (verify_tm.tm_year + 1900 != year ||
		verify_tm.tm_mon + 1 != month ||
		verify_tm.tm_mday != day) {
		fprintf(stderr, "���������Զ�������Ч\n");
		return false;
	}
	return true;
}

void linearRegression(const double x[], const double y[], int n, double* a, double* b)//һ�κ�����a,bϵ��
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
	*b = (sumXY - n * veragex * veragey) / denominator;  // б��
	*a = (sumY - (*b) * sumX) / n;                 // �ؾ�
}

void exponentialRegression(const double x[], const double y[], int n, double* a, double* b)//ָ��������a,bϵ�� 
{
	linearRegression(x, y, n, a, b);
}

void  logarithmicRegression(const double x[], const double y[], int n, double* a, double* b)//����������a,b ;y=a+blnx;
{
	double xdata[DAYS] = { };//t
	for (int i = 0; i < DAYS; i++)
	{
		xdata[i] = log(x[i]);
	}
	linearRegression(xdata, y, n, a, b);
}

/* ����ASCII����ͼ��o��ʾʵ��ֵ��x��ʾԤ��ֵ */
void drawAsciiChart(const double x[], const double y[], const double yPred[], int n)
{
	/* �����yֵ����������ͼ��߶� */
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

	/* �������´�ӡÿһ�� */
	for (int row = height; row >= lowest; row--)
	{
		printf("%3d | ", row);
		/* ÿ�ж�Ӧһ�����ݵ� */
		for (int col = 0; col < n; col++)
		{
			int actual = (int)(y[col] + 0.5);
			int pred = (int)(yPred[col] + 0.5);
			if (row == actual && row == pred)
			{
				printf("*  ");  /* �غ� */
			}
			else if (row == actual)
			{
				printf("o  ");  /* ʵ��ֵ */
			}
			else if (row == pred)
			{
				printf("x  ");  /* Ԥ��ֵ */
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}

	/* ��ӡX��̶� */
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

double calculateSumOfSquareResiduals(double estimatedValues[], double actualValues[], int count) //����в�ƽ��
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
	// �޸� drawChartView �����е��ַ���������ƥ�� LPCTSTR ����  
	int unitValue = drawChartView(values, DAYS, ORIGINX, ORIGINY, TOATALWIDTH, TOTALHEIGHT, UNITWIDTH, UNITHEIGHT, _T("ʱ��/��"), _T("����/��"), _T("�ӽ�����ǰ14�����������"));
	drawLineSeries(values, unitValue, DAYS, ORIGINX, ORIGINY, UNITWIDTH, UNITHEIGHT, GREEN);
	drawSplineSeries(estimated, unitValue, DAYS, ORIGINX, ORIGINY, UNITWIDTH, UNITHEIGHT, RED);
	
	struct button* p4 = button(850, 550, "����");
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
		fprintf(stderr, "����������Ч\n");
		return; // �޸�Ϊvoid�����ķ�������
	}
	struct tm start_tm = {};
	localtime_s(&start_tm, &startDate);
	//start_tm.tm_mday = 1;
	start_tm.tm_hour = 0;
	start_tm.tm_min = 0;
	start_tm.tm_sec = 0;
	mktime(&start_tm);
	startDate = mktime(&start_tm);
	// ִ��ͳ��
	/* ���µ������(ʾ��)������չ������������������ */
	double counts[DAYS] = { 0.0 };
	countPendingPackages(getPackages()->head->next, startDate, counts);
	/* x����ڼ��� */
	double xData[DAYS] = { };
	for (int i = 0; i < DAYS; i++)
	{
		xData[i] = i + 1;
	}
	/* ���Իع���б��b��ؾ�a */
	/*���������һ�κ�����Ҫִ�е�����*/
	//1.һ�κ��� 2.ָ������ 3.��������
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
	//@�Ƚϲ���@
	double temp = 0.0;
	temp = min(min(r1, r2), r3);
	//���ݵõ�����С�в��ƥ���Ӧ�Ĳ���
	if (temp == r1)//һ�κ�������
	{
		drawPart(counts, yPred,year,month,day);
	}
	if (temp == r2)//ָ����������
	{
		drawPart(counts, yPred1,year, month, day);
	}
	if (temp == r3)//������������
	{
		drawPart(counts, yPred3, year, month, day);
	}
}
void futuredata(int year, int month, int day)
{
	time_t startDate;
	if (!inputDateSafe(&startDate, year, month, day))
	{
		fprintf(stderr, "����������Ч\n");
		return; // �޸�Ϊvoid�����ķ�������
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
	//@�Ƚϲ���@
	double temp = 0.0;
	temp = min(min(r1, r2), r3);
	//���ݵõ�����С�в��ƥ���Ӧ�Ĳ���
	if (temp == r1) // һ�κ�������
	{
		printf("�ع鷽��(��� y) = %+.2lf %+.2lf * x\n", a1, b1);
		buildWindow();
		double sumNextWeek = 0.0;
		for (int day = 1; day <= 7; day++)
		{
			double predValue = a1 + b1 * (DAYS + day);
			sumNextWeek += predValue;
			label(400, 50 + 50 * day, predValue);
		}
		label(50, 450, "��һ���������Ԥ��");
		label(400, 450, sumNextWeek);
	}
	if (temp == r2) // ָ����������
	{
		printf("�ع鷽��(��� y) = %+.2lf * e^(%+.2lf * x)\n", a2, b2);
		buildWindow();
		double sumNextWeek = 0.0;
		for (int day = 1; day <= 7; day++)
		{
			double predValue = a2 * (exp(b2 * (DAYS + day)));
			sumNextWeek += predValue;
			label(400, 50 + 50 * day, predValue);
		}
		label(50, 450, "��һ���������Ԥ��");
		label(400, 450, sumNextWeek);
	}
	if (temp == r3) // ������������
	{
		printf("�ع鷽��(��� y) = %+.2lf * lnx %+.2lf\n", b3, a3);
		buildWindow();
		double sumNextWeek = 0.0;
		for (int day = 1; day <= 7; day++)
		{
			double predValue = a3 + b3 * log(DAYS + day);
			sumNextWeek += predValue;
			label(400, 50 + 50 * day, predValue);
		}
		label(50, 450, "��һ���������Ԥ��");
		label(400, 450, sumNextWeek);
	}
	struct button* p3 = button(850, 550, "����");
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
	ListNode* head = getPackages()->head->next;//ͷָ��
	ListNode* p = head;
	long long packagestatecount[8] = { 0 };
	long double allmoney = 0.0;
	//��ʾ�ļ���

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
	// ���ɹ�ȥһ��ʱ�䷶Χ�����������ڵĵ��죩
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
		mktime(&tmp);  // �Զ��������/��
		dayStarts[i] = mktime(&tmp);
	}
	for (; p != NULL; p = p->next)
	{
		Package* pkg = (Package*)p->data;
		struct tm tm_pending;
		localtime_s(&tm_pending, &pkg->time.pending);

		// ת��Ϊ����0��ʱ���
		tm_pending.tm_hour = 0;
		tm_pending.tm_min = 0;
		tm_pending.tm_sec = 0;
		time_t pendingDay = mktime(&tm_pending);

		// ƥ��ͳ�Ʒ�Χ
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
	label(50, 50, "���µ���������"); label(400, 50, packagestatecount[0]);
	label(50, 100, "�Ѽĳ���������"); label(400, 100, packagestatecount[1]);
	label(50, 150, "���ռ���������"); label(400, 150, packagestatecount[2]);
	label(50, 200, "���ռ���������"); label(400, 200, packagestatecount[3]);
	label(50, 250, "�����հ�������"); label(400, 250, packagestatecount[4]);
	label(50, 300, "��ȡ����������"); label(400, 300, packagestatecount[5]);
	label(50, 350, "����ȡ��������"); label(400, 350, packagestatecount[6]);
	label(50, 400, "�𻵶�ʧ��������"); label(400, 400, packagestatecount[7]);
	label(50, 450, "��վӯ���ܺͣ�"); label(400, 450, allmoney);
}
