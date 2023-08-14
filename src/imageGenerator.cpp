#include <pngwriter.h>

#include "imageGenerator.h"
#include <sstream>
#include <cstddef>
#include <fstream>

#include <string>
#include <iostream>

using namespace std;

void generateImage(Galaxy &g, int idx)
{
    int imgWidth = 1900, imgHeight = 1900;
    float boardWidth = 20, boardHeight = 20;
    string imgFolderPath = "./img";

    string img_path = imgFolderPath + "/sav_" + to_string(idx) + ".png";

    pngwriter PNG(imgWidth, imgHeight, 0, img_path.c_str());
    float widthCoef = imgWidth / boardWidth / 2, heightCoef = imgHeight / boardHeight / 2;
    float widthOffset = imgWidth / 2, heightOffset = imgHeight / 2;

    for (int i = 0; i < g.getNbStar(); ++i)
    {
        float x = g[i].pos.x, y = g[i].pos.y, z = g[i].pos.z;
        PNG.plot(x * widthCoef + widthOffset, y * heightCoef + heightOffset, 0.3f, 0.3f, 1.0f);
    }
    PNG.close();
}

int generateImages()
{
    int imgWidth = 1900, imgHeight = 1900;
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

        pngwriter PNG(imgWidth, imgHeight, 0, img_path.c_str());
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