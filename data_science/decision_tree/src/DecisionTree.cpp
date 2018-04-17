//
//  DecisionTree.cpp
//  Created by 주안 on 2018. 4. 16..
//  Copyright © 2018년 주안. All rights reserved.
//

#include "DecisionTree.hpp"
/**
	@brief Constructor
*/
DecisionTree::DecisionTree(DecisionTable dt){
	decision_table = dt;
}

/**
	@brief 노드 생성
	@return 생성된 노드 
*/
struct Node* DecisionTree::create_node(){
	struct Node *n = new struct Node;
	n->isLeaf = false;
	n->split_attr_id = DT_ID_UNSET;
	n->result_class_id = DT_ID_UNSET;
	return n;
}

/**
	@brief 모두 같은 클래스인지 여부 반환
	@param pTupleId 확인할 튜플들의 ID
	@return 해당 튜플들이 모두 같은 클래스인지 여부 
*/
bool DecisionTree::is_equal_class( vector<int> pTupleId ){
	if( pTupleId.size() <= 0) return true;

	int first_class = decision_table.get_tuple_class( pTupleId[0] );
	for( int i=1; i<pTupleId.size(); i++ ){
		if( decision_table.get_tuple_class( pTupleId[i] ) != first_class ) return false;
	}
	return true;
}

/**
	@brief 모두 같은 라벨을 가지고 있는지 여부 반환
	@param pAttrId 확인할 Attribute ID
	@param pTupleID 확인할 튜플들의 ID
*/
bool DecisionTree::is_equal_label(  int pAttrId, vector<int> pTupleId ){
	if( pTupleId.size() <= 0) return true;

	int first_label = decision_table.get_tuple_label( pTupleId[0], pAttrId );
	for( int i=1; i<pTupleId.size(); i++ ){
		if( decision_table.get_tuple_label( pTupleId[i], pAttrId ) != first_label ) return false;
	}
	return true;
}

/**
	@brief 노드에 튜플을 삽입
	@param node 튜플을 삽입할 노드
	@param 삽입할 튜플의 ID
*/
void DecisionTree::insert_tuple( struct Node* node, int pTupleId ){
	node -> tuple_ids.push_back( pTupleId );
}

/*
	@brief 재귀적으로 tree 생성
	@param node 
	@param pPrio Gain으로 판별된 우선권
*/
void DecisionTree::build_tree( struct Node* node){
	int selected_attr = select_attribute( node-> tuple_ids );
	// 더 이상 나눌 Attribute 가 없을 때
	if( selected_attr == -1 ){	
		int pv_size =decision_table.labels_size( decision_table.get_class_id() );
		int pv[ pv_size ];
		for( int v = 0; v< pv_size; v++ ) pv[ v ] = 0;

		for ( int v =0; v< node->tuple_ids.size(); v++){
			pv[ ( decision_table.get_tuple_label( node-> tuple_ids[v] , decision_table.get_class_id() ) )]++;
		}
		int max = 0;
		int max_i = 0;
		for( int v =0; v< pv_size; v++ ){
			if( max < pv[ v ] ){
				max = pv[ v ];
				max_i = v;
			}
		}
		node->isLeaf = true;
		node->result_class_id = max_i;
		return;
	}

	// 모두 같은 Calass 를 가졌을 때
	if( is_equal_class( node->tuple_ids ) ){
		node -> isLeaf = true;
		node -> result_class_id = decision_table.get_tuple_class(node->tuple_ids[0]);
		return;
	}

	// Node Split
	node -> split_attr_id = selected_attr; 
	node -> children.resize( decision_table.labels_size( node -> split_attr_id ) );
	
	for( int i=0; i< node->children.size(); i++){
		node->children[i] = NULL;
	}

	vector< vector< int > >splited_tuples( node-> children.size() );
	for( int i=0; i< node->tuple_ids.size(); i++ ){
		splited_tuples[ decision_table.get_tuple_label( node->tuple_ids[i], node->split_attr_id) ].push_back( node-> tuple_ids[i] );
	}

	for ( int i=0; i< splited_tuples.size(); i++ ){
		node -> children[i] = create_node();
		for ( int j=0; j< splited_tuples[i].size(); j++ ){
			insert_tuple( node->children[i] , splited_tuples[i][j] );
		}
		if( splited_tuples[i].size() > 0){
			build_tree( node->children[i]);

		}else{	// 어떤 Attribute label에 해당하는 튜플이 없을때 -> Vote 를 통해 결정
			int pv_size =decision_table.labels_size( decision_table.get_class_id() );
			int pv[ pv_size ];
			for( int v = 0; v< pv_size; v++ ) pv[ v ] = 0;

			for ( int v =0; v< node->tuple_ids.size(); v++){
				pv[ ( decision_table.get_tuple_label( node-> tuple_ids[v] , decision_table.get_class_id() ) )]++;
			}
			int max = 0;
			int max_i = 0;
			for( int v =0; v< pv_size; v++ ){
				if( max < pv[ v ] ){
					max = pv[ v ];
					max_i = v;
				}
			}
			node->children[i] = create_node();
			node->isLeaf = true;
			node->result_class_id = max_i;
		}
	}
}

