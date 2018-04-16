#include "iostream"
#include "Queue_LinkList.h"
using namespace std;
Queue <int> Open;
Queue <int> Close;
void Push_Point(Queue <int > * a, int b[2]);
void Pop_Point(Queue <int > * a,int *b);
void FindPoints_and_PushOpen();
void Calculate_MinPath();
void Push_Close();
void Delete_Min();
int Judge_CloseandOpen(int point[2]);
int Map[27][27] = {							//��ͼ����
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
};
int Map_Father[27][27] = { 0 };					//��¼ÿ����ĸ��ڵ�
double Map_Distan[27][27] = { 0 };				//��¼ÿ���㵽��ʼ��ľ���
int Begin_Point[2] = { 26,0 };					//������ʼ������
int Over_Point[2] = { 0,26 };					//������ֹ������
int  Min_Point[2];
int  Temp_Point[2];
int  Temp_Point2[2];
int main()
{
	memcpy(Min_Point, Begin_Point, sizeof(Begin_Point)); //��̾��������Ϊ��ʼ��
	Push_Point(&Open, Begin_Point);						 //��ʼ�������
	
	while (!Open.empty())								//��ʼ����ѭ��
	{
		FindPoints_and_PushOpen();						//�ҷ������������ڵĵ���Open����
		Push_Close();									//�߹��ĵ���Close����
		Delete_Min();									//Open������ɾ���߹��ĵ�
		Calculate_MinPath();							//����O���������̵�·���ĵ�
	}

	memcpy(Temp_Point, Over_Point, sizeof(Over_Point));
	while (Map_Father[Temp_Point[0]][Temp_Point[1]])		//���ݣ���ԭ�ߵ�·����·��������Map_
	{
		Temp_Point2[0] = Temp_Point[0]+ (Map_Father[Temp_Point[0]][Temp_Point[1]]-1)/3 -1;
		Temp_Point2[1] = Temp_Point[1]+ (Map_Father[Temp_Point[0]][Temp_Point[1]]-1)%3 -1;
		Map_Father[Temp_Point[0]][Temp_Point[1]] = 10;//���߹�������·��ֵ��Ϊ10����ͼ��ʱ��ֱ�Ӳ�ѯ
		memcpy(Temp_Point, Temp_Point2, sizeof(Over_Point));
	}
	Map_Father[Begin_Point[0]][Begin_Point[1]] = 10;
	cout << "      A * Algorithm For Optimal Path Search Writed By Jiang." << endl;
	cout << "     ";					////////////////////////////////////����̨ ��ͼ
	for (int i = 0; i < 27; i++)
	{
		cout << "һ";
	}
	cout << endl;
	for (int i = 0; i < 27; i++)
	{
		cout << "     |" ;
		for (int j = 0; j < 27; j++)
		{
			if (Map[i][j])
			{
				cout << "��";
			}
			else if (Map_Father[i][j] == 10)//��ѯ�ߵ�·��
			{
				cout << "+ ";
			}else
				cout << "  ";
		}
		cout << "|" << endl;
	}
	cout << "     ";
	for (int i = 0; i < 27; i++)
	{
		cout << "һ";
	}
	cout << endl;					////////////////////////////////////����̨ ��ͼ
	cout << "                           Finished!" << endl;
	system("pause");
    return 0;
}
void Push_Point(Queue <int> * a,int b[2])//�����һ������
{
	(*a).push(b[0]); 
	(*a).push(b[1]);
}
void Pop_Point(Queue <int> * a,int* b)//������һ������
{
	*b=(*a).pop(); 
	*(b+1) = (*a).pop(); 
}
int Distance_sum(int point[2])//�������h
{
	int aaa, bbb, ccc;
	bbb = sqrt((Over_Point[0] - point[0])* (Over_Point[0] - point[0]));
	ccc = sqrt((Over_Point[1] - point[1])*(Over_Point[1] - point[1]));
	if (bbb > ccc) aaa = ccc;
	else aaa = bbb;
	return abs(bbb-ccc)+aaa;
}
void FindPoints_and_PushOpen()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) 
		{
			Temp_Point[0] = Min_Point[0]+1-i; Temp_Point[1] = Min_Point[1] +1-j;
			if (Temp_Point[0] >= 0 && Temp_Point[0] <= 26 && Temp_Point[1] >= 0 && Temp_Point[1] <= 26)
			{
				if (!Map[Temp_Point[0]][Temp_Point[1]] && !Judge_CloseandOpen(Temp_Point))//  ��min��Χ�ĵ�
				{
					if (Temp_Point[0] == Min_Point[0] && Temp_Point[1] == Min_Point[1])
					{
					}
					else
					{
						Push_Point(&Open, Temp_Point);
						Map_Distan[Temp_Point[0]][Temp_Point[1]] = Map_Distan[Min_Point[0]][Min_Point[1]]+sqrt((i-1)*(i - 1) + (j - 1)*(j - 1));
						Map_Father[Temp_Point[0]][Temp_Point[1]] = i*3+j+1;
					}
				}
			}
		}
	}


}

void Calculate_MinPath() {			//��Open�����µĵ��ҵ�·����С�ĵ�
	int bb[2];
	double temp_total, min = 20000.0;
	for (int i = 1; i <= Open.size(); i++)
	{
		bb[0]= Open.Query( i++);
		bb[1]= Open.Query( i);
		temp_total = Distance_sum(bb)+Map_Distan[bb[0]][bb[1]];
		if (min > temp_total)
		{
			min = temp_total;
			Min_Point[0]= Open.Query(i-1);//��С����ĵ������
			Min_Point[1]= Open.Query(i);
		}
	}
}
void Push_Close() {						//���ҹ������������Close����
	Push_Point(&Close,Min_Point);
}
int Judge_CloseandOpen(int point[2])           //�ж����ҵ��ĵ��Ƿ���Close��	1����	0������
{
	int bb[2];
	for (int i = 1; i <= Close.size(); i++) {
		bb[0] = Close.Query(i++);
		bb[1] = Close.Query(i);
		if (point[0] == bb[0] && point[1] == bb[1])
		{
			return 1;
		}
	}
	for (int i = 1; i <= Open.size(); i++) {
		bb[0] = Open.Query(i++);
		bb[1] = Open.Query(i);
		if (point[0] == bb[0] && point[1] == bb[1])
		{
			return 1;
		}
	}
	return 0;
}
void Delete_Min() {
	int bb[2];
	int a= Open.size();
	for (int i = 1; i <= Open.size(); i++) {
		bb[0] = Open.Query(i++);
		bb[1] =	Open.Query(i);
		if (Min_Point[0] == bb[0] && Min_Point[1] == bb[1])
		{
			Open.del(i-1);
			Open.del(i-1);
			break;
		}
	}
}