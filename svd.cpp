/*
* generated using Gemini 2.5 flash in a google search of "armadillo c++ pca svd".
*
* search query inputter: Peratham Wiriyathammabhum
*/
  
#include <armadillo>

int main() {
    arma::mat A = arma::randu<arma::mat>(5, 3); // Example matrix
    arma::mat U, V;
    arma::vec s;

    arma::svd(U, s, V, A); // Compute SVD of matrix A

    // U, s, and V now contain the SVD components
    U.print("U:");
    s.print("s:");
    V.print("V:");

    return 0;
}
