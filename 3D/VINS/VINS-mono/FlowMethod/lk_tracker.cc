#include "lk_tracker.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

LKTracker::LKTracker() {

}

LKTracker::~LKTracker() {

}

int LKTracker::getMatInt(Mat mat, int row, int col) {
	Size size = mat.size();
	if (col < 0 || col >= size.width || 
		  row < 0 || row >= size.height) {
		return 0;
	}
	return mat.at<uchar>(row, col);
}

double LKTracker::getMatDouble(Mat mat, int row, int col) {
	Size size = mat.size();
	if (col < 0 || col >= size.width || 
		  row < 0 || row >= size.height) {
		return 0;
	}
	if (mat.type() == CV_64F) {
		return mat.at<double>(row, col);
	} else {
		return (double)mat.at<uchar>(row, col);
	}
}

double LKTracker::getMatDouble(Mat mat, double row, double col) {
	Size size = mat.size();
	if (col < 0 || col >= size.width || 
		  row < 0 || row >= size.height) {
		return 0;
	}
	int floorRow = floor(row);
	int floorCol = floor(col);
	double fracRow = row - floorRow;
	double fracCol = col - floorCol;
	int ceilRow = floorRow + 1;
	int ceilCol = floorCol + 1;

	return ((1.0 - fracRow) * (1.0 - fracCol) * getMatDouble(mat, floorRow, floorCol) + 
		(fracRow * (1.0 - fracCol) * getMatDouble(mat, ceilRow, floorCol)) + 
		((1.0 - fracRow) * fracCol * getMatDouble(mat, floorRow, ceilCol)) +
		(fracRow * fracCol * getMatDouble(mat, ceilRow, ceilCol))
	);
}

void LKTracker::lowpassFilter(InputArray src, OutputArray dst) {
  Mat srcMat = src.getMat();
	int dstWidth = srcMat.size().width / 2;
	int dstHeight = srcMat.size().height / 2;
	// dst.create(Size(dstWidth, dstHeight), srcMat.type());
	dst.create(Size(dstWidth, dstHeight), CV_64F);
	Mat dstMat = dst.getMat();
	for (int x = 0; x < dstHeight; x++) {
		for (int y = 0; y < dstWidth; y++) {
			double val = 0;
			val += getMatInt(srcMat, 2*x, 2*y) * 0.25;
			val += getMatInt(srcMat, 2*x-1, 2*y) * 0.125;
			val += getMatInt(srcMat, 2*x+1, 2*y) * 0.125;
			val += getMatInt(srcMat, 2*x, 2*y-1) * 0.125;
			val += getMatInt(srcMat, 2*x, 2*y+1) * 0.125;
			val += getMatInt(srcMat, 2*x-1, 2*y-1) * 0.0625;
			val += getMatInt(srcMat, 2*x+1, 2*y-1) * 0.0625;
			val += getMatInt(srcMat, 2*x-1, 2*y+1) * 0.0625;
			val += getMatInt(srcMat, 2*x+1, 2*y+1) * 0.0625;
			// dstMat.at<uchar>(x, y) = (uchar)val;
			dstMat.at<double>(x, y) = val;
		}
	}
}

vector<Mat> LKTracker::buildPyramid(InputArray src) {
	vector<Mat> layers;
	Mat currLayer = src.getMat();
	layers.push_back(currLayer);
	for (int i = 0; i < this->maxPyramidLayer; i++) {
		Mat nextLayer;
		this->lowpassFilter(currLayer, nextLayer);
		layers.push_back(nextLayer);
		currLayer = nextLayer;
	}
	return layers;
}

Mat LKTracker::calcGradientMatrix(InputArray frame, Point2f p) {
	Mat frameMat = frame.getMat();
	Mat mat(2, 2, CV_64F, Scalar(0));
	int pRow = p.y, pCol = p.x;
	for (int x = pRow - wx; x <= pRow + wx; x++) {
		for (int y = pCol - wy; y <= pCol + wy; y++) {
			double ix = (getMatDouble(frameMat, x + 1, y) - getMatDouble(frameMat, x - 1, y)) / 2.0;
			double iy = (getMatDouble(frameMat, x, y + 1) - getMatDouble(frameMat, x, y - 1)) / 2.0;
			mat.at<double>(0, 0) += ix * ix;
			mat.at<double>(0, 1) += ix * iy;
			mat.at<double>(1, 0) += ix * iy;
			mat.at<double>(1, 1) += iy * iy;
		}
	}
	return mat;
}

