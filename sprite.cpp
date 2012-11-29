#include "sprite.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

#define LINE_LENGTH 17 //16 chars and a \n
Sprite::Sprite()
{
    //ctor
}

Sprite::~Sprite()
{
    //dtor
}

using namespace std;
using std::vector;

namespace pfo_sprite {
    class sprite {
        public:
            //This is a bit wonky... I don't think there's a limit
            //on vector size. But, this is the only way to avoid
            //having blank frames. I think it behaves like a normal
            //array anyway.
            vector<vector<vector<char> > > data;

        sprite() {

        }

        int load(std::string fname) {
            //Load char-based (0 through A?) image file
            //Maybe 1 through F colors...
            cout << "Loading PFO Sprite " << fname << endl;

            ifstream file;

            char LineBuffer[LINE_LENGTH];
            bool LoadColors = false, LoadFrames = false;
            int CurrentColor = 0;
            int CurrentFrame = 0;
            int FrameLine = 0;

            file.open(fname.c_str());

            if (file == NULL) {
                file.close();
                cout << "Error: File is null. Check that file exists, or that the name is correct: " << fname << endl;
            }

            while(!file.eof()) {
                //Read in a line and store in LineBuffer
                file.getline(LineBuffer, LINE_LENGTH);

                //Check first character of the line
                switch(LineBuffer[0]) {
                    case '#': //Standard comment line
                        continue;

                    case '\\': //Color Marker
                        LoadColors = true;
                        break;

                    case '/': //Frame Block Marker
                        LoadFrames = true;
                        break;

                    case '$': //Number of frames in sprite
                        std::string Frames = "";
                        for (int i = 0; i < LINE_LENGTH; i++) {
                            if (LineBuffer[i] == '#' ) break;
                            if (isdigit(LineBuffer[i])) Frames += LineBuffer[i];
                        }

                        //Build data container for exact frames
                        data.resize(atoi(Frames.c_str()));
                        for (int i = 0; i < 15; i++) {
                            data[i].resize(16);
                            for (int j = 0; j < 15; j++) {
                                data[i][j].resize(16);
                            }
                        }
                        break;
                }
            }
        }
    };
}
