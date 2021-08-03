#ifndef IMAGE_H
#define IMAGE_H

/*
 * Struct to represent a pixel
 */
typedef struct {
	unsigned char r;				// red component
	unsigned char g;				// green
	unsigned char b;				// blue
} Pixel;


/*
 * Struct to represent an image. We keep the image height and width, along
 * with an array of pixels.
 */
typedef struct {
	int width;						// width of image in pixels
	int height;						// height of image in pixels
	Pixel *pixels;					// array of pixels
} Image;


/*
 * Function prototypes
 */

/*
 * Read an image from a PPM file.
 * Input: filename = name of file containing the image
 *        image = pointer to Image struct to hold the image
 * Returns: 0 on success, non-zero if an error occurs
 */
int readImage(char *filename, Image *image);

void grayscale(Image *image);
void laplacian(Image *image);
void rotate(Image *image, double angle);
void reduceSize(Image *image);
void posterize(Image *image);
void grayscaleRed(Image *image);

#endif