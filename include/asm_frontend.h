#ifndef LUMALANG_ASM_H_
#define LUMALANG_ASM_H_

#pragma once

#include <ast.h>
#include <string>

std::string asm_f_root(AST *ast);
std::string asm_f(AST *ast);

#endif