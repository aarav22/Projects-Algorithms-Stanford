#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int countInversions(std::vector<int> &numArray, int startIndex, int endIndex) {
  int size = endIndex - startIndex + 1;
  if (size == 0 || size == 1) {
    return 0;
  }

  int countInversionsLeft = countInversions(numArray, startIndex, size/2);
  int countInversionsRight = countInversions(numArray, size/2 + 1, endIndex);
  int counterLeft = startIndex, counterRight = size/2 + 1;
  int leftSize = size/2 + 1, rightSize = endIndex + 1;
  std::vector<int> newOutput;
  int countingInversions = 0;

  while (counterLeft < leftSize && counterRight < rightSize) {
    if (numArray[counterLeft] <= numArray[counterRight]) {
      newOutput.push_back(numArray[counterLeft++]);
    } else {
      newOutput.push_back(numArray[counterRight++]);
      countingInversions += leftSize - counterLeft;
    }
  }
  while (counterLeft < leftSize) {
    newOutput.push_back(numArray[counterLeft++]);
  }
  while (counterRight < rightSize) {
    newOutput.push_back(numArray[counterRight++]);
  }

  int newStart = startIndex;
  for (int i = 0; i < newOutput.size(); ++i) {
  //  numArray[newStart++] = newOutput[i];
  }

  return countingInversions + countInversionsLeft + countInversionsRight;
}

int main() {
  std::ifstream file("IntegerArray.txt");
  std::vector<int> numArray;
  while (file) {
    std::string line;
    file >> line;
    std::stringstream lineNew(line);
    int element = 0;
    lineNew >> element;
    numArray.push_back(element);
  }
  int size = numArray.size();
  file.close();
  std::cout << countInversions(numArray, 0, size - 1);
}
