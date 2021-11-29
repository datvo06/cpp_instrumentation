#ifndef _DATAFLOW_H
#define _DATAFLOW_H

#include <llvm/IR/Instruction.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Pass.h>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <llvm_utils.h>

namespace datautils {
	typedef std::pair<llvm::Value*, std::string> node;
	typedef std::pair<node, node> edge;
	typedef std::list<node> node_list;
	typedef std::list<edge> edge_list;

	std::string getValStaticName(llvm::Value* val);
  static unsigned int num = 0;

	struct DataWorker: llvm::ModulePass {
		static char ID;
		DataWorker();
		bool runOnModule(llvm::Module &M);
		private:
		bool dumpGlobals;
		std::list<node> gVars;
		std::map<llvm::Value*, llvm::Function*> func_calls;
		std::map<llvm::Function*, node_list> func_args;
			std::map<llvm::Function*, edge_list> func_edges_ctrl;
			std::map<llvm::Function*, node_list> func_nodes_ctrl;
		edge_list data_flow_edges;
	};
}

#endif
