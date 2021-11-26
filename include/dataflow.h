#ifndef _DATAFLOW_H
#define _DATAFLOW_H

#include <llvm/IR/Instruction.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <list>
#include <vector>

namespace datautils {
	typedef std::pair<llvm::Value*, std::string> node;
	typedef std::pair<node, node> edge;
	typedef std::list<node> node_list;
	typedef std::list<edge> edge_list;

	struct DataWorker: llvm::ModulePass {
		static char ID;
		DataWorker();
		bool runOnModule(llvm::Module &M);
		private:
		bool dumpGlobals;
	}
}

#endif
