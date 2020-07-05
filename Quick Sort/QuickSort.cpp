#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

long int getMedianOfThreePivot(std::vector<long int> numArray, long int startIndex, long int endIndex) {
  long int medianIndex = startIndex;
  long int middleElement = -1;
  long int size = (endIndex - startIndex + 1);
  if (size % 2 == 0) { middleElement = startIndex + (size)/2 - 1; }
  else { middleElement = startIndex + size/2; }

  long int maxElement = std::max<int>(numArray[middleElement], std::max<int>(numArray[startIndex], numArray[endIndex]));
  long int minElement = std::min<int>(numArray[middleElement], std::min<int>(numArray[startIndex], numArray[endIndex]));

  std::vector<int> medianVector;
  medianVector.push_back(numArray[middleElement]);
  medianVector.push_back(numArray[startIndex]);
  medianVector.push_back(numArray[endIndex]);

  long int medianValue = medianVector[0];
  for (int i = 0; i < 3; ++i) {
    if (medianVector[i] != minElement && medianVector[i] != maxElement) {
       medianValue = medianVector[i];
    }
  }
  if (medianValue == medianVector[0]) medianIndex = middleElement;
  else if(medianValue == medianVector[1]) medianIndex = startIndex;
  else if(medianValue == medianVector[2]) medianIndex = endIndex;


 // /*

 for (int i = startIndex; i <= endIndex; ++i) {
    std::cout << numArray[i] << " ";
  }
  std::cout << "\n";
  //*/
  std::cout << medianValue << " " << medianIndex << std::endl;
  // std::cout << maxElement << " " << minElement << std::endl;

  return medianIndex;
}

long int partitionArray(std::vector<long int>& numArray, long int startIndex, long int endIndex) {
  // int size = numArray.size()
  if (startIndex >= endIndex) {
    return -1;
  }
  /*for (int i = startIndex; i <= endIndex; ++i) {
    std::cout << numArray[i] << " ";
  }*/
  long int pivotIndex = startIndex;
  long int boundaryIndex = pivotIndex + 1;
  for (long int movingIndex = pivotIndex + 1; movingIndex <= endIndex; ++movingIndex) {
    if (numArray[pivotIndex] > numArray[movingIndex]) {
      std::swap(numArray[boundaryIndex], numArray[movingIndex]);
      boundaryIndex++;
    }
  }
  std::swap(numArray[boundaryIndex - 1], numArray[pivotIndex]);
  return boundaryIndex - 1;
}

long int countQuickSortComparisons(std::vector<long int>& numArray, long int pivotOption, long int startIndex, long int endIndex) {
  // int size = numArray.size()
  // std::cout << "Start: " << startIndex << " " << endIndex << std::endl;
  if (startIndex >= endIndex) {
    return 0;
  }
  long int pivotIndex = -1;
  if (pivotOption == 1) {pivotIndex = startIndex;}
  else if (pivotOption == 2) {pivotIndex = endIndex;}
  else if (pivotOption == 3) {pivotIndex = getMedianOfThreePivot(numArray, startIndex, endIndex);}
  std::swap(numArray[startIndex], numArray[pivotIndex]);
  long int partitionIndex = partitionArray(numArray, startIndex, endIndex);
  // std::cout << partitionIndex << std::endl;
  // return 0;

  if (partitionIndex == -1) {
    throw "Some error";
  }
  long int leftComparisons = countQuickSortComparisons(numArray, pivotOption, startIndex, partitionIndex - 1);
  long int rightComparisons = countQuickSortComparisons(numArray, pivotOption, partitionIndex + 1, endIndex);
  long int comparisons = endIndex - startIndex + leftComparisons + rightComparisons;
  return comparisons;
}

int main() {
  std::ifstream file("_QuickSort.txt");
  std::vector<long int> numArray;
// /*
  while (file) {
    std::string line;
    file >> line;
    std::stringstream lineNew(line);
    long int element = 0;
    lineNew >> element;
    numArray.push_back(element);
  }
  numArray.pop_back();
  file.close();
 //*/
   /*
  numArray.push_back(8);
  numArray.push_back(2);
  numArray.push_back(4);
  numArray.push_back(5);
  numArray.push_back(7);
  //numArray.push_back(1);

  //long int option_1 = countQuickSortComparisons(numArray, 1, 0, size - 1);
  //long int option_2 = countQuickSortComparisons(numArray, 2, 0, size - 1);
  //long int option_3 = countQuickSortComparisons(numArray, 3, 0, size - 1);


   */
  long int size = numArray.size();
  // long int option_1 = countQuickSortComparisons(numArray, 1, 0, size - 1);
  // long int option_2 = countQuickSortComparisons(numArray, 2, 0, size - 1);
  long int option_3 = countQuickSortComparisons(numArray, 3, 0, size - 1);
  /*for (int i = 0; i < numArray.size(); ++i) {
    std::cout << numArray[i] << " ";
  }*/
  std::cout << option_3 << " " << std::endl;
}
