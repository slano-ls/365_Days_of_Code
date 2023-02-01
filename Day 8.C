#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    // Load image
    Mat image = imread("example.jpg");
    // Resize image
    resize(image, image, Size(640, 480));
    // Convert to 8-bit 3-channel image
    cvtColor(image, image, COLOR_BGR2Lab);
    // Flatten image
    Mat reshaped = image.reshape(1, image.cols * image.rows);
    // Convert to 32-bit floating point
    reshaped.convertTo(reshaped, CV_32F);
    // Perform k-means clustering
    Mat labels, centers;
    kmeans(reshaped, 5, labels, TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);
    // Convert centers back to 8-bit 3-channel image
    centers.convertTo(centers, CV_8UC3);
    // Convert back to BGR
    cvtColor(centers, centers, COLOR_Lab2BGR);
    // Show extracted colors
    namedWindow("Colors", WINDOW_NORMAL);
    imshow("Colors", centers);
    waitKey();
    return 0;
}
