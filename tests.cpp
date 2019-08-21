int multiply(int a, int b)
{
	return a * b;
}

int multiply_loop(int a, int b)
{
	int result = 0;

	for(int i=0; i<b; ++i) {
		result = result + a;
	}

	if(b < 0) {
		result = result * -1;
	}

	return result;
}

int exp(int base, int e)
{
	int result = 1;

	for(int i=0; i<e; ++i)
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

// TODO: recursive gcd

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
