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
/*
	Decision Tree 의 노드.
*/
struct Node{
		bool isLeaf;						// 마지막 노드인지 여부
		vector< int > tuple_ids;			// 노드가 포함하고있는 튜플의 아이디
		vector< struct Node * > children;	// 자식 노드들
		int split_attr_id;					// 자식을 나누는 Attribute
		int result_class_id;				// Class 결과
	};
#endif
/*
	Decision Tree Class
*/
class DecisionTree{
	private :
	DecisionTable decision_table;	// Decision Table

	public :
	/* Constructor */
	DecisionTree(DecisionTable dt);	// Constructor
	
	struct Node * root;	// Decision Tree 의 루트 노드

	/* Function */
	struct Node * create_node();	// 노드 생성
	bool is_equal_class( vector<int> pTupleId );				// 튜플들이 모두 같은 클래스인지 여부 
	bool is_equal_label( int pAttrId, vector<int> pTupleId );	// 튜플들이 모두 같은 라벨을 가지고 있는지 여부
	void insert_tuple( struct Node* node, int pTupleId );		// node 에 튜플 삽입
	void build_tree( struct Node* node );			// Build DecisionTree Recursive
	void create_tree( );										// Decision Tree 생성
	void classify(  struct Node* node ,vector<int> &pTuple );	// 해당 튜플을 Calssify
	double info( vector<int> D );
	int select_attribute( vector< int > tuple_id );

	/* For Debug */
	void debug_print_t( struct Node * node, int level, int childi, int parent_end); // print tree 
};

#endif /* DecisionTree_hpp */
