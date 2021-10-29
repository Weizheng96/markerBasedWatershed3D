#include "watershed3D.h"
#include <chrono>
#include <iostream>

using namespace std;



int main() {

    /////////////////////////////////////////////////////////////
    /// 1.create a example as the input of the 3D markerbased watershed
    /////////////////////////////////////////////////////////////

    GVInt32 width=30;
    GVInt32 height=20;
    GVInt32 thick =20;


    const GVInt32 SZ_slice = width * height;
    const GVInt32 SZ = SZ_slice* thick;

    // the marker
    vector<vector<int>> marker;
    marker.resize(2);
    marker[0].push_back(7);
    marker[1].push_back(29);
    

    // the data
    GVByte* image = new GVByte[SZ];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < thick; k++) {
                image[i + j * width+ k*SZ_slice] = 5 - i;
                image[i + 10 + j * width + k * SZ_slice] = 5 - i;
                image[i + 5 + j * width + k * SZ_slice] = i;
                image[i + 15 + j * width + k * SZ_slice] = i;
                image[i + 25 + j * width + k * SZ_slice] = i;
                image[i + 20 + j * width + k * SZ_slice] = 5-i;
            }
        }
    }

    // the label (must allocate memory first)
    GVInt32* label = new GVInt32[SZ];

    /////////////////////////////////////////////////////////////
    /// 2. watershed
    /////////////////////////////////////////////////////////////

    auto t0 = chrono::high_resolution_clock::now();
    
    Watershed3D(image,width,height,thick,label,marker);

    auto t1 = chrono::high_resolution_clock::now();
    auto dt = 1.e-9 * chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
    cout << "Used " << dt << " seconds.\n\n" << endl;



    /////////////////////////////////////////////////////////////
    /// 3. show result
    /////////////////////////////////////////////////////////////
    int z = 0;
    cout << "Data (z=" << z << "/" << thick << "):" << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << (int)image[i * width + j + z * SZ_slice] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Label (z=" << z << "/" << thick << "):" << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << label[i * width + j + z * SZ_slice] << " ";
        }
        cout << endl;
    }
    
    return 0;
}