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

/* establish flag testing/setting */
int is_greater_10(int a)
{
	return a > 10;
}

int is_less_than_equal_10(int a)
{
	return a <= 10;
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

/* "_dummy" because exp() is built-in in some compilers */
int exp_dummy(int base, int e)
{
	int i;
	int result = 1;

	for(i=0; i<e; ++i)
		result = result * base;

	return result;
}

int expmod(int base, int e, int m)
{
	int result = 1;
	int runner = base;

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

int switch_doubler(int a)
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

#ifdef ARCH_Z80
int main()
{
	return -1;
}
#endif

