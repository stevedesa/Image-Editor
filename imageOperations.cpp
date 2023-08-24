/** **************************************************************************
 * @file
 ****************************************************************************/
#include "netPBM.h"

 /** ***************************************************************************
  * @author Steve Nathan de Sa
  *
  * @par Description
  * This function flips the image on its x-axis and changes magic number according
  * to the type of output file needed.
  *
  * @param[in, out]  img - defined image structure to obtain data from.
  * @param[in]       type - contains type of output file needed.
  *
  * @par Example
  * @verbatim
    string type = "-ascii";
    string output = "output";
    string input = "input";

    ifstream fin;
    ofstream fout;
    image img;

    openIPFile(fin, input);

    if (readImage(fin, img))
    {
        flipX(img, type);
        writeImage(fout, img, output);
    }
    @endverbatim
  *****************************************************************************/
void flipX(image& img, string type)
{
    int i,j;

    if (type == "--ascii")
    {
        img.magicNumber = "P3";
    }
    else if (type == "--binary")
    {
        img.magicNumber = "P6";
    }
    else
    {
        error("output");
    }

    for (i = 0; i < img.cols; i++)
    {
        for (j = 0; j < img.rows / 2; j++)
        {
            swap(img.redGray[j][i], img.redGray[img.rows - j - 1][i]);
            swap(img.blue[j][i], img.blue[img.rows - j - 1][i]);
            swap(img.green[j][i], img.green[img.rows - j - 1][i]);
        }
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function flips the image on its y-axis and changes magic number according
 * to the type of output file needed.
 *
 * @param[in, out]  img - defined image structure to obtain data from.
 * @param[in]       type - contains type of output file needed.
 *
 * @par Example
 * @verbatim
   string type = "-ascii";
   string output = "output";
   string input = "input";

   ifstream fin;
   ofstream fout;
   image img;

   openIPFile(fin, input);

   if (readImage(fin, img))
   {
       flipY(img, type);
       writeImage(fout, img, output);
   }
   @endverbatim
 *****************************************************************************/
void flipY(image& img, string type)
{
    int i, j;

    if (type == "--ascii")
    {
        img.magicNumber = "P3";
    }
    else if (type == "--binary")
    {
        img.magicNumber = "P6";
    }
    else
    {
        error("output");
    }

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols / 2; j++)
        {
            swap(img.redGray[i][j], img.redGray[i][img.cols - j - 1]);
            swap(img.blue[i][j], img.blue[i][img.cols - j - 1]);
            swap(img.green[i][j], img.green[i][img.cols - j - 1]);
        }
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function rotates the image clockwise and changes magic number according
 * to the type of output file needed.
 *
 * @param[in, out]  img - defined image structure to obtain data from.
 * @param[in]       type - contains type of output file needed.
 *
 * @par Example
 * @verbatim
   string type = "-ascii";
   string output = "output";
   string input = "input";

   ifstream fin;
   ofstream fout;
   image img;

   openIPFile(fin, input);

   if (readImage(fin, img))
   {
       rotateCW(img, type);
       writeImage(fout, img, output);
   }
   @endverbatim
 *****************************************************************************/
void rotateCW(image& img, string type)
{
    int i, j;

    if (type == "--ascii")
    {
        img.magicNumber = "P3";
    }
    else if (type == "--binary")
    {
        img.magicNumber = "P6";
    }
    else
    {
        error("output");
    }

    pixel** tR;
    pixel** tG;
    pixel** tB;

    allocarray(tR, img.cols, img.rows);
    allocarray(tG, img.cols, img.rows);
    allocarray(tB, img.cols, img.rows);

    for (i = 0; i < img.cols; i++)
    {
        for (j = 0; j < img.rows; j++)
        {
            tR[i][j] = img.redGray[img.rows - j - 1][i];
            tG[i][j] = img.green[img.rows - j - 1][i];
            tB[i][j] = img.blue[img.rows - j - 1][i];
        }
    }

    freearray(img.redGray, img.rows);
    freearray(img.green, img.rows);
    freearray(img.blue, img.rows);

    allocarray(img.redGray, img.cols, img.rows);
    allocarray(img.green, img.cols, img.rows);
    allocarray(img.blue, img.cols, img.rows);

    swap(img.cols, img.rows);

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            img.redGray[i][j] = tR[i][j];
            img.green[i][j] = tG[i][j];
            img.blue[i][j] = tB[i][j];
        }
    }

    freearray(tR, img.rows);
    freearray(tG, img.rows);
    freearray(tB, img.rows);
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function rotates the image counter clockwise and changes magic number 
 * according to the type of output file needed.
 *
 * @param[in, out]  img - defined image structure to obtain data from.
 * @param[in]       type - contains type of output file needed.
 *
 * @par Example
 * @verbatim
   string type = "-ascii";
   string output = "output";
   string input = "input";

   ifstream fin;
   ofstream fout;
   image img;
 
   openIPFile(fin, input);

   if (readImage(fin, img))
   {
       rotateCCW(img, type);
       writeImage(fout, img, output);
   }
   @endverbatim
 *****************************************************************************/
void rotateCCW(image& img, string type)
{
    int i,j;

    if (type == "--ascii")
    {
        img.magicNumber = "P3";
    }
    else if (type == "--binary")
    {
        img.magicNumber = "P6";
    }
    else
    {
        error("output");
    }

    pixel** tR;
    pixel** tG;
    pixel** tB;

    allocarray(tR, img.cols, img.rows);
    allocarray(tG, img.cols, img.rows);
    allocarray(tB, img.cols, img.rows);

    for (i = 0; i < img.cols; i++)
    {
        for (j = 0; j < img.rows; j++)
        {
            (tR[img.cols - i - 1][img.rows - j - 1] = img.redGray[img.rows - j - 1][i]);
            (tG[img.cols - i - 1][img.rows - j - 1] = img.green[img.rows - j - 1][i]);
            (tB[img.cols - i - 1][img.rows - j - 1] = img.blue[img.rows - j - 1][i]);
        }
    }


    freearray(img.redGray, img.rows);
    freearray(img.green, img.rows);
    freearray(img.blue, img.rows);

    allocarray(img.redGray, img.cols, img.rows);
    allocarray(img.blue, img.cols, img.rows);
    allocarray(img.green, img.cols, img.rows);

    swap(img.cols, img.rows);

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            img.redGray[i][j] = tR[i][j];
            img.green[i][j] = tG[i][j];
            img.blue[i][j] = tB[i][j];
        }
    }

    freearray(tR, img.rows);
    freearray(tG, img.rows);
    freearray(tB, img.rows);
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function makes the image grayscale and changes magic number according
 * to the type of output file needed.
 *
 * @param[in, out]  img - defined image structure to obtain data from.
 * @param[in]       type - contains type of output file needed.
 *
 * @par Example
 * @verbatim
   string type = "-ascii";
   string output = "output";
   string input = "input";

   ifstream fin;
   ofstream fout;
   image img;

   openIPFile(fin, input);

   if (readImage(fin, img))
   {
       grayscale(img, type);
       writeImage(fout, img, output);
   }
   @endverbatim
 *****************************************************************************/
