//
//  DecisionTree.cpp
//  Created by 주안 on 2018. 4. 16..
//  Copyright © 2018년 주안. All rights reserved.
//

#include "DecisionTree.hpp"

DecisionTree::DecisionTree(DecisionTable dt){
	decision_table = dt;
}

struct Node* DecisionTree::create_node(){
	struct Node *n = new struct Node;
	n->isLeaf = false;
	n->split_attr_id = DT_ID_UNSET;
	n->result_class_id = DT_ID_UNSET;
	return n;
}

bool DecisionTree::is_equal_class( vector<int> pTupleId ){
	if( pTupleId.size() <= 0) return true;

	int first_class = decision_table.get_tuple_class( pTupleId[0] );
	for( int i=1; i<pTupleId.size(); i++ ){
		if( decision_table.get_tuple_class( pTupleId[i] ) != first_class ) return false;
	}
	return true;
}

bool DecisionTree::is_equal_label(  int pAttrId, vector<int> pTupleId ){
	if( pTupleId.size() <= 0) return true;

	int first_label = decision_table.get_tuple_label( pTupleId[0], pAttrId );
	for( int i=1; i<pTupleId.size(); i++ ){
		if( decision_table.get_tuple_label( pTupleId[i], pAttrId ) != first_label ) return false;
	}
	return true;
}

void DecisionTree::insert_tuple( struct Node* node, int pTupleId ){
	node -> tuple_ids.push_back( pTupleId );
}

void DecisionTree::build_tree( struct Node* node, int pPrio ){
	if( node-> tuple_ids.size() <=0 ){
		node->isLeaf = true;
		node-> result_class_id = DT_ID_UNSET;
		return;
	}

	if( pPrio >= decision_table.get_gain_size() ){
		int vote[ decision_table.get_gain_size() ];
		for( int i=0; i<decision_table.get_gain_size(); i++ ){
			vote[i] = 0;
		}
		for( int i=0; i<node->tuple_ids.size(); i++){
			vote[ decision_table.get_tuple_class( node->tuple_ids[i] ) ] ++;
		}
		int max = 0;
		int max_id = 0;
		for( int i=0; i<decision_table.get_gain_size(); i++ ){
			if( vote[i] > max ){
				max = vote[i];
				max_id = i;
			}
		}
		node -> isLeaf = true;
		node -> result_class_id = max_id;
		return;
	}

	if( is_equal_class( node->tuple_ids ) ){
		node -> isLeaf = true;
		node -> result_class_id = decision_table.get_tuple_class(node->tuple_ids[0]);
		return;
	}

	if( is_equal_label( decision_table.get_prio_gain( pPrio ), node-> tuple_ids) ){
		build_tree( node, pPrio +1 );
		return;
	}
	
	node -> split_attr_id = decision_table.get_prio_gain( pPrio );
	node -> children.resize( decision_table.labels_size( node -> split_attr_id ) );
	for( int i=0; i< node->children.size(); i++){
		node->children[i] = NULL;
	}

	vector< vector< int > >splited_tuples( node-> children.size() );
	for( int i=0; i< node->tuple_ids.size(); i++ ){
		splited_tuples[ decision_table.get_tuple_label( node->tuple_ids[i], node->split_attr_id) ].push_back( node-> tuple_ids[i] );
	}
	node->tuple_ids.resize(0);

	for ( int i=0; i< splited_tuples.size(); i++ ){
		node -> children[i] = create_node();
		for ( int j=0; j< splited_tuples[i].size(); j++ ){
			insert_tuple( node->children[i] , splited_tuples[i][j] );
		}
		if( splited_tuples[i].size() > 0){
			build_tree( node->children[i], pPrio + 1);
		}
	}
}

void DecisionTree::create_tree(){
	 predic_vote.resize( decision_table.labels_size( decision_table.get_class_id() ) );
     for( int i=0; i< predic_vote.size(); i++ )
        predic_vote[i] = 0;

	this->root = create_node();
	for( int i=0; i< decision_table.get_tuple_size(); i++ ){
		insert_tuple( root, i );
	}
	build_tree( root, 0 );
}

void DecisionTree::classify(  struct Node* node ,vector<int> &pTuple){
	struct Node* cur = node;
	while( !(cur->isLeaf) ){
		if( cur ->split_attr_id == DT_ID_UNSET ){
			pTuple.push_back(-1);
			return;
		}
		int next = pTuple[ cur->split_attr_id ];
		cur = cur->children[ next ];
	}
	pTuple.push_back( cur-> result_class_id );
	predic_vote[ cur->result_class_id ] ++;
}

void DecisionTree::debug_print_t( struct Node* node, int level, int childi, int parent_end){
	if(node ==NULL)
		return;

	if(childi>0){
		for( int i=0; i< parent_end - 7; i++){
			cout<<" ";
		}
		cout<<"|------>";
	}

	string printed_str;
	struct Node * cur = node;
	
	if( node-> isLeaf ){
		printed_str = ( "[" + decision_table.get_label_by_id( decision_table.get_class_id(), node -> result_class_id ) +"]");
		cout<<printed_str<<endl;
		return;
	}else if( node->split_attr_id == DT_ID_UNSET ){
		printed_str = ( "[unkown]" );
		cout<<printed_str<<endl;
		return;
	}else{
		printed_str = ( "(" + decision_table.get_attr_by_id(node->split_attr_id) +")"+"(" +to_string(node->children.size())+")"+"----->" );
		cout<<printed_str;
	}
	for( int i=0; i< node->children.size(); i++ ){
		debug_print_t( node-> children[i] , level+1 , i , parent_end + printed_str.length() );
	}
}



