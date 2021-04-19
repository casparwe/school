
#include <math.h>
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <string>
#include <vector>

template <class T>
class Matris{
  private:
     size_t m_rows;
     size_t m_cols;
     size_t m_capacity;
     T * m_vec;

  public:
    static_assert(std::is_move_constructible<T>::value,"Not move constructible");
    static_assert(std::is_move_assignable<T>::value,"Not move assignable");

     // constructors
     explicit Matris () : m_rows(0),m_cols(0),m_capacity(0), m_vec(nullptr){}

     explicit Matris (size_t size) : m_rows(size),m_cols(size),m_capacity(size*size), m_vec(new T [size*size] ()){
       for (unsigned int i = 0; i < m_capacity; i++){
         m_vec[i] = 0;
       }
     }

     explicit Matris (size_t rows, size_t cols) : m_rows(rows),m_cols(cols),m_capacity(rows*cols), m_vec(new T [rows*cols] ()){
       for (unsigned int i = 0; i < m_capacity; i++){
         m_vec[i] = 0;
       }
     }

     Matris (const Matris<T> & toCopy) : m_rows(toCopy.m_rows),m_cols(toCopy.m_cols),m_capacity(toCopy.m_capacity){
       m_vec = new T [toCopy.m_capacity] ();
       for (unsigned int i = 0; i < toCopy.m_capacity; i++ ){
         m_vec[i] = toCopy.m_vec[i];
       }
     }


     Matris (const std::initializer_list <T> initList){
       if (fmod(sqrt(initList.size()),1) != 0){throw std::out_of_range("initializer_list length has to be even root");}
       else {
         m_rows = sqrt(initList.size());
         m_cols = sqrt(initList.size());
         m_capacity = initList.size();
         m_vec = new T [initList.size()] ();

         const T * first = initList.begin();

         for (unsigned int i = 0; i < m_capacity; i++){
           m_vec[i] = first[i];
         }
       }
     }



     ~Matris () {
       delete [] m_vec;
     }

     // operators

     const Matris<T> & operator= (const Matris<T> & Mat);

     void operator+= (const Matris<T> & Mat);

     void operator-= (const Matris<T> & Mat);

     void operator*= (const Matris<T> & Mat);

     T & operator()(unsigned row,unsigned col);

     //const T & operator()(unsigned row,unsigned col);




     Matris<T> operator* (const Matris<T> & right);

     Matris<T> operator+ (const Matris<T> & right);

     Matris<T> operator- (const Matris<T> & right);

     bool operator== (const Matris<T> & right);

     bool operator!= (const Matris<T> & right);


     friend std::istream& operator>>(std::istream& is, Matris<int> & Mat);



     // methods
     void print();

     void setMatrix();

     void transpose();

     typedef T* iterator;

     iterator begin(){return m_vec;}
     iterator end(){return (m_vec + m_capacity);}

     const size_t rows();
     const size_t cols();
     void reset();

     void insert_row(unsigned int row);
     void append_row(unsigned int row);
     void remove_row(unsigned int row);
     void insert_column(unsigned int col);
     void append_column(unsigned int col);
     void remove_column(unsigned int col);

};


template <class T>
void Matris<T>::transpose(){
  T * newVec = new T [m_capacity] ();
  unsigned int i = 0;
  for (unsigned int col = 0; col < m_cols; col++){
    for (unsigned int row = 0; row < m_rows; row++ ){
      newVec[i] = m_vec[col + row * m_cols];
      i ++;
    }
  }

  delete [] m_vec;
  m_vec = newVec;

  size_t tmp = m_cols;
  m_cols = m_rows;
  m_rows = tmp;
}

template <class T>
void Matris<T>::append_row(unsigned int row){
  m_rows += 1;
  m_capacity += m_cols;
  T * newVec = new T [m_capacity] ();
  unsigned int j = 0;
  for (unsigned int i = 0; i < m_capacity; i++){
    if (i == (row + 1) * m_cols){i += m_cols;}
    newVec[i] = m_vec[j];
    j ++;
  }
  delete [] m_vec;
  m_vec = newVec;
}


template <class T>
void Matris<T>::append_column(unsigned int col){
  m_cols += 1;
  m_capacity += m_rows;
  T * newVec = new T [m_capacity] ();
  unsigned int j = 0;
  for (unsigned int i = 0; i < m_capacity; i++){
    if (i % m_cols == col + 1){i ++;}
    newVec[i] = m_vec[j];
    j ++;
  }
  delete [] m_vec;
  m_vec = newVec;
}


