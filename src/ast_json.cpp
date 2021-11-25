#include <ast_json.hpp>
#include <nlohmann/json.hpp>


using namespace graphutils;
using nlohmann::json;


int32_t getId(const VertexInfo& v){
	return v.id;
}


int32_t getStartLine(const VertexInfo& v){
	return v.startLine;
}


int32_t getStartPos(const VertexInfo& v){
	return v.startPos;
}

int32_t getStartCol(const VertexInfo& v){
	return v.startCol;
}


int32_t getEndLine(const VertexInfo& v){
	return v.endLine;
}

int32_t getEndCol(const VertexInfo& v){
	return v.endCol;
}


int32_t getEndPos(const VertexInfo& v){
	return v.endPos;
}

std::string getType(const VertexInfo& v){
	return v.nType;
}

std::string getContent(const VertexInfo& v){
	return v.content;
}


typedef int32_t (*IntValFunc)(const VertexInfo&);
typedef std::string (*StrValFunc)(const VertexInfo&);

const std::map<std::string, IntValFunc> funcMapInt = {{"start_line", &getStartLine},
	{"start_pos", &getStartPos}, {"start_col", &getStartCol}, {"end_line", &getEndLine},
	{"end_pos", &getEndPos}, {"end_col", &getEndCol}, {"id", &getId}
};
const std::map<std::string, StrValFunc> funcMapStr = {{"content", &getContent},
	{"ntype", &getType}
};


VertexItr findVertex(const ASTGraph& g, const std::pair<std::string, int32_t> kvPair){
	auto key = kvPair.first;
	auto val = kvPair.second;
	auto p_func = funcMapInt.at(key);
	VertexItr vi, viEnd;
	for (boost::tie(vi, viEnd) = boost::vertices(g); vi != viEnd; ++vi){
		auto t_val = (*p_func)(g[*vi]);
		if (t_val == val){
			return vi;
		}
	}
	return viEnd;
}


VertexItr findVertex(const ASTGraph& g, const std::pair<std::string, std::string> kvPair){
	auto key = kvPair.first;
	auto val = kvPair.second;
	auto p_func = funcMapStr.at(key);
	VertexItr vi, viEnd;
	for (boost::tie(vi, viEnd) = boost::vertices(g); vi != viEnd; ++vi){
		auto t_val = (*p_func)(g[*vi]);
		if (t_val == val){
			return vi;
		}
	}
	return viEnd;
}


VertexItr findVertex(const ASTGraph& g, std::function<bool(VertexInfo)> filterFunc){
	VertexItr vi, viEnd;
	for (boost::tie(vi, viEnd) = boost::vertices(g); vi != viEnd; ++vi){
		if (filterFunc(g[*vi]))
			return vi;
	}
	return viEnd;
}



ASTGraph jsonStrToGraph(std::string jsonStr){
	// First: parse string
	auto jObject = json::parse(jsonStr);
	auto jNodes = jObject["Nodes"];
	ASTGraph g;
	int n = jNodes["size"];
	for (auto i = 0; i <= n; i++){
		auto jNodeDict = jNodes[std::to_string(i)];
		auto v = boost::add_vertex(g);
		g[v] = {i, jNodeDict["ntype"],
		 	jNodeDict["token"], jNodeDict["start_line"], jNodeDict["start_col"], jNodeDict["start_pos"],
			jNodeDict["end_line"], jNodeDict["end_col"], jNodeDict["end_pos"]
		};
		auto pID =  jNodeDict["parent"];
		if (pID != -1){
			auto p = *findVertex(g, std::make_pair("id", (int)pID));
			boost::add_edge(p, v, {1.0, "parent_child"}, g);
		}
	}
	return g;
}
