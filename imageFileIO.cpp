/** **************************************************************************
 * @file
 ****************************************************************************/
#include "netPBM.h"

//OPEN INPUT FILE
/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function opens input image file in binary format.
 *
 * @param[in, out]  file - ifstream file declaration to edit file.
 * @param[in]       filename - contains name of file to be opened.
 *
 * @par Example
 * @verbatim
   ifstream file;
   string filename = "steve.txt";
   openIPFile(file,filename); //opens input file named steve.txt
   @endverbatim
 *****************************************************************************/
void openIPFile(ifstream& file, string filename)
{
    file.open(filename, ios::binary);

    if (!file.is_open())
    {
        cout << "Unable to open the file: " << filename << endl;
        exit(0);
    }
}

//OPEN OUTPUT FILE
/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function opens output image file in binary format.
 *
 * @param[in, out]  file - ifstream file declaration to edit file.
 * @param[in]       filename - contains name of file to be opened.
 *
 * @par Example
 * @verbatim
   ifstream file;
   string filename = "output.txt";
   openIPFile(file,filename); //opens output file named output.txt
   @endverbatim
 *****************************************************************************/
void openOPFile(ofstream& file, string filename)
{
    file.open(filename, ios::binary | ios::trunc);

    if (!file.is_open())
    {
        cout << "Unable to open the file: " << filename << endl;
        exit(0);
    }
}

//READ DATA FROM IMAGE FILE
/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function reads the data from the file according to the file type as
 * specified by the magic number. The data is stored in the structure image 
 * for use later on in the code for editting and printing out.
 *
 * @param[in, out]  fin - ifstream file declaration to edit file.
 * @param[in, out]  img - defined image structure to store data in.
 *
 * @return true if the function successfully reads the file data.
 * 
 * @par Example
 * @verbatim
   ifstream fin;
   string filename = "steve.txt";
   openIPFile(fin,filename); //opens file named steve.txt
   image img; //structure
   if(readImage(fin, img)
   {
        cout << "File has been successfully read";
   }
   @endverbatim
 *****************************************************************************/
bool readImage(ifstream& fin, image& img)
{
    std::getline(fin, img.magicNumber);

    string unknown;

    while (std::getline(fin, unknown) && unknown[0] == '#')
    {
        img.comment = img.comment + unknown + '\n';
    }

    size_t nl = (img.comment).find_last_of('\n');
    (img.comment).erase(nl, 1);

    size_t pos = unknown.find(" ");
    img.cols = stoi(unknown.substr(0, pos));
    img.rows = stoi(unknown.substr(pos + 1));

    string max_pixels;
    std::getline(fin, max_pixels);

    int i,j;
    int x = 0; //COUNTER

    int inputs = 3 * img.rows * img.cols;

    int* avalues = nullptr;
    pixel* bvalues = nullptr;

    allocarray(img.redGray, img.rows, img.cols);
    allocarray(img.blue, img.rows, img.cols);
    allocarray(img.green, img.rows, img.cols);

    if (img.magicNumber == "P3" && stoi(max_pixels) <= 255) //PPM ASCII
    {
        avalues = new (nothrow) int[inputs];

        for (i = 0; i < inputs; i++)
        {
            fin >> avalues[i];
        }

        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                img.redGray[i][j] = pixel(avalues[x]);
                x++;
                img.green[i][j] = pixel(avalues[x]);
                x++;
                img.blue[i][j] = pixel(avalues[x]);
                x++;
            }
        }

        delete[] avalues;
        fin.close();
        
        return true;
    }

    else if (img.magicNumber == "P6" && stoi(max_pixels) <= 255) //PPM BINARY
    {
        bvalues = new (nothrow) pixel[inputs];

        fin.read((char*)bvalues, sizeof(pixel)*inputs);

        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                img.redGray[i][j] = bvalues[x];
                x++;
                img.green[i][j] = bvalues[x];
                x++;
                img.blue[i][j] = bvalues[x];
                x++;
            }
        }

        delete[] bvalues;
        fin.close();

        return true;
    }

    else
    {
        delete[] avalues;
        delete[] bvalues;
        return false;
    }

    return true;
}

//WRITING DATA TO THE IMAGE FILE
/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function writes the modified data of the image to the new file specified
 * by the user. 
 *
 * @param[in, out]  fout - ofstream file declaration to edit file.
 * @param[in, out]  img - defined image structure to obtain data from.
 * @param[in]       filename - contains name of file to be opened.
 *
 * @par Example
 * @verbatim
   ifstream fin;
   ofstream fout;
   string filename = "steve.txt";
   string opfile = "op.txt";
   openIPFile(fin,filename); //opens file named steve.txt
   image img; //structure
   if(readImage(fin, img)
   {
        cout << "File has been successfully read";
   }
  
   writeImage(fout,img,opfile); //writes data to opfile
   @endverbatim
 *****************************************************************************/

void writeImage(ofstream& fout, image& img, string filename)
{
    int i, j;

    if (img.magicNumber == "P3" || img.magicNumber == "P6")
    {
        filename = filename + ".ppm";
    }

    else if (img.magicNumber == "P2" || img.magicNumber == "P5")
    {
        filename = filename + ".pgm";
    }

    openOPFile(fout, filename);

    fout << img.magicNumber << endl;
    fout << img.comment << endl;
    fout << img.cols << " " << img.rows << endl;
    fout << 255 << endl;

    if (img.magicNumber == "P3") //PPM ASCII
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                fout << int(img.redGray[i][j]) << " " << int(img.green[i][j]) << " " << int(img.blue[i][j]) << endl;
            }
        }
    }

    else if (img.magicNumber == "P6") //PPM BINARY
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                fout.write((char*)&img.redGray[i][j], sizeof(pixel));
                fout.write((char*)&img.green[i][j], sizeof(pixel));
                fout.write((char*)&img.blue[i][j], sizeof(pixel));
            }
        }
    }

    else if (img.magicNumber == "P2") //PGM ASCII
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                fout << int(img.redGray[i][j]) << endl;
            }
        }
    }

    else if (img.magicNumber == "P5") //PGM BINARY
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                fout.write((char*)&img.redGray[i][j], sizeof(pixel));
            }
        }
    }

    freearray(img.redGray, img.rows);
    freearray(img.green, img.rows);
    freearray(img.blue, img.rows);

    fout.close();
}
