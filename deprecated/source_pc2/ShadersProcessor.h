#ifndef SHADERSPROCESSOR_H
#define SHADERSPROCESSOR_H

#include <vector>
#include <string>

enum ShaderType
{
    VERTEX,
    FRAGMENT,
};

class ShadersProcessor
{
    private:
        std::vector<int> shaders;
        std::vector<int> shadersPrograms;
    public:
        ShadersProcessor();
        ~ShadersProcessor();
        int processingShader(ShaderType, std::string);
        int getShader(int);
        int compileProgram(int, int);
        int getProgram(int);
        void checkShader(int);
        void checkProgram(int);
        void deleteShader(int);
        void deleteProgram(int);
        int loadShader(ShaderType _shaderType, std::string _shaderPath);
        void defaultShaders();
};

#endif
