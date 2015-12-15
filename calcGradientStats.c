/*
 * Author: Christoph Steefel
 * Date: December 12, 2015
 * Purpose: This file contains the gradient calculation code, which creates
 * a resulting edge array, as well as calculates the standard Deviation and
 * mean gradients.
 */

#include "edgeInfo.h"
#include <string.h>
#include <math.h>

#define RED 0
#define GREEN 1
#define BLUE 2
#define SQUARE(x) pow(x, 2)


/*
 * Function to calculate the gradients across the array, requires the base
 * array, info about the type of the base array, and the width and height
 * of the base array.
 *
 * Returns: Struct containing a pointer to the gradient array, as well as a
 * mean gradient value.
 */
gradientData * calcGradientMeans(gradientData * data) {
  // initial variables
  double mean = 0;
  // RGBA array type
  if (!strcmp(data->type, "RGBA")) {
    // array traversal pointer.
    void * traversal = data->baseArr;
    //counter for the loop
    int counter = 0;
    while (counter < (data->width - 1) * (data->height - 1)){
      // convert all values to char arrays, with entries R, G, B, and A
      char curr[4], eastNeighbor[4], southNeighbor[4];
      // Copy the data into char arrays for processing
      memcpy(curr, traversal, 1);
      memcpy(eastNeighbor, traversal + 1, 1);
      memcpy(southNeighbor, traversal + data->width, 1);
      //add eastern gradient
      mean += (+(curr[RED] - eastNeighbor[RED])) +
              (+(curr[GREEN] - eastNeighbor[GREEN])) +
              (+(curr[BLUE] - eastNeighbor[BLUE])) /
              ((data->width - 1) * (data->height - 1));
      //add southern gradient
      mean += (+(curr[RED] - southNeighbor[RED])) +
              (+(curr[GREEN] - southNeighbor[GREEN])) +
              (+(curr[BLUE] - southNeighbor[BLUE])) /
              ((data->width - 1) * (data->height - 1));
      traversal++;
      counter++;
    }
    data->mean = mean;
  }
  return data;
}



/*
 * Function to calculate standard deviation, assumes the mean is correct for
 * the raster data.
 *
 * Returns the original array in the gradientData struct, along with a stdDev
 * value.
 */
gradientData * calcStandardDeviation(gradientData * data) {
  double variance = 0;
  if (!strcmp(data->type, "RGBA")) {
    // array traversal pointer.
    void * traversal = data->baseArr;
    //counter for the loop
    int counter = 0;
    while (counter < (data->width - 1) * (data->height - 1)){
      // convert all values to char arrays, with entries R, G, B, and A
      char curr[4], eastNeighbor[4], southNeighbor[4];
      // Copy the data into char arrays for processing
      memcpy(curr, traversal, 1);
      memcpy(eastNeighbor, traversal + 1, 1);
      memcpy(southNeighbor, traversal + data->width, 1);
      //add eastern gradient
      variance += SQUARE((+(curr[RED] - eastNeighbor[RED])) +
              (+(curr[GREEN] - eastNeighbor[GREEN])) +
              (+(curr[BLUE] - eastNeighbor[BLUE]))- data->mean) /
              ((data->width - 1) * (data->height - 1));
      //add southern gradient
      variance += SQUARE((+(curr[RED] - southNeighbor[RED])) +
              (+(curr[GREEN] - southNeighbor[GREEN])) +
              (+(curr[BLUE] - southNeighbor[BLUE])) - data->mean) /
              ((data->width - 1) * (data->height - 1));
      traversal++;
      counter++;
    }
    data->stdDev = sqrt(variance);
  }
  return data;
}
