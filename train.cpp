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
	//��ȡ����
	Mat classes;
	Mat trainingData;
	Mat trainingImages;
	vector<int> trainingLabels;
	get_1(trainingImages, trainingLabels);
	get_0(trainingImages, trainingLabels);
	Mat(trainingImages).copyTo(trainingData);
	trainingData.convertTo(trainingData, CV_32FC1);
	Mat(trainingLabels).copyTo(classes);


	//����SVM����
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
	std::cout << "CΪ��" << svm->getC() << std::endl;

	/*svm->train(trainingData,classes,)*/
	svm->train(trainingData, cv::ml::ROW_SAMPLE, trainingLabels);
	svm->save("svm.xml");
	cout << "ѵ�����ˣ���" << endl;
	return 0;
}


//�������ļ�����·��
void getFiles(string path, vector<string>& files)
{
	long long  hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	//_findfirst������ȡ�ļ�
	//assign����path��p�����\\����
	// c_str()�ӿ���string���һ������,���ص����ַ������׵�ַ
	//fileinfo �����������������ļ���Ϣ�Ľṹ���ָ��
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //������ҵ������ļ���
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) //�����ļ��в���
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files); //�õ��ļ���
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
		SrcImage = SrcImage.reshape(1, 1);//cv::reshape(int cn, int row =0),cn��ʾͨ������0��ʾ���䡿��rowΪ����
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



