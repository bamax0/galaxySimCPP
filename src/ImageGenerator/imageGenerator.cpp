#include <pngwriter.h>

#include <sstream>
#include <cstddef>
#include <fstream>

#include <string>
#include <iostream>
#include <filesystem>
using namespace std;
int main()
{
    int width = 1900, height = 1900;
    string folderPath = "./data";
    string imgFolderPath = "./img";
    if (!filesystem::exists(folderPath))
    {
        folderPath = "../data";
        imgFolderPath = "../img";
    }

    for (const auto &entry : filesystem::directory_iterator(folderPath))
    {
        string path = entry.path();

        int id;
        char c;
        istringstream(filesystem::path(path).stem()) >> c >> c >> c >> c >> id;

        if (path.find("mass") != string::npos)
        {
            continue;
        }
        cout << "Image n°" << id << endl;

        ifstream source;
        source.open(path, ios_base::in); // open data

        string img_path = imgFolderPath + "/sav_" + to_string(id) + ".png";

        pngwriter PNG(width, height, 0, img_path.c_str());
        int h = -1;
        double r = 1;
        for (string line; getline(source, line);) // read stream line by line
        {
            istringstream in(line);
            float x, y, z;
            char c;
            in >> x >> c >> y >> c >> z;
            PNG.plot(x, y, 0.3f, 0.3f, 1.0f);
        }
        PNG.close();
    }
    return 0;
}