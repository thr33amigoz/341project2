#ifndef _RAQ_H
#define _RAQ_H

#include <vector>
#include <array>

// RAQ Class implements the Dynamic Programming solution

class RAQ {
 public:
  
  // Create the RAQ object; perform precomputation
  RAQ(std::vector<float> data);

  // ******************************************************
  // **
  // ** IF NEEDED (depends on class variables),
  // **   constructor, destructor, assignment operator
  // **   go here
  // **
  // ******************************************************
  
  // Query the RAQ for interval [i, j]
  float query(int i, int j) const;
  
  // Dump the RAQ data structure to stdout
  void dump() const;
  
 private:
  
  // ******************************************************
  // **
  // **  Define the class variables here
  // **
  // ******************************************************

  // track the size of the vector                                       
  int m_size;

  // store every precalculation inside of this vector                          
  std::vector<float> matrix;

  // ******************************************************
  // **
  // ** Declare private helper functions here
  // **
  // ******************************************************  

};

// BlockRAQ class implements the Block Decomposition solution

class BlockRAQ {
public:
  // Create the BlockRAQ object; perform precomputation
  BlockRAQ(std::vector<float> data);

  // ******************************************************
  // **
  // ** IF NEEDED (depends on class variables),
  // **   constructor, destructor, assignment operator
  // **   go here
  // **
  // ******************************************************

  // Query the BlockRAQ for interval [i, j]
  float query(int i, int j) const;
  
  // Dump the BlockRAQ data structure to stdout
  void dump() const;
  
 private:

  // ******************************************************
  // **
  // **  Define the class variables here
  // **
  // ******************************************************

  int m_sizeRaq;
  // track the number of blocks
  int m_blockNum;
  // track the size of the blocks
  int m_blockSize;
  // the vector containing the answer
  std::vector<float> answerVect;
  // a vector to make a copy of data
  std::vector<float> copyData;
  
  
  // ******************************************************
  // **
  // ** Declare private helper functions here
  // **
  // ******************************************************
  
  // function to create a copy of a vector
  void copyVect(std::vector<float> realData){

    for (unsigned int i = 0; i < realData.size(); i++){
      copyData.push_back(realData.at(i));
    }

  }
  
};


#endif