template <class T>
void Matris<T>::insert_row(unsigned int row){
  m_rows += 1;
  m_capacity += m_cols;
  T * newVec = new T [m_capacity] ();
  unsigned int j = 0;
  for (unsigned int i = 0; i < m_capacity; i++){
    if (i == row * m_cols){i += m_cols;}
    newVec[i] = m_vec[j];
    j ++;
  }
  delete [] m_vec;
  m_vec = newVec;
}


template <class T>
void Matris<T>::insert_column(unsigned int col){
  m_cols += 1;
  m_capacity += m_rows;
  T * newVec = new T [m_capacity] ();
  unsigned int j = 0;
  for (unsigned int i = 0; i < m_capacity; i++){
    if (i % m_cols == col){i ++;}
    newVec[i] = m_vec[j];
    j ++;
  }
  delete [] m_vec;
  m_vec = newVec;
}

template <class T>
void Matris<T>::remove_row(unsigned int row){
  m_rows -= 1;
  m_capacity -= m_cols;
  T * newVec = new T [m_capacity] ();
  unsigned int j = 0;
  for (unsigned int i = 0; i < m_capacity; i++){
    if (i == row * m_cols){j += m_cols;}
    newVec[i] = m_vec[j];
    j ++;
  }
  delete [] m_vec;
  m_vec = newVec;
}

template <class T>
void Matris<T>::remove_column(unsigned int col){
  m_cols -= 1;
  m_capacity -= m_rows;
  T * newVec = new T [m_capacity] ();
  unsigned int j = 0;
  for (unsigned int i = 0; i < m_capacity; i++){
    if (i % m_cols == col){j ++;}
    newVec[i] = m_vec[j];
    j ++;
  }
  delete [] m_vec;
  m_vec = newVec;
}


template <class T>
void Matris<T>::reset(){
  m_rows = 0;
  m_cols = 0;
  m_capacity = 0;
  delete [] m_vec;
  m_vec = new T [0] ();
}


template <class T>
Matris<T> identity(unsigned int msize){
  Matris<T> Mat(msize);
  for (unsigned int i = 0; i < msize; i++){
    Mat(i,i) += 1;
  }

  return Mat;
}

template <class T>
const size_t Matris<T>::rows(){return m_rows;}


template <class T>
const size_t Matris<T>::cols(){return m_cols;}


template <class T>
void Matris<T>::print(){
  //std::cout<<"m_rows = "<<m_rows<<"\n"<<"m_cols = "<<m_cols<<std::endl;
  for (unsigned int i = 0; i < m_rows ; i++){
     for (unsigned int j = 0; j < m_cols; j++){
       std::cout<<m_vec[j + i * m_cols]<<" ";
     }
 std::cout<<std::endl;
 }
 std::cout<<std::endl;
}

template <class T>
const Matris<T>& Matris<T>::operator= (const Matris<T> & Mat){
  m_rows = Mat.m_rows;
  m_cols = Mat.m_cols;
  m_capacity = Mat.m_capacity;
  T * newVec = new T [Mat.m_capacity];
  for (unsigned int i = 0; i < Mat.m_capacity; i++ ){
    newVec[i] = Mat.m_vec[i];
  }
  delete [] m_vec;
  m_vec = newVec;
  return Mat;
}

template <class T>
void Matris<T>::operator+= (const Matris<T> & Mat){
  if (m_rows != Mat.m_rows || m_cols != Mat.m_cols){throw std::out_of_range("cant add matrix of different size");}
  else {
    for (unsigned int i = 0; i < Mat.m_capacity; i++ ){
      m_vec[i] += Mat.m_vec[i];
    }
  }
}


template <class T>
void Matris<T>::operator-= (const Matris<T> & Mat){
  if (m_rows != Mat.m_rows || m_cols != Mat.m_cols){throw std::out_of_range("cant subtract matrix of different size");}
  else {
    for (unsigned int i = 0; i < Mat.m_capacity; i++ ){
      m_vec[i] -= Mat.m_vec[i];
    }
  }
}

