#include "CLMF_SDK_Import.h"

int main(int argc, char *argv[])
{
	cv::Mat img = cv::imread("housecorner.bmp", 1);
	if (argc >= 2) img = cv::imread(argv[1], 1);
	
	if (img.empty()) fprintf(stderr, "No input image!\n");

	cv::Mat imgOut;
	// Ex1: filter color image with CLMF-1
	FilterImageWithCLMF(1, 1, img, img, imgOut, 9, 25.0, 0.01, 0);

	cv::imshow("Original_Image", img);
	cv::imshow("Result_Show", imgOut);
	cv::imwrite("Processed_Result.png", imgOut);

	// Ex2: save out the cross map result
	cv::Mat_<cv::Vec3b> cmUD, cmLR;
	int maxRadius = 15;
	SaveOutCrossSupportMap(img, cmUD, cmLR, maxRadius, 25.0, 0);
	cmUD.convertTo(cmUD, CV_8UC3, 255.0/maxRadius);
	cmLR.convertTo(cmLR, CV_8UC3, 255.0/maxRadius);
	cv::imwrite("CrossMap-LeftRight.png", cmLR);
	cv::imwrite("CrossMap-UpDown.png", cmUD);
	cv::imshow("CrossMap-Left-Right", cmLR);
	cv::imshow("CrossMap-Up-Down", cmUD);

	// Ex3: filter using cost slice
	// same usage as Ex1, please refer CLMF_SDK_Import.h for detail instruction

	cv::waitKey(0);
	return 0;
}