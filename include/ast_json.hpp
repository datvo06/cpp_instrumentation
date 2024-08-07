#ifndef _AST_JSON_
#define _AST_JSON_

/**
 * Load the AST as boost's graph
 */
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace graphutils{
	struct VertexInfo{
		std::int32_t id;
		std::string nType;
		std::string content;
		std::int32_t startLine;
		std::int32_t startPos;
		std::int32_t startCol;
		std::int32_t endLine;
		std::int32_t endCol;
		std::int32_t endPos;
	};

	struct EdgeInfo{
		float weight;
		std::string label;
	};

		
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexInfo, EdgeInfo> ASTGraph;
	typedef boost::graph_traits<ASTGraph>::vertex_iterator VertexItr;
	ASTGraph jsonStrToGraph(std::string jsonStr);
	VertexItr findVertex(const ASTGraph& g, std::function< bool(VertexInfo)> lambda);
}

#endif
