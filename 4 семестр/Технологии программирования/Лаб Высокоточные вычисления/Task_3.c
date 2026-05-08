#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>
#include <stdint.h>

int main() 
{
    printf("\nБиблиотека GMP\n");
    int z_x, z_y, z_x2, z_x4, z_2y, z_2y2, z_y2, z_y2_plus_1, z_part2, z_res;
    mpz_inits(z_x, z_y, z_x2, z_x4, z_2y, z_2y2, z_y2, z_y2_plus_1, z_part2, z_res, NULL);
    
    mpz_set_ui(z_x, 665857);
    mpz_set_ui(z_y, 470832);
    
    mpz_mul(z_x2, z_x, z_x);                    // x^2
    mpz_mul(z_x4, z_x2, z_x2);                  // (x^2)^2
    mpz_mul_ui(z_2y, z_y, 2);                   // 2y
    mpz_mul(z_2y2, z_2y, z_2y);                 // (2y)^2
    mpz_mul(z_y2, z_y, z_y);                    // y^2
    mpz_add_ui(z_y2_plus_1, z_y2, 1);           // (y^2 + 1)
    mpz_mul(z_part2, z_2y2, z_y2_plus_1);       // (2y)^2 * (y^2 + 1)
    mpz_sub(z_res, z_x4, z_part2);              // (x^2)^2 - (2y)^2 * (y^2 + 1)
    
    gmp_printf("Результат GMP: %Zd\n", z_res);
    mpz_clears(z_x, z_y, z_x2, z_x4, z_2y, z_2y2, z_y2, z_y2_plus_1, z_part2, z_res, NULL);


    printf("\nБиблиотека MPFR\n");
    mpfr_prec_t prec = 256; // точность в битах
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
    
    printf("Результат MPFR: ");
    mpfr_out_str(stdout, 10, 0, q, MPFR_RNDN);
    printf("\n");
    
    mpfr_clears(x, y, x2, x4, y2, two_y, two_y_sq, y2_plus_1, part2, q, (mpfr_ptr) 0);
    return 0;
}
