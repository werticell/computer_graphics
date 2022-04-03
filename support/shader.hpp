#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

namespace framework {

namespace detail {
std::string ReadFile(const char* filepath);

void CompileShader(const char* filepath, std::string& code, GLuint& shader_id);

void CheckProgram(GLuint& shader_id, GLint& result);

bool MakeShader(const char* shader_path, GLuint& shader_id, GLint& result);

}  // namespace detail

GLuint LoadShaders(const char* vertex_file_path,
                   const char* fragment_file_path);

}  // namespace framework
