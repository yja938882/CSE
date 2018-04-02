# Apriori

  * 내용      :  Apriori Algorithm 구현
  * 세부내용  : apriori.pdf 
  * 컴파일   : #> g++ [excutable_file_name] apriori.cpp 
  * 실행     : #> [excutable_file_name] [minimum support] [input_file] [output_file] 
  
## Pseudo-code
  C[K] : Candidate itemset of size K </br>
  F[K] : Frequent itemset of size K </br></br>
  L[1] = { frequent items } </br>
  for( k = 1; L[k] != Empty ; k++) </br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;C[k+1] = Candidates generated from L[k]</br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;for each transaction t in DB</br>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  increment the count of all candidates in C[k+1] that are contained in t </br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;L[k+1] = Candidates in C[k+1] with min_support </br>
  return L[1...K];
  
