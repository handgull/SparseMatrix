#ifndef SparseMatrixHpp
#define SparseMatrixHpp
#include <iostream>
typedef unsigned int uint;

/**
@file sorted_array.hpp
@brief Dichiarazione della classe SparseMatrix e delle strutture usate dalla classe
**/

template <typename T>
struct Node {
  T data;
  uint i;
  uint j;
  Node* right, *down;

  Node(const T data, const uint i, const uint j) {
    this->data = data;
    this->i = i;
    this->j = j;
    right = 0;
    down = 0;
  }

  ~Node() {
    delete right;
    delete down;
  }
};

template <typename T>
class SparseMatrix {
  private:
    T _defaultValue;
    uint _i, _j, _counter;
    Node<T> *_head;

  public:
    /**
    @brief Costruttore di default (METODO FONDAMENTALE)

    Costruttore di default per istanziare una matrice sparsa vuota SENZA VALORE DI DEFAULT.
    Necessita quindi una chiamata del metodo setter del valore di default
    **/
    SparseMatrix() : _head(0), _i(0), _j(0), _counter(0) {}

    /**
    @brief Costruttore

    Costruttore per istanziare una matrice sparsa vuota.
    @param defaultValue (valore da restituire se l'elemento nelle posizioni specificate non esiste).
    **/
   SparseMatrix(const T defaultValue) : _head(0), _i(0), _j(0), _counter(0) {
     _defaultValue = defaultValue;
   }

  /**
  @brief recursiveAdd

  Scorre ricorsivamente la struttura dati e mette l'elemento nella posizione (i,j)
  @param data il valore
  @param data la riga
  @param data la colonna
  @return Ritorna true se è stato aggiunto un elemento, false se è stato sovrascritto
  **/
   bool recursiveAdd(Node<T> **headP, const T data, const uint i, const uint j) {
     // Caso base in cui ho 
     if (*headP == 0) {
       *headP = new Node<T>(data, i, j);
       return true;
     }
     // Caso base in cui ho la head con indici uguali al nuovo elemento (overwrite)
     else if (*(headP)->i == i && *headP->j == j) {
       *headP->data = data;
       return false;
     }
     // Caso in cui devo scorrere la riga
     else if (*headP->i < i) {
       // Se l'elemento della riga dopo ha la i > allora la riga va aggiunta
       if (*headP->down != 0 && *headP->down->i > i) {
         Node<T> *downElement = *headP->down, *newElement = new Node<T>(data, i, j);
         *headP->down = newElement;
         newElement->down = downElement;
         return true;
       }
     }
   }

    /**
    @brief add

    Inserisce l'elemento nella posizione (i,j)
    @param data il valore
    @param data la riga
    @param data la colonna
    **/
   void add(const T data, const uint i, const uint j) {
     // Setto i e j se sono maggiori delle attuali i e j
     if (i + 1 > this->_i) {
       this->_i = i + 1;
     }
     if (j + 1 > this->_j) {
       this->_j = j + 1;
     }
     if (recursiveAdd(&_head, data, i, j)) {
       this->_counter++;
     }
   }

    // Hakai
    /**
    @brief Distruttore (METODO FONDAMENTALE)

    Distruttore. Rimuove la memoria allocata dall'oggetto.
    **/
    ~SparseMatrix() {
      delete _head;
    }

    /**
    @brief getDefault
    @return Il _defaultValue della matrice sparsa.
    **/
    T getDefault() {
      return _defaultValue;
    }

    /**
    @brief setDefault
    @param defaultValue (Il nuovo valore di _defaultValue).
    **/
    void setDefault(const T defaultValue) {
      _defaultValue = defaultValue;
    }

    /**
    @brief getRows
    @return Il numero di righe della matrice sparsa
    **/
    uint getRows() {
      return _i;
    }

    /**
    @brief getColumns
    @return Il numero di colonne della matrice sparsa
    **/
    uint getColumns() {
      return _j;
    }

    /**
    @brief getElements
    @return Il numero di elementi totale della matrice sparsa
    **/
    uint getElements() {
      return _counter;
    }

    /**
    @brief display

    Stampa a video gli elementi della matrice sparsa "avvicinandoli"
    **/
    void display() {
      Node<T> *rightP, *downP = _head;

      while (downP) { 
        rightP = downP; 

        while (rightP) { 
            std::cout << rightP->data << "(" << rightP->i << "," << rightP->j << ") "; 
            rightP = rightP->right; 
        }
        std::cout << std::endl; 
        downP = downP->down; 
      }
    }
};
#endif
