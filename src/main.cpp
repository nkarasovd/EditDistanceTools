#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

#include <bits/stdc++.h>
using namespace std;


double min(double x, double y, double z) { return min(min(x, y), z); }


double editDistLevenshtein(
    vector<int> seq_1,
    vector<int> seq_2,
    vector<double> weights_1,
    vector<double> weights_2,
    int m, int n
    )
{
    double dp[m + 1][n + 1];

    dp[0][0] = 0.0;

    for (int j = 1; j <= n; j++) {
        dp[0][j] = weights_2[j - 1] + dp[0][j - 1];
    }

    for (int i = 1; i <= m; i++) {
        dp[i][0] = weights_1[i - 1] + dp[i - 1][0];

        for (int j = 1; j <= n; j++) {
            if (seq_1[i - 1] == seq_2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j]
                    = min(
                    dp[i][j - 1] + weights_2[j - 1], // Insert
                    dp[i - 1][j] + weights_1[i - 1], // Remove
                    dp[i - 1][j - 1] + weights_1[i - 1] + weights_2[j - 1]  // Replace
                    );
        }
    }

    return dp[m][n];
}


double max(double x, double y, double z) { return max(max(x, y), z); }


double cost(int i, int j, double c, double o) {
    return exp(-c * min(i, j)) * exp(-o * abs(i - j));
}


double reBucketSimilarity(
    vector<int> stack_1,
    vector<int> stack_2,
    int m, int n,
    double c, double o
    )
{
    double sim_matrix[m + 1][n + 1] = {0.0};

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (stack_1[i - 1] == stack_2[j - 1])
                double x = cost(i - 1, j - 1, c, o);
            else
                double x = 0.0;

            sim_matrix[i][j] = max(
                sim_matrix[i - 1][j - 1] + x,
                sim_matrix[i - 1][j],
                sim_matrix[i][j - 1]
            );
        }
    }

    double denominator = 0.0;

    for (int i = 0; i <= int(min(m, n)); i++) {
        denominator += exp(c * i);
    }

    return sim_matrix[m][n] / denominator;
}

namespace py = pybind11;

PYBIND11_MODULE(edit_distance_tools, m) {
    m.doc() = R"pbdoc(
        Pybind11 edit distance tools plugin
        -----------------------

        .. currentmodule:: edit_distance_tools

        .. autosummary::
           :toctree: _generate

           editDistLevenshtein
    )pbdoc";

    m.def("weighted_levenshtein", &editDistLevenshtein, R"pbdoc(
        Weighted Levenshtein distance.
    )pbdoc");

    m.def("rebucket_similarity", &reBucketSimilarity, R"pbdoc(
        ReBucket similarity.
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
