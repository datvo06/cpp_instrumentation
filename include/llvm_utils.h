#ifndef _LLVM_UTILS_H
#define _LLVM_UTILS_H
#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>

namespace llvmutils{
	std::string LLVMTypeAsString(const llvm::Type *T);
	std::string LLVMInstructionAsString(llvm::Instruction *I);
}

#endif
