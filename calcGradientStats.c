/*
 * Author: Christoph Steefel
 * Date: December 12, 2015
 * Purpose: This file contains the gradient calculation code, which creates
 * a gradient array, as well as calculates the standard Deviation and
 * mean gradients.
 */

#include "edgeInfo.h"
#include <string.h>

#define RED 0
#define GREEN 1
#define BLUE 2

/*
 * Function to calculate the gradients across the array, requires the base
 * array, info about the type of the base array, and the width and height
 * of the base array.
 *
 * Returns: Struct containing a pointer to the gradient array, statisitics
 * about the gradient array, and the size of the array.
 */
gradientData calcGradients(void ** baseArr, long width, long height,
    char* type)  {
  // initial variables
  double mean = 0;
  double stdDev = 0;
  gradientData result;
  // RGBA array type
  if (!strcmp(type, "RGBA")) {
    // array traversal pointer.
    void * traversal = *baseArr;
    //counter for the loop
    int counter = 0;
    while (counter < (width - 1) * (height - 1)){
      // convert all values to char arrays, with entries R, G, B, and A
      char curr[4], eastNeighbor[4], southNeighbor[4];
      // Copy the data into char arrays for processing
      memcpy(curr, traversal, 1);
      memcpy(eastNeighbor, traversal + 1, 1);
      memcpy(southNeighbor, traversal + width, 1);
      //add eastern gradient
      mean += (+(curr[RED] - eastNeighbor[RED])) +
              (+(curr[GREEN] - eastNeighbor[GREEN])) +
              (+(curr[BLUE] - eastNeighbor[BLUE])) /
              ((width - 1) * (height - 1));
      //add southern gradient
      mean += (+(curr[RED] - southNeighbor[RED])) +
              (+(curr[GREEN] - southNeighbor[GREEN])) +
              (+(curr[BLUE] - southNeighbor[BLUE])) /
              ((width - 1) * (height - 1));
      traversal++;
      counter++;
    }
    result.mean = mean;
  }
  return result;
}


