#include "image_comparison_module.hpp"

double ImageComparisonModule::calculateSimilarity(const QImage &image1, const QImage &image2)
{
    // Implement your algorithm to calculate similarity between two images
    // Placeholder for similarity calculation
    if (image1.size() != image2.size())
        return 0.0;

    // Simple pixel-by-pixel comparison algorithm as a placeholder
    double similarPixels = 0.0;
    for (int y = 0; y < image1.height(); ++y)
    {
        for (int x = 0; x < image1.width(); ++x)
        {
            if (image1.pixel(x, y) == image2.pixel(x, y))
            {
                ++similarPixels;
            }
        }
    }

    return (similarPixels / (image1.width() * image1.height())) * 100.0;
}
