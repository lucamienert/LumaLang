#ifndef LUMALANG_IO_H_
#define LUMALANG_IO_H_

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string get_file_content(std::string filename);
std::string shell_command(std::string command);

#endif