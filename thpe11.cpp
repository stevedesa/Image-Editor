/** **************************************************************************
 * @file
 ****************************************************************************/
#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"
#include "netPBM.h"

//TEST CASE DEFINITION
/** **********************************************************************
* @author Steve Nathan de Sa
*
* @par Description
* constant for RUNCATCH which defines whether test cases should run or not.
************************************************************************/
const bool RUNCATCH = false;

//MAIN
/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function receives command line arguments and accordingly calls the
 * necessary functions to read the image, edit the image and output the image.
 * 
 *
 * @param[in]  argc - contains number of command line arguments.
 * @param[in]  argv - contains the command line argument text.
 *
 * @return 0.
 *
 * @par Example
 * @verbatim
   If ".\thpe11.exe --sepia --binary sepiabb BalloonsX.ppm" was entered in terminal
   the function will open the image BalloonsX.ppm, read it, call sepia function, 
   and print the edited image to file named sepiabb.ppm.
   @endverbatim
 *****************************************************************************/
int main(int argc, char** argv)
{
    Catch::Session session;
    int result;

    //TEST CASE RUNCATCH
    if (RUNCATCH)
    {
        result = session.run(argc, argv);
        if (result != 0)
        {
            cout << "Test cases didn't pass" << endl;
            return 0;
        }
    }

    //4 ARGUMENTS
    if (argc == 4)
    {
        string output = argv[2];
        string input = argv[3];

        ifstream fin;
        ofstream fout;
        image img;

        openIPFile(fin, input);

        if (readImage(fin, img))
        {
            if (strcmp(argv[1], "--ascii") == 0)
            {
                img.magicNumber = "P3";
            }

            else if (strcmp(argv[1], "--binary") == 0)
            {
                img.magicNumber = "P6";
            }

            else
            {
                error("output");
            }

            writeImage(fout, img, output);
        }
        else
        {
            cout << "Unable to allocate memory for storage." << endl;
            exit(0);
        }
    }

    //5 ARGUMENTS
    else if (argc == 5)
    {
        string type = argv[2];
        string output = argv[3];
        string input = argv[4];

        ifstream fin;
        ofstream fout;
        image img;

        openIPFile(fin, input);

        if (strcmp(argv[1], "--flipX") == 0)
        {
            if (readImage(fin, img))
            {
                flipX(img, type);
                writeImage(fout, img, output);
            }
            else
            {
                cout << "Unable to allocate memory for storage." << endl;
                exit(0);
            }
        }

        else if (strcmp(argv[1], "--flipY") == 0)
        {
            if (readImage(fin, img))
            {
                flipY(img, type);
                writeImage(fout, img, output);
            }
            else
            {
                cout << "Unable to allocate memory for storage." << endl;
                exit(0);
            }
        }

        else if (strcmp(argv[1], "--rotateCW") == 0)
        {
            if (readImage(fin, img))
            {
                rotateCW(img, type);
                writeImage(fout, img, output);
            }
            else
            {
                cout << "Unable to allocate memory for storage." << endl;
                exit(0);
            }
        }

        else if (strcmp(argv[1], "--rotateCCW") == 0)
        {
            if (readImage(fin, img))
            {
                rotateCCW(img, type);
                writeImage(fout, img, output);
            }
            else
            {
                cout << "Unable to allocate memory for storage." << endl;
                exit(0);
            }
        }

        else if (strcmp(argv[1], "--grayscale") == 0)
        {
            if (readImage(fin, img))
            {
                grayscale(img, type);
                writeImage(fout, img, output);
            }
            else
            {
                cout << "Unable to allocate memory for storage." << endl;
                exit(0);
            }
        }

        else if (strcmp(argv[1], "--sepia") == 0)
        {
            if (readImage(fin, img))
            {
                sepia(img, type);
                writeImage(fout, img, output);
            }
            else
            {
                cout << "Unable to allocate memory for storage." << endl;
                exit(0);
            }
        }

        else //INVALID OPTION
        {
            fin.close();
            error("option");
        }
    }

    //INVALID NUMBER OF ARGS
    else
    {
        error("xxx");
    }
}

//ARGUMENT ERROR
/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function prints out error statements into the terminal if the command
 * line arguments have been inaccurately provided by the user. Based on type 
 * of error, appropriate error statement is printed.
 *
 * @param[in]       type - string that contains type of error.
 *
 * @par Example
 * @verbatim
   if(argc != 2)
   {
        error("xxx"); //prints plain error statement of usage
   }
   if(argv[1] != "s")
   {
        error("option"); //prints option error + usage statement
   }
   @endverbatim
 *****************************************************************************/
void error (string type)
{
    if (type == "option")
    {
        cout << "Invalid option given" << endl;
    }

    else if (type == "output")
    {
        cout << "Invalid output type specified" << endl;
    }

    cout << "thpe11.exe [option] --outputtype basename image.ppm" << endl;
    cout << endl;
    cout << "Output Type      Output Description" << endl;
    cout << "    --ascii      integer text numbers will be written for the data" << endl;
    cout << "    --binary     integer number will be written in binary form" << endl;
    cout << endl;
    cout << "Option Code      Option Description" << endl;
    cout << "    --flipX      Flip the image on the X axis" << endl;
    cout << "    --flipY      Flip the image on the Y axis" << endl;
    cout << "    --rotateCW   Rotate the image clockwise" << endl;
    cout << "    --rotateCCW  Rotate the image counter clockwise" << endl;
    cout << "    --grayscale  Convert image to grayscale" << endl;
    cout << "    --sepia      Antique a color image" << endl;
    exit(0);
}