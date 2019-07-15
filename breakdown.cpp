//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace  cv;
//
//int main() {
//	char ad[128] = { 0 };
//	int filename = 0, filenum = 0;
//	Mat img = imread("digits.png");
//	Mat gray;
//	cvtColor(img, gray, CV_BGR2GRAY); //ͼ��ҶȻ�
//	int b = 20;
//	int m = gray.rows / b; //ԭͼΪ1000*2000
//	int n = gray.cols / b; //�ü�Ϊ5000��20*20��С��
//
//	for (int i= 0; i < m;i++)  //ȡÿһ����
//	{
//		int offsetRow = i*b;  
//		if (i%5 == 0&&i !=0)
//		{
//			filename++;
//			filenum = 0;
//		}
//		for (int j = 0; j < n; j++)
//		{
//			int offsetCol = j * b;
//		
//		sprintf_s(ad, "D:\\data\\%d\%d.jpg", filename, filenum++);
//		Mat tmp;
//		gray(Range(offsetRow, offsetRow + b), Range(offsetCol, offsetCol + b)).copyTo(tmp);
//		imwrite(ad, tmp);
//		}
//	}
//	return 0;
//}




#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	char ad[128] = { 0 };
	int  filename = 0, filenum = 0;
	Mat img = imread("digits.png");
	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);
	int b = 20;
	int m = gray.rows / b;   //ԭͼΪ1000*2000
	int n = gray.cols / b;   //�ü�Ϊ5000��20*20��Сͼ��

	for (int i = 0; i < m; i++)
	{
		int offsetRow = i*b;  //���ϵ�ƫ����
		if (i % 5 == 0 && i != 0)
		{
			filename++;
			filenum = 0;
		}
		for (int j = 0; j < n; j++)
		{
			int offsetCol = j*b; //���ϵ�ƫ����
			if(filename==0)
				sprintf_s(ad, "D://data//0//%d.jpg", filenum++);
			else if (filename == 1)
				sprintf_s(ad, "D://data//1//%d.jpg", filenum++);
			else if (filename == 2)
				sprintf_s(ad, "D://data//2//%d.jpg", filenum++);
			else if (filename == 3)
				sprintf_s(ad, "D://data//3//%d.jpg", filenum++);
			else if (filename == 4)
				sprintf_s(ad, "D://data//4//%d.jpg", filenum++);
			else if (filename == 5)
				sprintf_s(ad, "D://data//5//%d.jpg", filenum++);
			else if (filename == 6)
				sprintf_s(ad, "D://data//6//%d.jpg", filenum++);
			else if (filename == 7)
				sprintf_s(ad, "D://data//7//%d.jpg", filenum++);
			else if (filename == 8)
				sprintf_s(ad, "D://data//8//%d.jpg", filenum++);
			else 
				sprintf_s(ad, "D://data//9//%d.jpg", filenum++);

			//��ȡ20*20��С��
			Mat tmp;
			gray(Range(offsetRow, offsetRow + b), Range(offsetCol, offsetCol + b)).copyTo(tmp);
			imwrite(ad, tmp);
		}
	}
	return 0;
}