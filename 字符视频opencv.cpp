#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>

using namespace cv;
using namespace std;

const char* char_list = " .,-'`&&&&&&&&((((%%$$''((''&&wxyz<>()\/{}[]?234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ%&@#$";
int len = 255 / strlen(char_list);
int main()
{

	VideoCapture cap;
	cap.open("D:/bilbil Video clip/44.mp4");
	//PlaySound(TEXT("D:/bilbil Video clip/44.mp4"), NULL, SND_ASYNC);//播放音频，可选
  /*cv::Ptr<AudioOutput> audio_output = createAudioOutput(fps, total_frames);*/
	if (!cap.isOpened()) {
		cout << "can't open file" << endl;
		return -1;
	}
	Mat frame, frame_resize, frame_gray;
	while (true)
	{
		cap >> frame;
		if (frame.empty())	break;
		resize(frame, frame_resize, Size(300, 90));
		cvtColor(frame_resize, frame_gray, COLOR_BGR2GRAY);
		String txt = "";

		int height = frame_gray.rows;
		int width = frame_gray.cols;

		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++)
			{
				int pdata = frame_gray.ptr<uchar>(j)[i];
				if (pdata == 255)
					txt += char_list[87];
				else
					txt += char_list[pdata / len];
			}
			txt += "\n";
		}

		//将光标移动到（0，0）处
		HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		pos.X = 0;
		pos.Y = 0;
		SetConsoleCursorPosition(hConsoleOutput, pos);

		//输出当前字符
		cout << txt;
	}
	return 0;
}

////#include<opencv2/opencv.hpp>
////#include<iostream>
////#include <string>
////using namespace cv;
////void ImageThreshold(String str) {
////	Mat image = imread(str);
////	Mat binary;
////	cvtColor(image, binary, COLOR_BGR2GRAY);
////	imshow("test_opencv_srtup", binary);
////	waitKey(0);
////}
////int main() {
////	String str = "C:\\Users\\NWT\\Desktop\\nb.jpeg";
////	ImageThreshold(str);
////	return 0;
////}
//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <Windows.h>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//    // 加载视频文件
//    cv::VideoCapture cap("D:/bilbil Video clip/44.mp4");
//
//    // 检查是否成功加载
//    if (!cap.isOpened())
//    {
//        std::cout << "Error opening video stream or file" << endl;
//        return -1;
//    }
//
//    // 创建窗口
//    namedWindow("Video", WINDOW_NORMAL);
//    resizeWindow("Video", 640, 480);
//
//    // 获取视频的FPS和帧数
//    /*double fps = cap.get(CAP_PROP_FPS);
//    int total_frames = cap.get(CAP_PROP_FRAME_COUNT);*/
//
//    // 创建音频播放器
//    PlaySound(TEXT("D:/bilbil Video clip/44.mp4"), NULL, SND_ASYNC);//播放音频，可选
//    /*cv::Ptr<AudioOutput> audio_output = createAudioOutput(fps, total_frames);*/
//
//    // 循环播放视频
//    while (true)
//    {
//        Mat frame;
//        // 读取视频帧
//        if (!cap.read(frame))
//            break;
//
//        // 播放音频
//        PlaySound(TEXT("D:/bilbil Video clip/44.mp4"), NULL, SND_ASYNC);//播放音频，可选
//
//        // 显示视频帧
//        imshow("Video", frame);
//
//        // 按下ESC键退出播放
//        if (waitKey(25) == 27)
//            break;
//    }
//
//    // 释放视频流、音频播放器和窗口
//    cap.release();
//    destroyAllWindows();
//
//    return 0;
//}
