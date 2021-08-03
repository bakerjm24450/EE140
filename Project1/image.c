/*
 * Functions for image processing. 
 * 
 * COMPLETE THE FUNCTIONS BELOW.
 *
 * Be sure to add a block of comments for each function, as
 * specified in the assignment.
 */
#include <stdio.h>
#include "image.h"

// Dims the image by reducing each pixel value by half.
// Input: image to process
// Returns nothing, but modifies image
void dim(unsigned char image[512][512])
{
	for (int r = 0; r < 512; ++r)
	{
		for (int c = 0; c < 512; ++c)
		{
			// reduce each pixel by half
			image[r][c] = image[r][c] / 2;
		}
	}
}

void inverse(unsigned char image[512][512])
{
	// FIXME: complete this function
}

void rotate(unsigned char image[512][512])
{
	// FIXME: complete this function
}

void lowpass(unsigned char image[512][512])
{
	// FIXME: complete this function
}

void highpass(unsigned char image[512][512])
{
	// FIXME: complete this function
}

void median(unsigned char image[512][512])
{
	// FIXME: complete this function
}

/*
 * The following functions are for extra credit.
 */
void zoom(unsigned char image[512][512])
{
	// FIXME: complete this function for extra credit
}

void tile(unsigned char image[512][512])
{
	// FIXME: complete this function for extra credit
}

void edge(unsigned char image[512][512])
{
	// FIXME: complete this function for extra credit
}

void threshold(unsigned char image[512][512])
{
	// FIXME: complete this function for extra credit
}

void histogram(unsigned char image[512][512])
{
	// FIXME: complete this function for extra credit
}
