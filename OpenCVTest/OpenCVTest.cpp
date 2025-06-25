// OpenCVTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/logger.hpp>

#include <map>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
using namespace cv;


int main()
{
    // define map for depth() values
    map<int, std::string> depth_type_to_description_map;
    depth_type_to_description_map[0] = "CV_8U - 8-bit unsigned integers ( 0..255 )";
    depth_type_to_description_map[1] = "CV_8S - 8-bit signed integers ( -128..127 )";
    depth_type_to_description_map[2] = "CV_16U - 16-bit unsigned integers ( 0..65535 )";
    depth_type_to_description_map[3] = "CV_16S - 16-bit signed integers ( -32768..32767 )";
    depth_type_to_description_map[4] = "CV_32S - 32-bit signed integers ( -2147483648..2147483647 )";
    depth_type_to_description_map[5] = "CV_32F - 32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )";
    depth_type_to_description_map[6] = "CV_64F - 64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )";
    depth_type_to_description_map[7] = "CV_16F - 16-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )";


    map<string, int> rgb_map;
    rgb_map["B"] = 0;
    rgb_map["G"] = 1;
    rgb_map["R"] = 2;
    rgb_map["b"] = 0;
    rgb_map["g"] = 1;
    rgb_map["r"] = 2;


    // disable OpenCV logging
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    std::cout << "Hello World!\n";

    string image_path = "bar\\cocosette.jpg";
    if ( ! fs::exists(image_path))
    {
        std::cerr << "Could not read the image: " << image_path << std::endl;
        return 2;
    }

    fs::path canonical = fs::canonical(image_path);
    string canonical_path = canonical.string();

    Mat img = imread(canonical_path, /*IMREAD_COLOR*/ IMREAD_UNCHANGED);

    if (img.empty())
    {
        std::cout << "Could not read the image: " << canonical_path << std::endl;
        return 1;
    }

    int img_depth = img.depth();
    int img_channel_count = img.channels();

    std::cout << "Image size (r x c): " << img.rows << " x " << img.cols << std::endl;

    std::cout << "Image channels: " << img_channel_count << std::endl;

    std::cout << "Image depth_type[" << img_depth << "]: " << depth_type_to_description_map[img_depth] << std::endl;

    std::cout << "Image type: " << img.type() << std::endl;

    // Show the original image
    string window_title = canonical_path;

    imshow(window_title, img);

    // create different images for each channel
    // Split the image into different channels
    vector<Mat> rgbChannels(img_channel_count);
    split(img, rgbChannels);

    // Show individual channels
    Mat g, fin_img;
    g = Mat::zeros(Size(img.cols, img.rows), CV_MAKETYPE(img_depth, 1));

    // Showing Red Channel
    // G and B channels are kept as zero matrix for visual perception
    {
        vector<Mat> channels;
        channels.push_back(g);
        channels.push_back(g);
        channels.push_back(rgbChannels[rgb_map["R"]]);

        /// Merge the three channels
        merge(channels, fin_img);
        namedWindow("R", 1); imshow("R", fin_img);
    }

    // Showing Green Channel
    {
        vector<Mat> channels;
        channels.push_back(g);
        channels.push_back(rgbChannels[rgb_map["G"]]);
        channels.push_back(g);
        merge(channels, fin_img);
        namedWindow("G", 1); 
        imshow("G", fin_img);
    }

    // Showing Blue Channel
    {
        vector<Mat> channels;
        channels.push_back(rgbChannels[rgb_map["B"]]);
        channels.push_back(g);
        channels.push_back(g);
        merge(channels, fin_img);
        namedWindow("B", 1); 
        imshow("B", fin_img);
    }


    // Showing Red Channel as gray shades
    {
        vector<Mat> channels;
        channels.push_back(rgbChannels[rgb_map["R"]]);
        channels.push_back(rgbChannels[rgb_map["R"]]);
        channels.push_back(rgbChannels[rgb_map["R"]]);

        /// Merge the three channels
        merge(channels, fin_img);
        namedWindow("R -> B&W", 1); imshow("R -> B&W", fin_img);
    }

    // Showing Green Channel as gray shades
    {
        vector<Mat> channels;
        channels.push_back(rgbChannels[rgb_map["G"]]);
        channels.push_back(rgbChannels[rgb_map["G"]]);
        channels.push_back(rgbChannels[rgb_map["G"]]);
        merge(channels, fin_img);
        namedWindow("G -> B&W", 1);
        imshow("G -> B&W", fin_img);
    }

    // Showing Blue Channel as gray shades
    {
        vector<Mat> channels;
        channels.push_back(rgbChannels[rgb_map["B"]]);
        channels.push_back(rgbChannels[rgb_map["B"]]);
        channels.push_back(rgbChannels[rgb_map["B"]]);
        merge(channels, fin_img);
        namedWindow("B -> B&W", 1);
        imshow("B -> B&W", fin_img);
    }

    // Displaying images from the channel data
    namedWindow("RGB[R] -> B&W", 1);
    imshow("RGB[R] -> B&W", rgbChannels[rgb_map["R"]]);

    namedWindow("RGB[G] -> B&W", 1);
    imshow("RGB[G] -> B&W", rgbChannels[rgb_map["G"]]);

    namedWindow("RGB[B] -> B&W", 1);
    imshow("RGB[B] -> B&W", rgbChannels[rgb_map["B"]]);

    // Generating B&W based on RGB values
    // avg = (R + G + B)/3
    // distance = SQRT(R^2 + G^2 + B^2)/SQRT(3)
    // luminance = 0.2989 * R + 0.5870 * G + 0.1140 * B 
    //              The coefficients used to calculate grayscale values in rgb2gray are identical to those used to calculate 
    //              luminance (E'y) in Rec.ITU-R BT.601-7 after rounding to 3 decimal places.
    // darkness = SQRT( (Depth - R)^2 + (Depth - G)^2 + (Depth - B)^2

    int k = waitKey(0); // Wait for a keystroke in the window

    if (k == 's')
    {
        imwrite("bar\\starry_night.jpeg", img);
    }

    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
