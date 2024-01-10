/* establish ability to return values */
int life_universe_everything()
{
	return 42;
}

/* establish ability to operate on arguments */
int add(int a, int b)
{
	return a + b;
}

/* establish flag testing/setting,
	attempt to exercise many LowLevelILFlagCondition

	returns 7 (true) and 13 (false) instead of 1, 0 to avoid compiler
	generating bit tricks to quickly set return value */
unsigned int test_byte_e_10(unsigned char a)
{
	if(a == 10) return 7;
	return 13;
}

unsigned int test_byte_ne_10(unsigned char a)
{
	if(a != 10) return 7;
	return 13;
}

unsigned int test_byte_slt_10(signed char a)
{
	if(a < 10)
		return 7;
	else
		return 13;
}

unsigned int test_byte_ult_10(unsigned char a)
{
	if(a < 10)
		return 7;
	else
		return 13;
}

unsigned int test_byte_sle_10(signed char a)
{
	if(a <= 10)
		return 7;
	else
		return 13;
}

unsigned int test_byte_ule_10(unsigned char a)
{
	if(a <= 10)
		return 7;
	else
		return 13;
}

unsigned int test_byte_sge_10(signed char a)
{
	if(a >= 10)
		return 7;
	else
		return 13;
}

unsigned int test_byte_uge_10(unsigned char a)
{
	if(a >= 10)
		return 7;
	else
		return 13;
}

unsigned int test_byte_sgt_10(signed char a)
{
	if(a > 10)
		return 7;
	else
		return 13;
}

unsigned int test_byte_ugt_10(unsigned char a)
{
	if(a > 10)
		return 7;
	else
		return 13;
}

unsigned int test_byte_neg(signed char a)
{
	if(a < 0)
		return 7;
	else
		return 13;
}

unsigned int test_byte_pos(signed char a)
{
	if(a >= 0)
		return 7;
	else
		return 13;
}

//

unsigned int test_word_e_10(unsigned short a)
{
	if(a == 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_ne_10(unsigned short a)
{
	if(a != 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_slt_10(signed short a)
{
	if(a < 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_ult_10(unsigned short a)
{
	if(a < 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_sle_10(signed short a)
{
	if(a <= 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_ule_10(unsigned short a)
{
	if(a <= 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_sge_10(signed short a)
{
	if(a >= 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_uge_10(unsigned short a)
{
	if(a >= 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_sgt_10(signed short a)
{
	if(a > 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_ugt_10(unsigned short a)
{
	if(a > 10)
		return 7;
	else
		return 13;
}

unsigned int test_word_neg(signed short a)
{
	if(a < 0)
		return 7;
	else
		return 13;
}

unsigned int test_word_pos(signed short a)
{
	if(a >= 0)
		return 7;
	else
		return 13;
}

/* establish ability to loop and conditionally jump */
int triangle_up(int a)
{
    int i, result = 0;
    for(i=1; i<=a; ++i)
    {
        result += i;
    }

    return result;
}

int triangle_down(int a)
{
    int i, result = 0;
    for(i=a; i>0; --i)
    {
        result += i;
    }

    return result;
}

/* this is pretty hard if arch doesn't have a mul instruction */
unsigned char multiply_u8(unsigned char a, unsigned char b)
{
	return a * b;
}

int multiply(int a, int b)
{
	return a * b;
}

int multiply_loop(int a, int b)
{
	int i;
	int result = 0;
	int neg = 1;

	if(b < 0) {
		b = -b;
		neg = -neg;
	}

	for(i=0; i<b; ++i) {
		result = result + a;
	}

	return neg * result;
}

int div(int a, int b)
{
	return a / b;
}

int mod(int a, int b)
{
	return a % b;
}

/* "_dummy" because exp() is built-in in some compilers */
int exp_dummy(int base, int e)
{
	int i;
	int result = 1;

	if(base == 0)
		return 0;

	for(i=0; i<e; ++i)
		result = result * base;

	return result;
}

int expmod(int base, int e, int m)
{
	int result = 1;
	int runner = base;

	if(base == 0)
		return 0;

	while(e) {
		if(e & 1) {
			result = (result * runner) % m;
		}

		runner = (runner * runner) % m;
		e = e >> 1;
	}

	return result;
}

int gcd(int a, int b)
{
	int result;

	while(1) {
		if(a == 0) {
			result = b;
			break;
		}
		if(b == 0) {
			result = a;
			break;
		}

		if(a > b)
			a = a % b;
		else
			b = b % a;
	}

	return result;
}

int gcd_recursive(int a, int b)
{
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == b) return a;
	if(a > b) return gcd_recursive(a - b, b);
	return gcd_recursive(a, b - a);
}

int switch_doubler(unsigned int a)
{
	int result;

	switch(a) {
		case 0: result=0; break;
		case 1: result=2; break;
		case 2: result=4; break;
		case 3: result=6; break;
		case 4: result=8; break;
		case 5: result=10; break;
		case 6: result=12; break;
		case 7: result=14; break;
		case 8: result=16; break;
		case 9: result=18; break;
		case 10: result=20; break;
		default: result=-1;
	}

	return result;
}

int factorial(int n)
{
	if(n <= 1)
		return 1;
	else
		return n * factorial(n-1);
}

/* primitive floating point */
float fp_single_add(float a, float b)
{
	return a + b;
}

float fp_single_sub(float a, float b)
{
	return a - b;
}

float fp_single_mul(float a, float b)
{
	return a * b;
}

float fp_single_div(float a, float b)
{
	return a / b;
}

/*
void test()
{
	float tmp = fp_single_div(1.0, 2.0);
	tmp = fp_single_div(3.57, 11.13);
}
*/

float fp_convert_double_to_single(double a)
{
	return a;
}

float fp_convert_double_product_to_single(double a, double b)
{
	return a * b;
}

#ifdef ARCH_Z80
int main()
{
	return -1;
}
#endif

