#include <stdio.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <io.h>

using namespace std;
using namespace cv;

void getFiles(string path, vector<string>&files);
void get_1(Mat & trainingImages, vector<int>& trainingLabels);
void get_0(Mat & trainingImages, vector<int>& trainingLabels);

int main() {
	//获取数据
	Mat classes;
	Mat trainingData;
	Mat trainingImages;
	vector<int> trainingLabels;
	get_1(trainingImages, trainingLabels);
	get_0(trainingImages, trainingLabels);
	Mat(trainingImages).copyTo(trainingData);
	trainingData.convertTo(trainingData, CV_32FC1);
	Mat(trainingLabels).copyTo(classes);


	//配置SVM参数
	Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
	svm->setType(cv::ml::SVM::C_SVC);
	svm->setKernel(cv::ml::SVM::LINEAR);
	svm->setDegree(0.0);
	svm->setGamma(1);
	svm->setCoef0(0);
	svm->setC(1);
	svm->setNu(0);
	svm->setP(0);
	svm->setTermCriteria(cvTermCriteria(CV_TERMCRIT_ITER, 1000, 0.001));
	std::cout << "C为：" << svm->getC() << std::endl;

	/*svm->train(trainingData,classes,)*/
	svm->train(trainingData, cv::ml::ROW_SAMPLE, trainingLabels);
	svm->save("svm.xml");
	cout << "训练好了！！" << endl;
	return 0;
}


//用来找文件具体路径
void getFiles(string path, vector<string>& files)
{
	long long  hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	//_findfirst用来读取文件
	//assign拷贝path给p，添加\\区分
	// c_str()接口是string类的一个函数,返回的是字符串的首地址
	//fileinfo ：这里就是用来存放文件信息的结构体的指针
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //如果查找到的是文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) //进入文件夹查找
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files); //得到文件名
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}
void get_1(Mat& trainingImages, vector<int>& trainingLabels)
{
	char * filePath = "D:\\data\\train_image\\1";
	vector<string> files;
	getFiles(filePath, files);
	int number = files.size();
	for (int i = 0; i < number; i++)
	{
		Mat  SrcImage = imread(files[i].c_str());
		SrcImage = SrcImage.reshape(1, 1);//cv::reshape(int cn, int row =0),cn表示通道数【0表示不变】，row为行数
		trainingImages.push_back(SrcImage);
		trainingLabels.push_back(1);
	}
}
void get_0(Mat& trainingImages, vector<int>& trainingLabels)
{
	char * filePath = "D:\\data\\train_image\\0";
	vector<string> files;
	getFiles(filePath, files);
	int number = files.size();
	for (int i = 0; i < number; i++)
	{
		Mat  SrcImage = imread(files[i].c_str());
		SrcImage = SrcImage.reshape(1, 1);
		trainingImages.push_back(SrcImage);
		trainingLabels.push_back(0);
	}
}



