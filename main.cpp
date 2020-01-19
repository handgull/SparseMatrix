#include "SparseMatrix.h"
#include <iostream>
#include <cassert>
using namespace std;

void testConstructors() {
  /// - Test sul default constructor
  cout << "Testing default constructor..." << endl;
  SparseMatrix<string> sparseMatrix1;
  // Test 1
  cout << "  checking if the default value is changed...";
  string newDefault1 = "404";
  sparseMatrix1.setDefault(newDefault1);
  assert(sparseMatrix1.getDefault() == newDefault1);
  cout << " OK!" << endl;
  /// - Test sul constructor
  cout << "Testing constructor..." << endl;
  SparseMatrix<uint> sparseMatrix2(42);
  // Test 1
  cout << "  checking the default value...";
  assert(sparseMatrix2.getDefault() == 42);
  cout << " OK!" << endl;
  // Test 2
  cout << "  checking if the default value is changed...";
  uint newDefault2 = 420;
  sparseMatrix2.setDefault(newDefault2);
  assert(sparseMatrix2.getDefault() == newDefault2);
  cout << " OK!" << endl;
  // Test 3
  cout << "  SparseMatrix values..." << endl;
  sparseMatrix2.display();
}

void testAdd() {
  /// - Test sul metodo add
  cout << "Testing add method..." << endl;
  SparseMatrix<char*> sparseMatrix1((char*)"404");
  // Test 1
  cout << "  printing the sparse matrix after an insertion..." << endl;
  sparseMatrix1.add((char*)"0", 5, 0);
  sparseMatrix1.display();
  // Test 2
  cout << "  testing rows, columns, and elements counter... ";
  const uint rows = sparseMatrix1.getRows();
  const uint columns = sparseMatrix1.getColumns();
  const uint elements = sparseMatrix1.getElements();
  assert(rows == 6);
  cout << rows << ", ";
  assert(columns == 1);
  cout << columns << ", ";
  assert(elements == 1);
  cout << elements << " OK!" << endl;
  // Test 3
  cout << "  testing after a lot of insertions... ";
  sparseMatrix1.add((char*)"a", 3, 8);
  sparseMatrix1.add((char*)"b", 2, 4);
  sparseMatrix1.add((char*)"c", 1, 0);
  assert(sparseMatrix1.getElements() == 4);
  sparseMatrix1.add((char*)"d", 1, 2);
  assert(sparseMatrix1.getElements() == 5);
  /*sparseMatrix1.add((char*)"e", 1, 1);
  assert(sparseMatrix1.getElements() == 6);
  assert(sparseMatrix1.getRows() == 6);
  assert(sparseMatrix1.getColumns() == 9);
  sparseMatrix1.add((char*)"f", 1, 1);
  assert(sparseMatrix1.getElements() + 1 == 7);
  sparseMatrix1.add((char*)"g", 8, 9);
  sparseMatrix1.add((char*)"h", 9, 9);
  assert(sparseMatrix1.getElements() == 8);
  sparseMatrix1.add((char*)"i", 4, 0);
  assert(sparseMatrix1.getElements() == 9);
  sparseMatrix1.add((char*)"l", 8, 4);
  assert(sparseMatrix1.getElements() == 10);
  sparseMatrix1.add((char*)"m", 8, 2);
  sparseMatrix1.add((char*)"n", 8, 1);
  sparseMatrix1.add((char*)"o", 0, 15);
  assert(sparseMatrix1.getElements() == 13);
  assert(sparseMatrix1.getRows() == 10);
  assert(sparseMatrix1.getColumns() == 16);
  cout << "OK!" << endl;
  sparseMatrix1.display();*/
}

int main() {
  //testConstructors();
  testAdd();
  return 0;
}