template <class T>
void Matris<T>::operator*= (const Matris<T> & Mat){
  if (m_cols != Mat.m_rows){throw std::out_of_range("non match for multiplication");}
  else {


    size_t newRows = m_rows;
    size_t newCols = Mat.m_cols;
    size_t newCap = newCols * newRows;
    T * newVec = new T [newCols*newRows] ();


    for (unsigned int i = 0; i < newRows; i++){
      for (unsigned int j = 0; j < newCols; j++){
        for (unsigned int k = 0; k < m_cols; k++){
          newVec[j + i*newCols] += Mat.m_vec[j + k*Mat.m_cols] * m_vec[k + i * m_cols];
        }
      }
    }


    delete [] m_vec;


    m_cols = newCols;
    m_rows = newRows;
    m_capacity = newCap;
    m_vec = newVec;
  }
}


template <class T>
Matris<T> Matris<T>::operator* (const Matris<T> & Mat){
  if (m_cols != Mat.m_rows){throw std::out_of_range("non match for multiplication");}
  else {
    Matris<T> nyMat(m_rows,Mat.m_cols);

    for (unsigned int i = 0; i < nyMat.m_rows; i++){
      for (unsigned int j = 0; j < nyMat.m_cols; j++){
        for (unsigned int k = 0; k < m_cols; k++){
          nyMat.m_vec[j + i*Mat.m_cols] += Mat.m_vec[j + k*Mat.m_cols] * m_vec[k + i * m_cols];
        }
      }
    }
    return nyMat;
  }
}


template <class T>
Matris<T> Matris<T>::operator+ (const Matris<T> & Mat){
  if (m_rows != Mat.m_rows || m_cols != Mat.m_cols){throw std::out_of_range("cant add matrix of different size");}
  else {
    Matris<T> nyMat(Mat);
    for (unsigned int i = 0; i < m_capacity; i++ ){
      nyMat.m_vec[i] += m_vec[i];
    }
    return nyMat;
  }
}

template <class T>
Matris<T> Matris<T>::operator- (const Matris<T> & Mat){
  if (m_rows != Mat.m_rows || m_cols != Mat.m_cols){throw std::out_of_range("cant add matrix of different size");}
  else {
    Matris<T> nyMat(*this);
    for (unsigned int i = 0; i < m_capacity; i++ ){
      nyMat.m_vec[i] -= Mat.m_vec[i];
    }
    return nyMat;
  }
}

template <class T>
T & Matris<T>::operator()(unsigned row,unsigned col){
  return m_vec[row*m_cols + col];
}

/*
template <class T>
const T & Matris<T>::operator()(unsigned row,unsigned col){
  const T tmp= m_vec[row*m_cols + col];
  return tmp;
}*/

template <class T>
std::ostream& operator<<(std::ostream& os, Matris<T> & Mat) {
    size_t rows = Mat.rows();
    size_t cols = Mat.cols();
    for (unsigned int i = 0; i < rows; i++){
      for (unsigned int j = 0; j < cols; j++){
        os << Mat(i,j);
        if (j+1 != cols){os << ",";}
      }
      os << ";";
    }
    os << "\n";
    return os;}

//template <class T>


std::istream& operator>>(std::istream& is, Matris<int> & Mat) {

  std::string strInput;

  is >> strInput;

  const std::string::iterator strPtr = strInput.begin();

  const std::string::iterator strEnd = strInput.end();

  size_t strLen = strInput.size();

  if(*(strEnd-1) != ';'){throw "invalid matrix input formatting";}

  size_t rows = 0;
  size_t cols = 0;
  size_t cols_prev = 0;

  size_t i = 0;
  size_t int_len = 0;

  int * inputs = new int [strLen];
  size_t mat_len = 0;

  while(i < strLen){
    cols ++;
    while(*(strPtr + i) != ',' && *(strPtr + i) != ';'){
      int_len ++;
      i++;
    }

    inputs[mat_len] = std::stoi(strInput.substr(i-int_len,int_len));
    mat_len++;
    int_len = 0;

    if (*(strPtr + i) == ';'){
      rows ++;
      if(cols_prev > 0 && cols_prev != cols){throw "invalid matrix dimensions";}
      else{cols_prev = cols;cols = 0;}
    }

    i++;
  }

  Mat.m_capacity = mat_len;
  Mat.m_vec = new int [mat_len] ();
  Mat.m_rows = rows;
  Mat.m_cols = cols_prev;

  for(size_t j = 0;j<mat_len;j++){
    Mat.m_vec[j] = inputs[j];
  }

  delete[] inputs;

  return is;
}
