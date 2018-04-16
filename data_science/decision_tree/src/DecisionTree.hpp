//
//  DecisionTree.hpp
//  Created by 주안 on 2018. 4. 16..
//  Copyright © 2018년 주안. All rights reserved.
//

#ifndef DecisionTree_hpp
#define DecisionTree_hpp

#include <stdio.h>
#include <string>
#include "DecisionTable.hpp"

#ifndef DT_ID_UNSET
#define DT_ID_UNSET  -1
#endif

#ifndef D_NODE
#define D_NODE
struct Node{
		bool isLeaf;
		vector< int > tuple_ids;
		vector< struct Node * > children;
		int split_attr_id;
		int result_class_id;
	};
#endif
class DecisionTree{
	private :
	
	DecisionTable decision_table;

	public :
	struct Node * root;
	vector< int > predic_vote;
	DecisionTree(DecisionTable dt);
	struct Node * create_node();
	bool is_equal_class( vector<int> pTupleId );
	bool is_equal_label( int pAttrId, vector<int> pTupleId );
	void insert_tuple( struct Node* node, int pTupleId );
	void build_tree( struct Node* node, int pPrio );
	void create_tree( );
	void classify(  struct Node* node ,vector<int> &pTuple );

	/* For Debug */
	void debug_print_t( struct Node * node, int level, int childi, int parent_end); // print tree 
};

#endif /* DecisionTree_hpp */
