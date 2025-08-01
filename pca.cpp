/*
* generated using Gemini 2.5 flash in a google search of "armadillo c++ pca svd".
*
* search query inputter: Peratham Wiriyathammabhum
*/
#include <armadillo>

int main() {
    arma::mat data = arma::randu<arma::mat>(10, 5); // Example data matrix (rows are samples, columns are features)

    // 1. Center the data
    arma::mat centered_data = data.each_row() - arma::mean(data);

    // 2. Compute SVD of the centered data
    arma::mat U, V;
    arma::vec s;
    arma::svd(U, s, V, centered_data);

    // 3. The columns of V are the principal components
    // You can select the desired number of principal components based on the singular values (s)

    V.print("Principal Components (V matrix from SVD):");

    return 0;
}
