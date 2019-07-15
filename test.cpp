#include <stdio.h>  
#include <time.h>  
#include <opencv2/opencv.hpp>  
#include <opencv/cv.h>  
#include <iostream> 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/ml/ml.hpp>  
#include <io.h>

using namespace std;
using namespace cv;
using namespace ml;

void getFiles(string path, vector<string>& files);

int main()
{
	int result = 0;
	char * filePath = "D:\\data\\test_image\\5";
	vector<string> files;
	getFiles(filePath, files);
	int number = files.size();
	printf("number=");
	printf("%d", number);
	string modelpath = "svm.xml";
	Ptr<ml::SVM> svm;
	svm = Algorithm::load<ml::SVM>(modelpath);//加载训练权重

	for (int i = 0; i < number; i++)
	{
		Mat inMat = imread(files[i].c_str());//c_str()返回string容器内部实现char指针
		Mat p = inMat.reshape(1, 1);
		p.convertTo(p, CV_32FC1);
		int response = (int)svm->predict(p);
		printf("response=:");
		printf("%d\n",response);
		if (response == 0)
		{
			result++;
		}
	}
	printf(" result=:");
	printf("%d\n",result);
	getchar();
	return  0;
}
void getFiles(string path, vector<string>& files)
{
	long long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
