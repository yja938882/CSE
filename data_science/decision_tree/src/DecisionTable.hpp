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

class DecisionTable{
    private :
    
    map< string, int > attr_id_Map;
    map< int, string > id_attr_Map;
    
    vector< map< string, int > > label_id_Maps;
    vector< map< int, string > > id_label_Maps;
    
    int attr_count;
    vector< int > label_count;
    int class_id;
    
    vector< vector<int> > tuples;

    double infoD;
    vector< pair< double, int > > gain;
    
 

    public :
    
    DecisionTable();
    
    void insert_attr ( string pAttr );
    string get_attr_by_id ( int pId );
    int get_id_by_attr ( string pAttr );
    
    void init_label();
    void insert_label ( int pAttrId, string pLabel );
    string get_label_by_id ( int pAttrId, int pId );
    int get_id_by_label ( int pAttrId, string pLabel );
    
    int attrs_size();
    int labels_size( int pAttr );
    
    void insert_tuple( string pTuple );
    
    double _I( int *pClassCount, int N );

    void init_info_gain();


    int get_class_id();
    int get_tuple_class( int pTupleId );
    int get_tuple_label( int pTupleId, int pAttr );
    int get_gain_size();
    int get_prio_gain( int priority );
    int get_tuple_size();

    static bool GreaterPair( const pair<double , int> & a, const pair<double, int>& b);


    /*For Debug*/
    void debug_print_al();  // print attrs & labels
    void debug_print_tp();  // print tuples
    void debug_print_ig();  // print info gain
    
};
#endif /* DecisionTable_hpp */

