#include "ShadersProcessor.h"
#include "Log.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>


ShadersProcessor::ShadersProcessor()
{
}

ShadersProcessor::~ShadersProcessor()
{
}

int ShadersProcessor::processingShader(ShaderType _shaderType, std::string _shaderSource)
{
    int shader;
    switch(_shaderType)
    {
        case ShaderType::VERTEX:
            std::cout << "VERTEX" << std::endl;
            shader = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::FRAGMENT:
            std::cout << "FRAGMENT" << std::endl;
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    Log::println("shader2", "LOW");
    const char* shaderSource = _shaderSource.c_str();
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    Log::println("shader3", "LOW");
    checkShader(shader);
    shaders.push_back(shader);
    return shaders.size() - 1;
}

int ShadersProcessor::compileProgram(int _vertexShader, int _fragmentShader)
{
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, shaders[_vertexShader]);
    glAttachShader(shaderProgram, shaders[_fragmentShader]);
    glLinkProgram(shaderProgram);
    checkProgram(shaderProgram);
    shadersPrograms.push_back(shaderProgram);
    return shadersPrograms.size() - 1;
}

int ShadersProcessor::getShader(int _shaderIndex)
{
    return shaders[_shaderIndex];
}

int ShadersProcessor::getProgram(int _programIndex)
{
    return shadersPrograms[_programIndex];
}

void ShadersProcessor::checkProgram(int _compiledProgram)
{
    int isCompiled;
    char log[512];
    glGetProgramiv(_compiledProgram, GL_LINK_STATUS, &isCompiled);
    if (!isCompiled)
    {
        glGetProgramInfoLog(isCompiled, 512, NULL, log);
        std::cout << "Program compilation failed!" << std::endl << log << std::endl;
    }
}

void ShadersProcessor::checkShader(int _compiledShader)
{
    int isCompiled;
    char log[512];
    glGetShaderiv(_compiledShader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        glGetShaderInfoLog(isCompiled, 512, NULL, log);
        std::cout << "Shader compilation failed!" << std::endl << log << std::endl;
    }
}

void ShadersProcessor::deleteShader(int _shaderIndex)
{
    glDeleteShader(_shaderIndex);
    shaders[_shaderIndex] = 0;
    // emptyShadersSlots.push_back(_shaderIndex);
}

void ShadersProcessor::deleteProgram(int _programIndex)
{
    glDeleteProgram(_programIndex);
    shadersPrograms[_programIndex] = 0;
    // emptyProgramsSlots.push_back(_programIndex);
}

int ShadersProcessor::loadShader(ShaderType _shaderType, std::string _shaderPath)
{
    std::cout << _shaderPath << std::endl;
    std::cout << _shaderType << std::endl;
    std::ifstream shadersFile(_shaderPath);
    if(shadersFile.fail())
    {
        std::cout << "Failed to open shader file" << std::endl;
        return -1;
    }
    std::stringstream shaderStream;
    shaderStream << shadersFile.rdbuf();
    std::string shaderText = shaderStream.str();
    shadersFile.close();
    Log::println("shader1", "LOW");
    return processingShader(_shaderType, shaderText);
}

void ShadersProcessor::defaultShaders()
{
    int a = loadShader(ShaderType::VERTEX, "shaders\\shader2.vert");
    int b = loadShader(ShaderType::FRAGMENT, "shaders\\shader.frag");
    int c = compileProgram(a, b);
}