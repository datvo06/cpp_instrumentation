#include <dataflow.h>

std::string datautils::getValStaticName(llvm::Value *val){
	std::string rVal = "val";
	if (val->getName().empty()) {
		rVal += std::to_string(datautils::num);
		num++;
	}
	else rVal = val->getName().str();
	// llvm::isa works exactly like java 'instanceof'
	if (llvm::isa<llvm::Instruction>(val)){
		rVal += ":" + llvmutils::LLVMInstructionAsString(llvm::dyn_cast<llvm::Instruction>(val));
	}
	return rVal;
}


bool datautils::DataWorker::runOnModule(llvm::Module &M){
	for (auto g_vIdx : M.getGlobalList()){
		gVars.push_back(&*g_vIdx, g_vIdx->getName().str());
	}

	for (auto FI : M.getFunctionList()){
		// Get a function wise list so the operands defined in the function make sense when
		// use in store instructions, else in the graph they appear out of no where
		for (auto BB : FI->getBasicBlockList()){
			for (auto II : BB){
				switch(II->getOpCode()){
					case llvm::Instruction::Call:
						{
							llvm::CallInst * callinst = llvm::dyn_cast_or_null<llvm::CallInst>(II);
							llvm::Function * func = callinst->getCalledFunction();
							// Use iterations over the arguments of functions
							func_calls[&*II] = func;
							for (auto arg_idx : func->args()){
								func_args[func].push_back(node(&*arg_idx, datautils::getValStaticName(&*arg_idx)));
								// TODO: use iterations over the arguments of the function
							}
							break;
						}
					case llvm::Instruction::Store:
						{
							llvm::StoreInst* storeInst = llvm::dyn_cast<llvm::StoreInst>(II);
							llvm::Value* storeValPtr = storeInst->getPointerOperand();
							// Store both pointer and value into the dataflow graph
							// storeVal -> II -> storeAddr
							llvm::Value* storeVal= storeInst->getValueOperand();
							data_flow_edges.push_back(
									edge(
										node(&*II, datautils::getValStaticName(&*II)),
									 	node(storeValPtr, datautils::getValStaticName(storeValPtr))));
							data_flow_edges.push_back(
									edge(
										node(storeVal, datautils::getValStaticName(storeVal)),
										node(&*II, datautils::getValStaticName(&*II))
										)
									)
								break;
						}
					case llvm::Instruction::Load:
						{
							llvm::LoadInst* loadInst = llvm::dyn_cast<llvm::LoadInst>(II);
							llvm::Value* loadValPtr = loadInst->getPointerOperand();
							// load: loadAddr -> II
							data_flow_edges.push_back(
									edge(
										node(loadValPtr, datautils::getValStaticName(loadValPtr)),
										node(&*II, datautils::getValStaticName(&*II))
										)
							);
							break;
						}
					default:
						{
							for(auto op : II){
								if (llvm::dyn_cast<Instruction>(*op)|| llvm::dyn_cast<llvm::Argument>(*op)){
										data_flow_edges.push_back(edge(
													node(
														op->get(),
														datautils::getValStaticName(op->get())
													), 
													node(&*II, datautils::getValStaticName(&*II))));
								}
							}
							break;
						}
				}
				auto prev = II;
				++prev;
			}
		}
	}
	return false;
}
