#ifdef BSFACEDETECTOR_EXPORTS
#define BSFACEDETECTOR_API __declspec(dllexport)
#else
#define BSFACEDETECTOR_API __declspec(dllimport)
#endif

#include <memory>
//#include "ipp.h"
//#include "ippcore.h"
//#include "ippi.h"
//#include <omp.h>



namespace bsfd
{
	using namespace cv;
	using namespace std;

	class BSFACEDETECTOR_API SimilarRects
	{
	public:
		SimilarRects(double _eps) : eps(_eps) {}
		inline bool operator()(const cv::Rect& r1, const cv::Rect& r2) const
		{
			double delta = eps*(min(r1.width, r2.width) + min(r1.height, r2.height))*0.5;
			return std::abs(r1.x - r2.x) <= delta &&
				std::abs(r1.y - r2.y) <= delta &&
				std::abs(r1.x + r1.width - r2.x - r2.width) <= delta &&
				std::abs(r1.y + r1.height - r2.y - r2.height) <= delta;
		}
		double eps;
	};

	int BSFACEDETECTOR_API calc2RectsIntersectArea(cv::Rect r1, cv::Rect r2);

	struct RectScore
	{
		RectScore(cv::Rect _rect, double _score, double _angle, double _ratio)
		{
			rect = cv::Rect(_rect.x, _rect.y, _rect.width, _rect.height);
			score = _score;
			angle = _angle;
			ratio = _ratio;
		}
		RectScore()
		{
			rect = cv::Rect(0, 0, 0, 0);
			score = 0;
			angle = 0;
			ratio = 0;
		}

		cv::Rect rect;
		double score;
		double ratio;
		double angle;
	};

	class BSFACEDETECTOR_API SimilarRectScores
	{
	public:
		SimilarRectScores(double _eps) : eps(_eps) {}
		inline bool operator()(const RectScore& rs1, const RectScore& rs2) const
		{
			double delta = eps*((std::min)(rs1.rect.width, rs2.rect.width) + (std::min)(rs1.rect.height, rs2.rect.height))*0.5;
			return std::abs(rs1.rect.x - rs2.rect.x) <= delta &&
				std::abs(rs1.rect.y - rs2.rect.y) <= delta &&
				std::abs(rs1.rect.x + rs1.rect.width - rs2.rect.x - rs2.rect.width) <= delta &&
				std::abs(rs1.rect.y + rs1.rect.height - rs2.rect.y - rs2.rect.height) <= delta;
		}
		double eps;
	};

	class QGBEvaluator
	{
	public:
		struct Feature
		{
			Feature();
			Feature(const Feature &obj);	
			inline void calc(int offset, int& bPos) const;
			const uchar *spsPtr_0, *spsPtr_1, *spsPtr_2, *spsPtr_3;
			const uchar* pcPtr;
			Point pc; 				
			Point spoints[4];
			inline void updatePtrs(const Mat& _img);
		};

		QGBEvaluator();
		~QGBEvaluator();

		std::unique_ptr<QGBEvaluator> clone() const;
		int getFeatureType() const { return 1; }	

		bool setImage(const Mat image, Size& _origWinSize);
		void setWindow(Point pt);
		inline void setWindow(int startPosRow, int col)
		{
			offset = startPosRow + col;
		}

		inline void operator()(int featureIdx, int& _bPos) const	
		{
			features[featureIdx].calc(offset, _bPos);
		}	

		inline void operator()(int& _bPos) const	
		{
			fPtr->calc(offset, _bPos);
		}	

		inline void reset()
		{
			fPtr = &(features[0]);			
		}
		inline void increment()
		{			
			++fPtr;
		}
		void load(FILE* m_pFile);

	protected:
		Feature* fPtr; 
		int offset;
		Mat srcImage;		
		vector<Feature>  features;	
		int nFeatures;
		Size origWinSize;
	};

