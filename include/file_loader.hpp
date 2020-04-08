#ifndef FILE_LOADER_HPP
#define FILE_LOADER_HPP

#include <stdint.h>
#include <functional>
#include <vector>
#include <string>

class Color;
class Vec2D;
struct ParseFuncParams{
    std::string line = "";
    size_t delimitPos = 0;
    uint32_t lineNum = 0;
};

using ParseFunction = std::function<void(const ParseFuncParams& params)>;

enum CommandType{ 
    ONE_LINE_COMMAND = 0,
    MULTI_LINE_COMMAND
};

struct Command{
    CommandType type = ONE_LINE_COMMAND;
    std::string command = "";
    ParseFunction func = nullptr;
};

class FileLoader{
    public:
        void addCommand(const Command& command);
        bool loadFile(const std::string& filePath);
        static Color readColor(const ParseFuncParams& params);
        static Vec2D readVec2D(const ParseFuncParams& params);
        static Vec2D readSize(const ParseFuncParams& params);
        static uint32_t readInt(const ParseFuncParams& params);
        static std::string readString(const ParseFuncParams& params);
        static char readChar(const ParseFuncParams& params);
    private:
        std::vector<Command> _commands;
};
#endif