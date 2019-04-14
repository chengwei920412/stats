/*################################################################################
  ##
  ##   Copyright (C) 2011-2019 Keith O'Hara
  ##
  ##   This file is part of the StatsLib C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

#define STATS_TEST_INPUT_TYPE 1

#include "stats.hpp"
#include "../stats_tests.hpp"

int main()
{
    print_begin("qchisq");

    // settings

    double err_tol = 1E-05;
    int print_level = TEST_PRINT_LEVEL;

    int print_precision_1 = 2;
    int print_precision_2 = 5;

    // parameters

    double dof = 6.0;

    //

    std::vector<double> inp_vals = { 0.1,       0.6,       0.95 };
    std::vector<double> exp_vals = { 2.204131,  6.210757,  12.59159 };

    //
    // scalar tests

    int test_number = 0;

    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,inp_vals[0],exp_vals[0],dof);
    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,inp_vals[1],exp_vals[1],dof);
    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,inp_vals[2],exp_vals[2],dof);

    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,TEST_NAN,TEST_NAN,3);                                      // Input NaNs
    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,0.5,TEST_NAN,TEST_NAN);
    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,TEST_NAN,TEST_NAN,TEST_NAN);

    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,-0.1,TEST_NAN,dof);                                        // p < 0 or p > 1 cases
    STATS_TEST_EXPECTED_QUANT_VAL(qchisq, 1.1,TEST_NAN,dof);

    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,0,0,0);                                                    // dof <= 0
    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,1,TEST_POSINF,0);
    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,1,TEST_NAN,-1.0);
    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,1,TEST_NAN,TEST_NEGINF);

    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,0,0,TEST_POSINF);                                          // dof == Inf
    STATS_TEST_EXPECTED_QUANT_VAL(qchisq,1,TEST_POSINF,TEST_POSINF);

    //
    // vector/matrix tests

#ifdef STATS_TEST_STDVEC_FEATURES
    STATS_TEST_EXPECTED_QUANT_MAT(qchisq,inp_vals,exp_vals,std::vector<double>,dof);
#endif

#ifdef STATS_TEST_MATRIX_FEATURES
    mat_obj inp_mat(2,3);
    inp_mat(0,0) = inp_vals[0];
    inp_mat(1,0) = inp_vals[2];
    inp_mat(0,1) = inp_vals[1];
    inp_mat(1,1) = inp_vals[0];
    inp_mat(0,2) = inp_vals[2];
    inp_mat(1,2) = inp_vals[1];

    mat_obj exp_mat(2,3);
    exp_mat(0,0) = exp_vals[0];
    exp_mat(1,0) = exp_vals[2];
    exp_mat(0,1) = exp_vals[1];
    exp_mat(1,1) = exp_vals[0];
    exp_mat(0,2) = exp_vals[2];
    exp_mat(1,2) = exp_vals[1];

    STATS_TEST_EXPECTED_QUANT_MAT(qchisq,inp_mat,exp_mat,mat_obj,dof);
#endif

    // 

    print_final("qchisq",test_number);

    return 0;
}
