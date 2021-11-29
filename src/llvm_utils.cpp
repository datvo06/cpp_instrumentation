#include <llvm_utils.h>

std::string llvmutils::LLVMTypeAsString(const llvm::Type *T){
	std::string typeNm;
	llvm::raw_string_ostream N(typeNm);
	T->print(N);
	return N.str();
}


std::string llvmutils::LLVMInstructionAsString(llvm::Instruction* I){
	std::string instStr;
	llvm::raw_string_ostream N(instStr);
	I->print(N);
	return N.str();
}
