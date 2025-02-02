void main() {
	printByValue(true);
	printByValue(false);
	printByValuee(false);
	printByValuee(false);
	if(true)
    {
        print("true");
    }
    if(false or false and  true)
    {
        print("true");
    }
}

void printByValue(bool val) {
    int x = 5;
    printi(x); 
	if (val)
		print("val is true");
	else {
		print("val is false");
	}
}

void printByValuee(bool val) {
    int x = 3;
    printi(x); 
	if (val)
		print("val is true");
	else {
		print("val is false");
	}
}