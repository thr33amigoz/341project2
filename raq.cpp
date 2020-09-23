#include "raq.h"
#include <iostream>
#include <math.h>

// Creates a RAQ object from a data vector.
// Performs precomputation for the Dynamic Programming solution.
RAQ::RAQ(std::vector<float> data){

  int size = data.size();
  float prevAvg;
  float average;
  int count = -1;
  bool first = true;

  m_size = data.size();
  
  // for loop for i
  for(unsigned int i = 0; i < data.size(); i++){

    if (first == false){
      matrix.pop_back();
    }
    
    count++;
    prevAvg = data.at(i);

    matrix.push_back(prevAvg);
    
    // nested for loop for j, j is always greater than i
    for(unsigned int j = i; j < size + i; j++){

      // use the given formula to caluclate average
      average = ( (j - i + 1) * prevAvg + data[j + 1] ) / (j - i + 2);
      // add every average
      matrix.push_back(average);
      // set the previous average
      prevAvg = average;

    }
   
    first = false;
    // decrease size of the next line by 1
    size--;
  }
  matrix.pop_back();
  
}

// Performs a Range Average Query from index i to index j. i and j must be in the range 
// 0…n−1 where n is the length of the data vector.
float RAQ::query(int i, int j) const{

  int size = m_size;

  // throw an domain error, if i or j are out of bounds
  if ( i < 0 || i > j || j >= m_size ){
    throw std::domain_error("RAQ::query(): out of bounds");
  }

  // if its the first row, index in the matrix is just j
  if ( i == 0 ){
    return matrix[j];
  }

  // otherwise, calculate the index using a formula I created
  else{
    int valFirst = ( (i - 2) * (i - 1) ) / 2;

    // calulate the index in the vector
    int value = (size * i ) - ( ( valFirst ) + (i - 1) );
    return matrix[ value + (j - i)];
  }
}

// Print the contents of the precomputation data structure.
// Must be formatted to be easily read, at least for small data sizes n≤15.
void RAQ::dump() const{
  int count = 0;
  int counter = 0;

  // prints out every element in the vector
  for (unsigned int i = 0; i < matrix.size(); i++){
    if (count == m_size - counter){
      count = 0;
      counter++;
      // create a newline at the end of a line
      std::cout << "\n";
    }
    count++;
    std::cout << matrix.at(i) << "\t";
  }
  std::cout << std::endl;
}

// Creates a BlockRAQ object from a data vector.
// Performs precomputation for the Block Decomposition solution.  
BlockRAQ::BlockRAQ(std::vector<float> data){

  copyVect(data);
  
  // size of the data vector
  int size = data.size();
  
  m_sizeRaq = data.size();
  
  // size of blocks equal the square root of the size of the data vector
  int blockSize = sqrt(size);
  
  float blockFloat = size/blockSize;
  int blockNum = blockFloat;

  // set blockNum and blockSize
  m_blockNum = blockNum;
  m_blockSize = blockSize;

  // round up the number of blocks
  if (blockFloat > blockNum){
    blockNum++;
  }
  
  float average = 0;
  int count = 0;

  // iterate through the data
  for (int i = 0; i < size; i++){
    // add to average each time
    average = average + data.at(i);

    // incase the final cube isn't the normal blockSize
    if ((i == size - 1) && (count != blockSize - 1)){

      average = average / (count + 1);
      answerVect.push_back(average);
      m_blockNum++;
    }

    // if the count equals the normal blockSize
    if (count == blockSize - 1){
      
      count = 0;
      average = average / blockSize;
      answerVect.push_back(average);
      average = 0;
    }
    
    // if count isnt the normal blockSize
    else{
      count++;
    }
  }
  
}

// Performs a Range Average Query from index i to index j. i and j must
// be in the range (0…n−1) where n is the length of the data vector.
float BlockRAQ::query(int i, int j) const{
  
  float average = 0;
  int count = 0;

  // throw an domain error, if i or j are out of bounds
  if ( i < 0 || i > j || j >= m_sizeRaq ){
    throw std::domain_error("BlockRAQ::query(): out of bounds");
  }

  // iterate through the initial non-fully used block, if there is one
  while( ( i != 0 ) && ( i < j ) && ( i % m_blockSize != 0 )  ){

    // add to the average
    average = average + copyData.at(i);
    i++;
    count++;
  }

  // if an entire block can be used to calculate average, use it
  while( i + m_blockSize <= j ){

    // multiply by the block size and add to average
    average = average + (m_blockSize * answerVect[i / m_blockSize]);
    // increase i and count by blocksize
    i = i + m_blockSize;
    count = count + m_blockSize;
  }

  // iterate through the final non-fully used block
  while ( i <= j ){

    // add to the average
    average = average + copyData.at(i);
    i++;
    count++;
    
  }

  // return the average
  return average / count;  
}

// Print the contents of the precomputation data structure.
// The output must include the number of blocks, block size,
// and the precomputed block averages.
// Must be formatted to be easily read, at least for small data sizes n≤15
void BlockRAQ::dump() const{
  std::cout << "Num blocks: " << m_blockNum << std::endl;
  std::cout << "Block size: " << m_blockSize << std::endl;
  std::cout << "Block averages: " << std::endl;
  
  // print out the vector
  for (int i = 0; i < m_blockNum; i++){
    std::cout << answerVect.at(i) << "  ";
  }

  std::cout << std::endl;
}
