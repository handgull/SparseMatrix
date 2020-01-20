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
    right = 0;
    down = 0;
  }
};

template <typename T>
class SparseMatrix {
  private:
    T _defaultValue;
    uint _i, _j, _counter;
    Node<T> *_head;

    /**
    @brief iterativeColumnAdd

    Si occupa dell'inserimento all'interno della riga, che è stata già individuata
    @param curr il nodo con il primo elemento della riga in questione
    @param value il valore
    @param j la colonna
    **/
    void iterativeColumnAdd(const Node<T> *up, const Node<T> *init, const T value, const uint i, const uint j) {
      // Se la i di init non è uguale ad i allora questo metodo non è stato chiamato al momento giusto
      if (init->i != i) {
        return; // ERROR
      }
      Node<T> *current = (Node<T>*)init;
      Node<T> *upNode = (Node<T>*)up;
      Node<T> *leftNode = 0;

      while(current != 0) {
        // Se sia i che j sono uguali, allora devo fare una semplice overwrite del valore
        if (current->j == j) {
          current->value = value;
          return;
        }
        // Se la colonna corrente è minore della nuova colonna
        if (current->j < j) {
          // Ed ho un elemento a destra, allora scorro a destra e salvo l'elemento corrente
          if (current->right) {
            leftNode = current;
            current = current->right;
          }
          // E non ho un elemento a destra, allora aggiungo un elemento alla destra
          else {
            current->right = new Node<T>(value, current->i, j);;
            _counter++;
            return;
          }
        }
        // Se la colonna corrente è maggiore della nuova colonna
        else {
          // Ed ho un nodo più a sinistra, allora devo aggiungere un nodo tra il sinistro ed il corrente
          if (leftNode) {
            Node<T> *tmp = new Node<T>(value, current->i, j);
            leftNode->right = tmp;
            tmp->right = current;
            _counter++;
            return;
          }
          // E non ho un nodo più a sinistra, allora devo mettere un nuovo nodo a sinistra e spostare i collegamenti
          else {
            Node<T> *tmp = new Node<T>(value, current->i, j);
            upNode->down = tmp;
            tmp->right = current;
            tmp->down = current->down;
            current->down = 0;
            _counter++;
            return;
          }
        }
      }
    }

    /**
    @brief innerIterativeAdd

    Si occupa dell'inserimento effettivo e dell'incremento del contatore degli elementi, una volta scartati alcuni "casi base"
    @param value il valore
    @param i la riga
    @param j la colonna
    **/
    void innerIterativeAdd(const T value, const uint i, const uint j) {
      // Se non ho 0 elementi, la i è maggiore/uguale della i della head e
      if (!_head || i < _head->i || _head->i == i && _head->j > j) {
        return; // ERROR
      }

      bool sameRow = false;
      Node<T> *current = _head;
      Node<T> *upNode = 0;

      while(current != 0 && !sameRow) {
        // Se sono nella stessa riga allora smetto di ciclare e chiamo la funzione che si occupa della stessa riga
        if (current->i == i) {
          sameRow = true;
        }
        // Se la riga corrente è minore della nuova riga
        else if (current->i < i) {
          // Ed ho un nodo immediatamente sotto, allora passo al nodo più sotto, salvando il nodo corrente
          if (current->down != 0) {
            upNode = current;
            current = current->down;
          }
          // E non ho nodi sotto, allora aggiungo un nuovo nodo sotto al corrente
          else {
            current->down = new Node<T>(value, i, j);;
            _counter++;
            return;
          }
        }
        // Se la riga corrente è maggiore della nuova riga
        else {
          // E non ho nodi sopra, allora ho un eccezione, dato che questo caso doveva essere gestito dalla iterativeAdd
          if (!upNode) {
            std::cout << "eccezione" << std::endl;
            return; // ECCEZIONE
          }
          // Ed ho un nodo sopra, metto un nuovo nodo tra quello sopra ed il corrente
          Node<T> *tmp = new Node<T>(value, i, j);
          upNode->down = tmp;
          tmp->down = current;
          _counter++;
          return;
        }
      }
      if (sameRow) {
        iterativeColumnAdd(upNode, current, value, i, j);
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
      // Se non ho elementi aggiungo alla testa della lista
      if (_head == 0) {
        _head = new Node<T>(value, i, j);
        _counter++;
      }
      // Se la head ha una i maggiore dell'input allora devo cambiare head
      else if (_head->i > i) {
        Node<T> *nextDown = _head;
        _head = new Node<T>(value, i, j);
        _head->down = nextDown;
        _counter++;
      }
      // Se la head ha i uguale ma ha una j maggiore devo cambiare la head
      else if (_head->i == i && _head->j > j) {
        Node<T> *nextRight = _head;
        _head = new Node<T>(value, i, j);
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