void grayscale(image& img, string type)
{
    int i, j;

    if (type == "--ascii")
    {
        img.magicNumber = "P2";
    }
    else if (type == "--binary")
    {
        img.magicNumber = "P5";
    }
    else
    {
        error("output");
    }

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            int r = int(img.redGray[i][j]);
            int g = int(img.green[i][j]);
            int b = int(img.blue[i][j]);

            img.redGray[i][j] = pixel(round(0.3 * r + 0.6 * g + 0.1 * b));
        }
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function makes the image antique with sepia and changes magic number 
 * according to the type of output file needed.
 *
 * @param[in, out]  img - defined image structure to obtain data from.
 * @param[in]       type - contains type of output file needed.
 *
 * @par Example
 * @verbatim
   string type = "-ascii";
   string output = "output";
   string input = "input";

   ifstream fin;
   ofstream fout;
   image img;

   openIPFile(fin, input);

   if (readImage(fin, img))
   {
       sepia(img, type);
       writeImage(fout, img, output);
   }
   @endverbatim
 *****************************************************************************/
void sepia(image& img, string type)
{
    int i, j;

    if (type == "--ascii")
    {
        img.magicNumber = "P3";
    }
    else if (type == "--binary")
    {
        img.magicNumber = "P6";
    }
    else
    {
        error("output");
    }

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            double r = img.redGray[i][j];
            double g = img.green[i][j];
            double b = img.blue[i][j];

            int tr = edit(round(0.393 * r + 0.769 * g + 0.189 * b));
            int tg = edit(round(0.349 * r + 0.686 * g + 0.168 * b));
            int tb = edit(round(0.272 * r + 0.534 * g + 0.131 * b));

            img.redGray[i][j] = pixel(tr);
            img.green[i][j] = pixel(tg);
            img.blue[i][j] = pixel(tb);
        }
    }
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function corrects the value of the pixel if it overshoots the bounds of 
 * 255 pixels and contains it in bounds accordingly, iff necessary.
 *
 * @param[in]   value - contains value of pixel.
 * 
 * @return integer value of modified pixel.
 *
 * @par Example
 * @verbatim
   double r = img.redGray[i][j];
   double g = img.green[i][j];
   double b = img.blue[i][j];

   int tr = edit(round(0.393 * r + 0.769 * g + 0.189 * b)); 
   //returns proper int value of pixel
   @endverbatim
 *****************************************************************************/
int edit(double value)
{
    if (value > 255)
    {
        return 255;
    }

    else
    {
        return int(value);
    }
}