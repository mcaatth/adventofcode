// Too complicated. What is the complexity?

// The idea is to take all factors of the length
// of given number, "rotate" such a number by
// every one of them and check if the output
// after every rotation is the same as input.

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h> // for very big numbers of type __int128

typedef unsigned long ulong;

ulong mthPowerOfTen(ulong m)
{
	ulong out = 1;
	for (ulong i = 1; i < m + 1; i++) {
		out *= 10;
	}
	return out;
}

// n not included, 1 included
std::vector<int> factorsOfLength(ulong n) {
    std::string str = std::to_string(n);
	int howManyDigits = str.length();
    std::vector<int> factors;
    for (int i = 1; i < howManyDigits; i++) {
        if (howManyDigits % i == 0) { factors.push_back(i); }
    }
    return factors;
}

// I took this function from the internet
// it helps to print __int128 (not printable via cout)
std::string toString(__int128 x) {
	if (x == 0) return "0";
	bool neg = false;
	if (x < 0) {
		neg = true;
		x = -x;
	}
	std::string s;
	while (x > 0) {
		int digit = (int)(x % 10);
		s.push_back('0' + digit);
		x /= 10;
	}
	if (neg) s.push_back('-');
	std::reverse(s.begin(), s.end());
	return s;
}

bool rotateAndCompare(int shift, ulong input) {
    std::string str = std::to_string(input);
	int howManyDigits = str.length();
    ulong output = input / mthPowerOfTen(shift) + (input % mthPowerOfTen(shift)) * mthPowerOfTen(howManyDigits -  shift);
    return (output == input);
}

bool checkIfInvalid(ulong number) {
	std::string str = std::to_string(number);
	int howManyDigits = str.length();
	std::vector<int> factors = factorsOfLength(number);
	for (ulong i : factors) {
		    if (rotateAndCompare(i, number)) { return true; }
	}
	return false;
}

void checkRange(ulong first, ulong last, __int128& output) {
	for (ulong i = first; i < last + 1; i++) {
		if (checkIfInvalid(i) == true) {
			output += i;
		}
	}
}

int main()
{
	__int128 output = 0;
	ulong firstNumberInRange;
	ulong lastNumberInRange;
	std::ifstream file("input.txt");
	char ch;

	if (file.is_open()) {

        // I don't like this repeated part
		file >> firstNumberInRange;
		file.get(ch);
		file >> lastNumberInRange;
		checkRange(firstNumberInRange, lastNumberInRange, output);

		while (file.get(ch)) {
			file >> firstNumberInRange;
			file.get(ch);
			file >> lastNumberInRange;
			checkRange(firstNumberInRange, lastNumberInRange, output);
		}
	} else {
		std::cout << "Unable to open input file" << std::endl;
	}

	//for given test input it shall return 4174379265
	std::cout << toString(output);
}
