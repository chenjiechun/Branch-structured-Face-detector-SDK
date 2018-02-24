#include "stdafx.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "bsFaceDetector.h"

#include <stdio.h>
#include <Windows.h>

using namespace std;
using namespace cv;
using namespace bsfd;

string window_name = "Capture - Face detection";

/**
 * @function main
 */
int main( int argc, char* argv[] )
{
	Mat frame;
	VideoCapture capture;
	vector<cv::Rect> detectedFaces;
	BsFaceDetector _bsFaceDetector;
	
    int vecNum = 6;
	int minFaces = 3;
	vector<vector<cv::Rect>> faceRectLists;
	vector<cv::Rect> avgFaces;
	vector<float> timeList;
	timeList.resize(vecNum);
	faceRectLists.resize(vecNum);
	const double GROUP_EPS_1 = 0.3;

	for (int i = 0; i < vecNum; i++)
		timeList[i] = 0;

	_bsFaceDetector.setDetThreashold(0.6);
	_bsFaceDetector.setMaxFace(cv::Size(640, 480));
	_bsFaceDetector.setMinFace(cv::Size(48, 48));
	_bsFaceDetector.setScaleFactor(1.2);
	_bsFaceDetector.setStep(3);
	_bsFaceDetector.setThreadNum(4);

	int res_tmp = _bsFaceDetector.loadModels("cascadeModels.bin", "seeta_fd_frontal_v1.0.bin");
	if (res_tmp < 0)
	{
		printf("model cannot be loaded!\n");
		return res_tmp;
	}
	capture.open( 0 );
	if( capture.isOpened() )
	{
		int curIdx = 0;
		for (;;)
		{
			capture >> frame;
			if (!frame.empty())
			{
				LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;	//Added by Jie-chun Chen
				LARGE_INTEGER Frequency;	//Added by Jie-chun Chen
				QueryPerformanceFrequency(&Frequency);	//Added by Jie-chun Chen
				QueryPerformanceCounter(&StartingTime);	//Added by Jie-chun Chen

				_bsFaceDetector.detectFaces(frame, detectedFaces);

				QueryPerformanceCounter(&EndingTime);	//Added by Jie-chun Chen
				ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;	//Added by Jie-chun Chen
				ElapsedMicroseconds.QuadPart *= 1000;	//Added by Jie-chun Chen
				float tempF = (ElapsedMicroseconds.QuadPart * 1.0) / Frequency.QuadPart;	//Added by Jie-chun Chen
				printf("cascade detector elapsed time: %.2f ms\n", tempF);	//Added by Jie-chun Chen	
				printf("detected faces: %d\n", detectedFaces.size());

				timeList[curIdx] = tempF;
				faceRectLists[curIdx].clear();
				avgFaces.clear();
				for (int i = 0; i < detectedFaces.size(); i++)
				{
					faceRectLists[curIdx].push_back(detectedFaces[i]);
					int count = 1;
					cv::Rect rect_sum;
					rect_sum.x = detectedFaces[i].x;
					rect_sum.y = detectedFaces[i].y;
					rect_sum.width = detectedFaces[i].width;
					rect_sum.height = detectedFaces[i].height;
					for (int j = 0; j < vecNum; j++)
					{
						if (curIdx != j)
						{
							for (int k = 0; k < faceRectLists[j].size(); k++)
							{
								int iArea = calc2RectsIntersectArea(detectedFaces[i], faceRectLists[j][k]);
								double iRatio_1 = (iArea * 1.0) / (detectedFaces[i].width * detectedFaces[i].height);
								double iRatio_2 = (iArea * 1.0) / (faceRectLists[j][k].width * faceRectLists[j][k].height);
								if ((iRatio_1 > 0.7) || (iRatio_2 > 0.7) || (bsfd::SimilarRects(GROUP_EPS_1)(detectedFaces[i], faceRectLists[j][k])))
								{
									count += 1;
									rect_sum.x += faceRectLists[j][k].x;
									rect_sum.y += faceRectLists[j][k].y;
									rect_sum.width += faceRectLists[j][k].width;
									rect_sum.height += faceRectLists[j][k].height;
									break;
								}
							}
						}
					}
					if (count >= minFaces)
					{
						rect_sum.x = (int)rect_sum.x / count;
						rect_sum.y = (int)rect_sum.y / count;
						rect_sum.width = (int)rect_sum.width / count;
						rect_sum.height = (int)rect_sum.height / count;
						avgFaces.push_back(rect_sum);
					}
				}
				//average detection time
				double timeSum = 0;
				int averageFPS;
				int timeCount = 0;
				for (int i = 0; i < vecNum; i++)
				{
					if (0 != timeList[i])
					{
						timeSum += timeList[i];
						timeCount += 1;
					}
				}
				averageFPS = (int)((1000 * timeCount) / timeSum);

				for (int i = 0; i < avgFaces.size(); i++)
				{
					rectangle(frame, avgFaces[i], Scalar(0, 255, 0), 2);
				}
				
				char tempStr[100];
				sprintf(tempStr, "Average Detection Rate (FPS): %d", averageFPS);

				putText(frame, tempStr, cv::Point(10, 30), FONT_HERSHEY_DUPLEX, 0.7, Scalar(0, 0, 255));
				imshow(window_name, frame);
			}
			else
			{
				/*printf(" --(!) No captured frame -- Break!");
				break; */
				
				continue;
			}			

			int c = waitKey(10);
			if( (char)c == 'c' ) 
			{ 
				break; 
			}
			
			curIdx += 1;
			if (vecNum == curIdx)
				curIdx = 0;
		}
	}
	else
	{
		printf("camera cannot be opened!\n");		
	}
      
	capture.release();
	return 0;
}






