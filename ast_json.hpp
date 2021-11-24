#ifndef _AST_JSON_
#define _AST_JSON_

/**
 * Load the AST as boost's graph
 */
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace graphutils{
	struct VertexInfo{
	};
		
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> Graph;
}

#endif
