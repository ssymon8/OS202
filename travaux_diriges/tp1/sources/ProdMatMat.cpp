#include <algorithm>
#include <cassert>
#include <iostream>
#include <thread>
#if defined(_OPENMP)
#include <omp.h>
#endif
#include "ProdMatMat.hpp"

namespace {
void prodSubBlocks(int iRowBlkA, int iColBlkB, int iColBlkA, int szBlock,
                   const Matrix& A, const Matrix& B, Matrix& C) {
  #pragma omp parallel for
  for (int j = iRowBlkA; j< std::min(A.nbCols, iRowBlkA + szBlock); ++j)
    for (int k = iColBlkA; k < std::min(A.nbCols, iColBlkA + szBlock); k++)
      for (int i = iColBlkB; i < std::min(B.nbRows, iColBlkB + szBlock); i++)
        C(i, j) += A(i, k) * B(k, j);
}
const int szBlock = 64;
}  // namespace

Matrix operator*(const Matrix& A, const Matrix& B) {
  Matrix C(A.nbRows, B.nbCols, 0.0);
  # pragma omp parallel for collapse(2)
  for (int jb=0; jb < B.nbCols; jb += szBlock )
      for (int kb=0; kb<A.nbCols; kb += szBlock )
          for(int ib=0; ib<A.nbRows; ib += szBlock)
              prodSubBlocks(ib, jb, kb, szBlock, A, B, C);
  //prodSubBlocks(0, 0, 0, std::max({A.nbRows, B.nbCols, A.nbCols}), A, B, C);
  return C;
}
