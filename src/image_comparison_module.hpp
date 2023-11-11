#ifndef IMAGE_COMPARISON_MODULE_HPP
#define IMAGE_COMPARISON_MODULE_HPP

#include <QObject>
#include <QImage>

class ImageComparisonModule
{
public:
    static double calculateSimilarity(const QImage &image1, const QImage &image2);
};

#endif // IMAGE_COMPARISON_MODULE_HPP
