int main()
{
	int t[3];
	int i;
	t[0] = 1;
	for(i = 0; i < 3; i++)
		t[i] = t[i-1] + 2;
	for(i = 0; i < 3; i++)
		printint(t[i]);
	printint(fact(10));
}
int fact(int x)
{
	if(x == 0)
		return 1;
	else
		return fact(x-1)*x;
}

