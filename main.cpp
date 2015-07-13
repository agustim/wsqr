#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zbar.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;
using namespace zbar;

int main(int argc, char **argv) {
    int cam_idx = 0;

    if (argc == 2) {
        cam_idx = atoi(argv[1]);
    }

    VideoCapture cap(cam_idx);
    if (!cap.isOpened()) {
        cerr << "Could not open camera." << endl;
        exit(EXIT_FAILURE);
    }
    //cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    //namedWindow("captured", CV_WINDOW_AUTOSIZE);

    // Create a zbar reader
    ImageScanner scanner;

    // Configure the reader
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    for (;;) {
        // Capture an OpenCV frame
        cv::Mat frame, frame_grayscale;
        cap >> frame;

        // Convert to grayscale
        cvtColor(frame, frame_grayscale, CV_BGR2GRAY);

        // Obtain image data
        int width = frame_grayscale.cols;
        int height = frame_grayscale.rows;
        uchar *raw = (uchar *)(frame_grayscale.data);

        // Wrap image data
        Image image(width, height, "Y800", raw, width * height);

        // Scan the image for barcodes
        //int n = scanner.scan(image);
        scanner.scan(image);

        // Extract results
        int counter = 0;
        for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) {

            // do something useful with results
            //cout << symbol->get_data() << endl;
            printf("%s\n", symbol->get_data().c_str());
            return 0;

            //cout << "Location: (" << symbol->get_location_x(0) << "," << symbol->get_location_y(0) << ")" << endl;
            //cout << "Size: " << symbol->get_location_size() << endl;

            // Draw location of the symbols found
  /*
            if (symbol->get_location_size() == 4) {
                //rectangle(frame, Rect(symbol->get_location_x(i), symbol->get_location_y(i), 10, 10), Scalar(0, 255, 0));
                line(frame, Point(symbol->get_location_x(0), symbol->get_location_y(0)), Point(symbol->get_location_x(1), symbol->get_location_y(1)), Scalar(0, 255, 0), 2, 8, 0);
                line(frame, Point(symbol->get_location_x(1), symbol->get_location_y(1)), Point(symbol->get_location_x(2), symbol->get_location_y(2)), Scalar(0, 255, 0), 2, 8, 0);
                line(frame, Point(symbol->get_location_x(2), symbol->get_location_y(2)), Point(symbol->get_location_x(3), symbol->get_location_y(3)), Scalar(0, 255, 0), 2, 8, 0);
                line(frame, Point(symbol->get_location_x(3), symbol->get_location_y(3)), Point(symbol->get_location_x(0), symbol->get_location_y(0)), Scalar(0, 255, 0), 2, 8, 0);
            }
*/
            // Get points
            /*for (Symbol::PointIterator point = symbol.point_begin(); point != symbol.point_end(); ++point) {
                cout << point << endl;
            } */
            counter++;
        }

        // Show captured frame, now with overlays!
        //imshow("captured", frame);

        // clean up
        image.set_data(NULL, 0);

        waitKey(30);
    }

    return 0;
}
