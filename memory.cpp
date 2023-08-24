/** **************************************************************************
 * @file
 ****************************************************************************/
#include "netPBM.h"

//2D ARRAY ALLOCATION
/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function accepts a 2d pointer array and assigns 2d memory 
 * to the array of n rows and m columns, based on the number of rows and 
 * columns provided by the user.
 *
 * @param[in, out]  array - accepts 2d pointer array, to assign dynamic memory.
 * @param[in]       rows - number of rows of memory to assign.
 * @param[in]       columns - number of columns of memory to assign.
 *
 * @par Example
 * @verbatim
   pixel** array;   
   int x = rows; //number of rows
   int y = columns; //number of columns
   allocarray(array, x, y);
   //now array is a dynamic 2d array of x rows and y columns;
   @endverbatim
 *****************************************************************************/
void allocarray(pixel** &array, int rows, int columns)
{
    int i;

    array = new (nothrow) pixel*[rows];

    if (array == nullptr)
    {
        cout << "Unable to allocate memory for storage." << endl;
        delete[] array;
        exit(0);
    }

    for (i = 0; i < rows; i++)
    {
        array[i] = new (nothrow) pixel[columns];

        if (array[i] == nullptr)
        {
            cout << "Unable to allocate memory for storage." << endl;
            freearray(array, i);
            exit(0);
        }
    }
}

//2D ARRAY DELETION
/** ***************************************************************************
 * @author Steve Nathan de Sa
 *
 * @par Description
 * This function accepts an initiated 2d dynamic pointer array and clears its
 * data memory.
 *
 * @param[in, out]  array - accepts 2d pointer array, to erase dynamic memory.
 * @param[in]       rows - number of rows of memory in file.
 *
 * @par Example
 * @verbatim
   pixel** array;
   int x = rows; //number of rows
   int y = columns; //number of columns
   allocarray(array, x, y);
   //now array is a dynamic 2d array of x rows and y columns
   freearray(array, x);
   //now array has its memory freed up, with memory erased
   @endverbatim
 *****************************************************************************/
void freearray(pixel** &array, int rows)
{
    int i;

    if (array == nullptr)
    {
        return;
    }

    for (i = 0; i < rows; i++)
    {
        delete[] array[i];
    }

    delete[] array;
}
