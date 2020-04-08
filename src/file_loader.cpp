#include "file_loader.hpp"
#include <fstream>
#include <iostream>

#include "color.hpp"
#include "v2d.hpp"

void FileLoader::addCommand(const Command& command){
    _commands.push_back(command);
}

bool FileLoader::loadFile(const std::string& filePath){
    std::fstream input;
    std::string line;
    input.open(filePath);
    if(!input.is_open()){
        std::cerr << "could not open file: " << filePath << "!" << std::endl;
        return false;
    }

    size_t commPos = std::string::npos;
    size_t commEndPos = std::string::npos;
    std::string command = "";
    ParseFuncParams params;
    while(!input.eof()){
        std::getline(input, line);
        commPos = line.find(":");
        if(commPos != std::string::npos){
            commEndPos = line.find_first_of(" ", commPos);
            if(commEndPos == std::string::npos){
                commEndPos = line.length();
            } else{
                commEndPos -= 1; // we found first space, now go back one 
            }
            commPos += 1; // we found first colon, now go one forward
            command = line.substr(commPos, commEndPos);

            // find appropriate command interpretation
            for(size_t commIdx = 0; commIdx < _commands.size(); commIdx++){
                if(command == _commands[commIdx].command){
                    if(_commands[commIdx].type == ONE_LINE_COMMAND){
                        params.line = line;
                        params.delimitPos = commEndPos;
                        params.lineNum = 0;
                        _commands[commIdx].func(params);
                    }else{
                        size_t numLines = std::stoi(line.substr(commEndPos + 1)); 
                        size_t lineIdx = 0; 
                        while(lineIdx < numLines){
                            std::getline(input, line);
                            if(line.empty()){
                                continue;
                            }

                            params.line = line;
                            params.delimitPos = 0;
                            params.lineNum = lineIdx;
                            _commands[commIdx].func(params);
                            ++lineIdx;
                        }
                    }
                }
            }
        }
    }
    return true;
}

Color FileLoader::readColor(const ParseFuncParams& params){
    size_t prevSpacePos, nextSpacePos;
    uint32_t red, green, blue, alpha;

    prevSpacePos = params.delimitPos;
    nextSpacePos = params.line.find_first_of(" ", prevSpacePos + 1);
    red = std::stoi(params.line.substr(prevSpacePos + 1, 
                                       nextSpacePos - prevSpacePos));
    
    prevSpacePos = nextSpacePos;
    nextSpacePos = params.line.find_first_of(" ", prevSpacePos + 1);
    green = std::stoi(params.line.substr(prevSpacePos + 1, 
                                         nextSpacePos - prevSpacePos));

    prevSpacePos = nextSpacePos;
    nextSpacePos = params.line.find_first_of(" ", prevSpacePos + 1);
    blue = std::stoi(params.line.substr(prevSpacePos + 1, 
                                        nextSpacePos - prevSpacePos));

    prevSpacePos = nextSpacePos;
    alpha = std::stoi(params.line.substr(prevSpacePos + 1));
    return Color(red, green, blue, alpha);
}

Vec2D FileLoader::readVec2D(const ParseFuncParams& params){
    size_t prevSpacePos, nextSpacePos;
    float x, y;

    prevSpacePos = params.delimitPos;
    nextSpacePos = params.line.find_first_of(" ", prevSpacePos + 1);
    x = std::stof(params.line.substr(prevSpacePos + 1, 
                                     nextSpacePos - prevSpacePos));
    
    prevSpacePos = nextSpacePos;
    y = std::stof(params.line.substr(prevSpacePos + 1));
    return Vec2D(x, y);
}

Vec2D FileLoader::readSize(const ParseFuncParams& params){
    return readVec2D(params);
}


uint32_t FileLoader::readInt(const ParseFuncParams& params){
    return std::stoi(params.line.substr(params.delimitPos + 1));
}
std::string FileLoader::readString(const ParseFuncParams& params){
    return params.line.substr(params.delimitPos + 1);
}
char FileLoader::readChar(const ParseFuncParams& params){
    return params.line.substr(params.delimitPos + 1)[0];
}
