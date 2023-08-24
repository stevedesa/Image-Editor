/** **************************************************************************
 * @file
 ****************************************************************************/
 /** **************************************************************************
  * @mainpage Take Home Programming Exam 1
  *
  * @section course_section Course Information
  *
  * @author Steve Nathan de Sa
  *
  * @par Professor:
  *         Roger Schrader
  *
  * @par Course:
  *         CSC215 - M01 - Programming Techniques
  *
  * @par Location:
  *         Classroom Building - CB-327
  *
  * @date Due: March 3, 2023
  *
  * @section program_section Program Information
  *
  * @details
  * The program reads in a netPBM type image file, in either ascii
  * or binary format, as per the type of image. 
  * 
  * The program has 6 options to make changes to the image, ie. flip
  * image over x axis, flip image over y axis, rotate image clockwise,
  * rotate image counterclockwise, make image gray and make image antique.
  * 
  * After altering the image, the modified image data is stored in a new,
  * unique file as specified by user, in either ascii or binary format.
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      none - a straight compile and link with no external libraries.
  *
  * @par Usage:
    @verbatim
    c:\> thpe11.exe [option] --outputtype basename image.ppm

         Output Type      Output Description
        --ascii      integer text numbers will be written for the data
        --binary     integer number will be written in binary form

         Option Code      Option Description
        --flipX      Flip the image on the X axis
        --flipY      Flip the image on the Y axis
        --rotateCW   Rotate the image clockwise
        --rotateCCW  Rotate the image counter clockwise
        --grayscale  Convert image to grayscale
        --sepia      Antique a color image
    @endverbatim
  *
  * @par Modifications and Development Timeline:
  * This is a link to my Gitlab Repository of THPE1. To view <a target="_blank"
  * href="https://gitlab.cse.sdsmt.edu/101124071/csc215s23programs/-/commits/main/thpe11">click here.</a>
  *
  *****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#ifndef __NETPBM__H__
#define __NETPBM__H__

/** **********************************************************************
* @author Steve Nathan de Sa
*
* @par Description
* Unsigned char is simplified as pixel, for easier operation, by typedef
************************************************************************/
typedef unsigned char pixel;

/** **********************************************************************
* @author Steve Nathan de Sa
*
* @par Description
* Structure that stores image data
************************************************************************/
struct image
{
    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains image magic number.
    ************************************************************************/
    string magicNumber;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains image comment.
    ************************************************************************/
    string comment;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * Integer that contains image rows.
    ************************************************************************/
    int rows;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * Integer that contains image columns.
    ************************************************************************/
    int cols;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * 2d dynamic array of type pixel that contains Red pixels.
    ************************************************************************/
    pixel** redGray;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * 2d dynamic array of type pixel that contains Green pixels.
    ************************************************************************/
    pixel** green;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * 2d dynamic array of type pixel that contains Blue pixels.
    ************************************************************************/
    pixel** blue;
};

void openIPFile(ifstream& file, string filename);
void openOPFile(ofstream& file, string filename);

bool readImage(ifstream& fin, image& img);
void writeImage(ofstream& fout, image& img, string filename);

void allocarray(pixel**& array, int rows, int columns);
void freearray(pixel**& array, int rows);

void flipX(image& img, string type);
void flipY(image& img, string type);

void rotateCW(image& img, string type);
void rotateCCW(image& img, string type);

void grayscale(image& img, string type);
void sepia(image& img, string type);

int edit(double value);
void error(string type);

#endif