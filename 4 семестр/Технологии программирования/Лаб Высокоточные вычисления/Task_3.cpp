#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <gmpxx.h>
#include <mpfr.h>

int main() 
{
    std::cout << "Библиотека GMP\n";
    // Класс mpz_class из gmpxx.h автоматически управляет памятью и позволяет использовать перегрузку операторов.
    mpz_class x_gmp = 665857;
    mpz_class y_gmp = 470832;
    mpz_class res_gmp = (x_gmp * x_gmp) * (x_gmp * x_gmp) - (2 * y_gmp) * (2 * y_gmp) * (y_gmp * y_gmp + 1);
    std::cout << "Результат GMP: " << res_gmp << "\n\n";

    std::cout << "Библиотека MPFR\n";
    mpfr_prec_t prec = 256;
    mpfr_t x, y, x2, x4, y2, two_y, two_y_sq, y2_plus_1, part2, q;
    mpfr_inits2(prec, x, y, x2, x4, y2, two_y, two_y_sq, y2_plus_1, part2, q, (mpfr_ptr) 0);
    
    mpfr_set_ui(x, 665857, MPFR_RNDN);
    mpfr_set_ui(y, 470832, MPFR_RNDN);
    
    mpfr_mul(x2, x, x, MPFR_RNDN);
    mpfr_mul(x4, x2, x2, MPFR_RNDN);
    mpfr_mul(y2, y, y, MPFR_RNDN);
    mpfr_mul_ui(two_y, y, 2, MPFR_RNDN);
    mpfr_mul(two_y_sq, two_y, two_y, MPFR_RNDN);
    mpfr_add_ui(y2_plus_1, y2, 1, MPFR_RNDN);
    mpfr_mul(part2, two_y_sq, y2_plus_1, MPFR_RNDN);
    mpfr_sub(q, x4, part2, MPFR_RNDN);
    
    std::cout << "Результат MPFR: ";
    mpfr_out_str(stdout, 10, 0, q, MPFR_RNDN);
    std::cout << "\n";
    
    mpfr_clears(x, y, x2, x4, y2, two_y, two_y_sq, y2_plus_1, part2, q, (mpfr_ptr) 0);

    return 0;
}
