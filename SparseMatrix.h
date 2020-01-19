#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
typedef unsigned int uint;

/**
@file SparseMatrix.hpp
@brief Dichiarazione della classe SparseMatrix e delle strutture usate dalla classe
**/

template <typename T>
struct Node {
  T value;
  uint i, j;
  Node* right, *down;

  Node(const T value, const uint i, const uint j) : value(value), i(i), j(j) {
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

    /**
    @brief innerIterativeAdd

    Si occupa dell'inserimento effettivo e dell'incremento del contatore degli elementi, una volta scartati alcuni "casi base"
    @param value il valore
    @param i la riga
    @param j la colonna
    **/
    void innerIterativeAdd(const T value, const uint i, const uint j) {
      if (i < _head->i) {
        return; // ERROR
      }
      // Se non ho 0 elementi e la i è maggiore/uguale della i della head
      Node<T> *tmp = new Node<T>(value, i, j);
      Node<T> *current = _head;

      while(current != 0) {
        // Se la i dell'elemento corrente è minore della nuova i
        if (current->i < i) {
          // Ed ho un elemento più sotto
          if (current->down) {
            // Ed esso ha una i maggiore della nuova i, allora inserisco un nuovo nodo tra current e il nodo sotto
            if (current->down->i > i) {
              Node<T> *nextDown = current->down;
              current->down = tmp;
              tmp->down = nextDown;
              _counter++;
              return;
            }
            // Ed esso ha una i uguale alla nuova i, ma una j maggiore, allora devo creare il nodo sotto e mettere i link nel nuovo nodo
            else {
              if (current->down->i == i && current->down->j > j) {
                Node<T> *nextDown = current->down;
                current->down = tmp;
                tmp->right = nextDown;
                tmp->down = nextDown->down;
                nextDown->down = 0;
                _counter++;
              }
              else {
                current = current->down;
              }
            }
          }
          // Se non vi è un elemento più sotto metto il nuovo valore in un nodo più sotto
          else {
            current->down = tmp;
            _counter++;
            return;
          }
        }
        // Se la i dell'elemento corrente è uguale alla nuova i
        else {
          // E se j == alla nuova j, devo fare l'overwrite del valore
          if (current->j == j) {
            current->value = value;
          }
          // Se la j è minore della nuova j (se la j è maggiore il caso è già nella iterativeAdd)
          else {
            // E non ho un elemento a destra, metto un nuovo nodo a destra
            if (!current->right) {
              current->right = tmp;
              _counter++;
            }
            // Ed ho un elemento a destra
            else {
              // Con j minore della nuova j allora mi sposto a destra e ricomincio il ciclo
              if (current->right->j < j) {
                current = current->right;
              }
              // con j maggiore della nuova, allora metto il nuovo nodo tra il corrente ed il suo nodo destro
              else if (current->right->j > j) {
                Node<T> *nextRight = current->right;
                current->right = tmp;
                tmp->right = nextRight;
                _counter++;
                return;
              }
              // Se j è uguale alla nuova j allora devo farne l'overwrite
              else {
                current->right->value = value;
                return;
              }
            }
          }
        }
      }
    }


    /**
    @brief iterativeAdd

    Si occupa dell'inserimento effettivo e dell'incremento del contatore degli elementi
    @param value il valore
    @param i la riga
    @param j la colonna
    **/
    void iterativeAdd(const T value, const uint i, const uint j) {
      Node<T> *tmp = new Node<T>(value, i, j);
      // Se non ho elementi aggiungo alla testa della lista
      if (_head == 0) {
        _head = tmp;
        _counter++;
      }
      // Se la head ha una i maggiore dell'input allora devo cambiare head
      else if (_head->i > i) {
        Node<T> *nextDown = _head;
        _head = tmp;
        _head->down = nextDown;
        _counter++;
      }
      // Se la head ha i uguale ma ha una j maggiore devo cambiare la head
      else if (_head->i == i && _head->j > j) {
        Node<T> *nextRight = _head;
        _head = tmp;
        _head->right = nextRight;
        _head->down = nextRight->down;
        nextRight->down = 0;
        _counter++;
      }
      else {
        innerIterativeAdd(value, i, j);
      }
    }


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
    @brief add
    
    Inserisce l'elemento nella posizione (i,j)
    @param value il valore
    @param i la riga
    @param j la colonna
    **/
    void add(const T value, const uint i, const uint j) {
      // Setto i e j se sono maggiori delle attuali i e j
      const uint newRows = i + 1, newColumns = j + 1;
      if (newRows > _i) {
        _i = newRows;
      }
      if (newColumns > _j) {
        _j = newColumns;
      }
      iterativeAdd(value, i, j);
    }

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
            std::cout << rightP->value << "(" << rightP->i << "," << rightP->j << ") "; 
            rightP = rightP->right; 
        }
        std::cout << std::endl; 
        downP = downP->down; 
      }
    }
};
#endif
