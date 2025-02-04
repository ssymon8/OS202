# include "Matrix.hpp"
# include <cassert>

Matrix::Matrix( int nRows, int nCols ) :
  nbRows{nRows}, nbCols{nCols}, m_arr_coefs(nRows*nCols)
{}
// ------------------------------------------------------------------------
Matrix::Matrix( int nRows, int nCols, double val ) :
  nbRows{nRows}, nbCols{nCols}, m_arr_coefs(nRows*nCols, val)
{}
// ========================================================================
Matrix Matrix::get_submatrix(int startRow, int startCol, int blockRows, int blockCols) const {
    Matrix submatrix(blockRows, blockCols);
    for (int i = 0; i < blockRows; ++i) {
        for (int j = 0; j < blockCols; ++j) {
            submatrix(i, j) = (*this)(startRow + i, startCol + j);
        }
    }
    return submatrix;
}