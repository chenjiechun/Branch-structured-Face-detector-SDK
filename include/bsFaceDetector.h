// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BSFACEDETECTOR_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BSFACEDETECTOR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.


//#pragma once

#ifdef BSFACEDETECTOR_EXPORTS
#define BSFACEDETECTOR_API __declspec(dllexport)
#else
#define BSFACEDETECTOR_API __declspec(dllimport)
#endif

#include <map>
#include <deque>
#include <memory>
#include <algorithm>
#include "face_detection.h"
#include "classifier.h"
using namespace seeta;



namespace bsfd
{	
	class BSFACEDETECTOR_API BsFaceDetector
	{
	public:
		BsFaceDetector();
		int loadModels(const char* fileName, const char* _surf_mlp_name);
		void detectFaces(cv::Mat& frame, vector<cv::Rect>& _detectedFaces);
		void setScaleFactor(float _scaleFactor);
		void setStep(int _step);
		void setThreadNum(int _threadNum);
		void setMinFace(cv::Size _minFace);
		void setMaxFace(cv::Size _maxFace);
		void setDetThreashold(float _threshold);

	private:
		CascadeClassifier_cjc face_cascades[3];
		FaceDetection seeta_detector;
		float m_scaleFactor;
		int m_step;
		int m_threadNum;
		cv::Size m_minFace;
		cv::Size m_maxFace;
		float m_detThreshold;
		void getBuffSizes(const char* fileName, int m_buffSize[]);
	};


}