	class CascadeClassifier_cjc
	{
	public:
		CascadeClassifier_cjc();
		CascadeClassifier_cjc(const string& filename);
		CascadeClassifier_cjc(const CascadeClassifier_cjc& obj)	
		{
			data = obj.data;
			featureEvaluator = obj.featureEvaluator->clone();
		}
		virtual ~CascadeClassifier_cjc();

		virtual bool empty() const;
		void detectMultiScale(const Mat& _image,
			vector<RectScore>& _firstObjects,
			vector<RectScore>& _secondObjects,
			CascadeClassifier_cjc& _secondClassifier,
			CascadeClassifier_cjc& _thirdClassifier,
			double _scaleFactor = 1.2,
			int _minNeighbors = 3, int _step = 3, int _threadNum = 2,
			Size _minSize = Size(19, 19),
			Size _maxSize = Size(640, 480));

		int detectWindow(std::unique_ptr<QGBEvaluator>& evaluator, Mat _scaledImage, Point _position, double& _score);

		bool isOldFormatCascade() const;
		virtual Size getOriginalWindowSize() const;
		int getFeatureType() const;
		bool setImage(const Mat&);

		class Data
		{
		public:
			Data(){};
			Data(const Data& obj)	
			{
				isStumpBased = obj.isStumpBased;
				stageType = obj.stageType;
				ncategories = obj.ncategories;
				origWinSize = obj.origWinSize;
			}
			~Data()
			{
				if (!pMainBuffer)
					delete[] pMainBuffer;
			}

			struct DTreeNode
			{
				DTreeNode(){};
				DTreeNode(const DTreeNode& obj)	
				{
					featureIdx = obj.featureIdx;
					threshold = obj.threshold;
					left = obj.left;
					right = obj.right;
				}
				int featureIdx;
				float threshold; 
				int left;
				int right;
			};

			struct DTree
			{
				DTree(){};
				DTree(const DTree& obj)	
				{
					nodeCount = obj.nodeCount;
				}
				int nodeCount;
			};

			struct Stage
			{
				Stage(){};
				Stage(const Stage& obj)	
				{
					first = obj.first;
					ntrees = obj.ntrees;
					threshold = obj.threshold;
				}
				int first;
				int ntrees;
				float threshold;
			};

			void load(FILE* m_pFile, int m_buffSize);	

			bool isStumpBased;
			int stageType;
			int ncategories;
			Size origWinSize;

			char* pMainBuffer;
			Stage* pStages;
			float* pLeaves;
			int* pSubsets;
			DTree* pDTrees;
			DTreeNode* pDTreeNode;
			int nStages;			
		};
		void load(FILE* m_pFile, int m_BuffSize);

	protected:
		bool detectSingleScale(const Mat& image, int stripCount,
			Size processingRectSize, int stripSize, int yStep, double factor,
			vector<RectScore>& firstCandidates, vector<RectScore>& secondCandidates,
			CascadeClassifier_cjc& _secondClassifier, CascadeClassifier_cjc& _thirdClassifier);	
		inline int runAt(std::unique_ptr<QGBEvaluator>& evaluator, int startPosRow, int col, double& _score);	
		friend inline int predictCategoricalStump_GBandQGB(CascadeClassifier_cjc& cascade, std::unique_ptr<QGBEvaluator> &featureEvaluator, double& _score);
		friend inline int predictCategoricalStump_GBandQGB_deep(CascadeClassifier_cjc& cascade, std::unique_ptr<QGBEvaluator> &featureEvaluator, double& _score);
		
		bool detectSingleScale_st(const Mat& image, int yStep, double factor,
			vector<RectScore>& firstCandidates, vector<RectScore>& secondCandidates,
			CascadeClassifier_cjc& _secondClassifier, CascadeClassifier_cjc& _thirdClassifier);	

	protected:
		enum { BOOST = 0 };		
		friend class CascadeClassifierInvoker_RS_2L;	
		bool setImage(std::unique_ptr<QGBEvaluator>& feval, const Mat& image);
		Data data;
		std::unique_ptr<QGBEvaluator> featureEvaluator;
	};

}