Mat LKTracker::calcMismatchVector(InputArray preFrame, InputArray curFrame, Point2f p, Mat g, Mat v) {
	Mat preMat = preFrame.getMat();
	Mat curMat = curFrame.getMat();
	Mat mismatchVector(2, 1, CV_64F, Scalar(0));
	int pRow = p.y, pCol = p.x;
	for (int x = pRow - wx; x <= pRow + wx; x++) {
		for (int y = pCol - wy; y <= pCol + wy; y++) {
			double curX = 1.0 * x + g.at<double>(0, 0) + v.at<double>(0, 0);
			double curY = 1.0 * y + g.at<double>(1, 0) + v.at<double>(1, 0);
			double ix = (getMatDouble(preMat, x + 1, y) - getMatDouble(preMat, x - 1, y)) / 2.0;
			double iy = (getMatDouble(preMat, x, y + 1) - getMatDouble(preMat, x, y - 1)) / 2.0;
			double diff = getMatDouble(preMat, x, y) - getMatDouble(curMat, curX, curY);
			mismatchVector.at<double>(0, 0) += diff * ix;
			mismatchVector.at<double>(1, 0) += diff * iy;
		}
	}
	return mismatchVector;
}

double LKTracker::calcResidual(Mat mat) {
	return sqrt(pow(mat.at<double>(0, 0), 2) + pow(mat.at<double>(1, 0), 2));
}

bool LKTracker::isOpticalFlowValid(Mat of) {
	return (abs(of.at<double>(0, 0)) <= 50 && abs(of.at<double>(0, 0)) >= 1 
		&& abs(of.at<double>(1, 0)) <= 50 && abs(of.at<double>(1, 0)) >= 1);
}

vector<TrackedPoint> LKTracker::track(InputArray preFrame, InputArray curFrame, vector<Point> keyPoints) {
	vector<Mat> prePyramid = this->buildPyramid(preFrame);
	vector<Mat> curPyramid = this->buildPyramid(curFrame);
	vector<TrackedPoint> tPoints;
	for (unsigned int i = 0; i < keyPoints.size(); i++) {
		Mat g(2, 1, CV_64F, Scalar(0));
		Point srcPoint = keyPoints[i];
		bool isValid = true;
		for (int j = this->maxPyramidLayer - 1; j > 0; j--) {
			Mat preMat = prePyramid[j];
			Mat curMat = curPyramid[j];
			Point2f prePoint;
			prePoint.x = 1.0 * srcPoint.x / pow(2.0, j);
			prePoint.y = 1.0 * srcPoint.y / pow(2.0, j);
			Mat gradient = calcGradientMatrix(preMat, prePoint);
			Mat gradientInv = gradient.inv();
			Mat v(2, 1, CV_64F, Scalar(0));
			int iterCount = 0;
			double residual = 1;
			while(iterCount < this->maxIteration && residual > this->opticalflowResidual) {
				iterCount++;
				Mat mismatch = calcMismatchVector(preMat, curMat, prePoint, g, v);
				Mat delta = gradientInv * mismatch;
				v += delta;
				residual = calcResidual(delta);
			}

			if (iterCount >= this->maxIteration) {
				isValid = false;
				break;
			}

			if (j == 0) {
				g = g + v;
			} else {
				g = 2 * (g + v);
			}
		}

		if (isValid && isOpticalFlowValid(g)) {
			Point dstPoint;
			dstPoint.x = (int)(srcPoint.x + g.at<double>(1, 0));
			dstPoint.y = (int)(srcPoint.y + g.at<double>(0, 0));
			TrackedPoint tPoint(dstPoint, g);
			tPoints.push_back(tPoint);
		}
	}
	return tPoints;
}

double LKTracker::calcHarrisResponse(Mat gradient, double alpha) {
	double A = gradient.at<double>(0, 0);
	double B = gradient.at<double>(0, 1);
	double C = gradient.at<double>(1, 1);
	double det = A * C - B * B;
	double trace = A + C;
	return det - trace * trace * alpha;
}

vector<TrackedPoint> LKTracker::trackAll(InputArray preFrame, InputArray curFrame, double qualityLevel) {
  Mat preMat = preFrame.getMat();
	vector<Point> keyPoints;
	goodFeaturesToTrack(preFrame, keyPoints, 1000, 0.01, 10, Mat());
	return track(preFrame, curFrame, keyPoints);
}
