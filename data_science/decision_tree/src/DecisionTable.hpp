//
//  DecisionTable.hpp
//  Created by 주안 on 2018. 4. 16..
//  Copyright © 2018년 주안. All rights reserved.
//

#ifndef DecisionTable_hpp
#define DecisionTable_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;

/*
    Decision Table
*/
class DecisionTable{
    private :
    
    map< string, int > attr_id_Map;     // Attribute(string) - ID(int) Mapping
    map< int, string > id_attr_Map;     // ID(int) - Attribute(string) Mapping
    vector< map< string, int > > label_id_Maps; // Label(string) - ID(int) Mapping
    vector< map< int, string > > id_label_Maps; // ID(int) - Label(string) Mapping
    int attr_count;             // Attribute 의 갯수
    vector< int > label_count;  // Label의 갯수
    int class_id;               // Class 기준 이되는 Attribute ID
    
    public :
    /* Constructor */
    DecisionTable();

    vector< vector<int> > tuples;   // Training Tuples
    /* Function */
    void insert_attr ( string pAttr );      // Attribute 를 테이블에 추가
    string get_attr_by_id ( int pId );      // ID에 해당하는 Attribute 반환
    int get_id_by_attr ( string pAttr );    // Attribute에 해당하는 ID 반환
    void init_label();                      // Label 초기화
    void insert_label ( int pAttrId, string pLabel );   // Label 을 해당 Attribute 에 추가
    string get_label_by_id ( int pAttrId, int pId );    // ID 에 해당하는 Label 반환
    int get_id_by_label ( int pAttrId, string pLabel ); // Label에 해당하는 ID 반환
    int attrs_size();               // Attribute 의 갯수
    int labels_size( int pAttr );   // Label 들의 갯수
    void insert_tuple( string pTuple ); // Table 에 튜플 삽입
    
    int get_class_id();                             // Class Attribute ID 반환
    int get_tuple_class( int pTupleId );            // Tuple이 해당하는 Class 반환
    int get_tuple_label( int pTupleId, int pAttr ); // Tuple이 가진 Label 반환
    int get_gain_size();                            // Gain 의 갯수 반환
    int get_prio_gain( int priority );              // 해당하는 순위의 Gain 반환
    int get_tuple_size();                           // 튜플의 크기 반환

    /* Static */
    static bool GreaterPair( const pair<double , int> & a, const pair<double, int>& b);

    /*For Debug */
    void debug_print_al();  // print attrs & labels
    void debug_print_tp();  // print tuples
    
};
#endif /* DecisionTable_hpp */

