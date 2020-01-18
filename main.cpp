#include "SparseMatrix.hpp"
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
  sparseMatrix1.add((char*)"hi", 0, 0);
  sparseMatrix1.display();
  // Test 2
  cout << "  testing rows, columns, and elements counter... ";
  const uint rows = sparseMatrix1.getRows();
  const uint columns = sparseMatrix1.getColumns();
  const uint elements = sparseMatrix1.getElements();
  assert(rows == 1);
  cout << rows << ", ";
  assert(columns == 1);
  cout << columns << ", ";
  assert(elements == 1);
  cout << elements << " OK!" << endl;
}

int main() {
  testConstructors();
  testAdd();
  return 0;
}