/**
	@brief 트리 생성
*/
void DecisionTree::create_tree(){
	this->root = create_node();
	for( int i=0; i< decision_table.get_tuple_size(); i++ ){
		insert_tuple( root, i );
	}
	build_tree( root );
}

/**
	@brief	Tuple 의 Class 예측
	@param node 분류를 시작하려는 node
	@param pTupleId 분류하려는 tuple 의 id
*/
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
}

/**
	@brief information 계산 info (d)
*/
double DecisionTree::info( vector<int> D ){
	int sum = 0;
	double info = 0.0;
	for( int i=0; i<D.size(); i++ ){
		sum += D[i];
	} 
	for( int i=0; i<D.size(); i++ ){
		if( D[i] == sum ){
			return 0.0;
		}
	}

	for( int i=0; i<D.size(); i++ ){
		if( D[i] == 0) continue;
		info -= ( (double)D[i]/sum ) * log2( (double)D[i]/sum );
	}
	return info;
}

/**
	@brief 현재 선택되어야할 attribute id 반환
*/
int DecisionTree::select_attribute( vector< int > tuple_id ){
	int class_sz = decision_table.labels_size( decision_table.get_class_id() ) ;
	vector< vector< vector< int > > > label_cnt( decision_table.attrs_size() -1 );

	// Initialize
	for( int i=0; i< decision_table.attrs_size()-1; i++ ){
		label_cnt[i].resize( decision_table.labels_size(i) );
		for( int j=0; j< label_cnt[i].size() ; j++ )
			label_cnt[i][j].resize( class_sz );
	}

	// Initialize
	for( int i=0; i<label_cnt.size(); i++ )
		for( int j=0; j<label_cnt[i].size(); j++)
			for( int k=0; k<label_cnt[i][j].size(); k++ )
				label_cnt[i][j][k] = 0;
	// Count
	for( int i=0; i< tuple_id.size(); i++ ){
		for( int j=0; j< decision_table.attrs_size()-1; j++){
			label_cnt[j][ decision_table.get_tuple_label( tuple_id[i], j) ]
			[decision_table.get_tuple_label(tuple_id[i], decision_table.get_class_id()) ]++;
		}
	}

	int min_i = -1;
	double min = 1000.0;	
	for( int i=0; i<label_cnt.size(); i++ ){
		double attr_Info = 0.0;
		
		if( is_equal_label( i , tuple_id ) ){
			continue;
		}
		for( int j=0; j< label_cnt[i].size(); j++ ){
			double _I = info( label_cnt[i][j]);
			int sum = 0;
			for ( int k=0; k< label_cnt[i][j].size() ; k++ ){
				sum += label_cnt[i][j][k];
			}
			attr_Info += ( ((double) sum )/ (double) tuple_id.size() ) * _I;
		}
		if(attr_Info < min ){
			min = attr_Info;
			min_i = i;
		}
	}
	return min_i;
}

/*===========================================
	For Debug
============================================*/

/**	For DEBUG.
	@brief Print Decision Tree 
*/
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

