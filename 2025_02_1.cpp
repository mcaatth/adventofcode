#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h> // for very big numbers of type __int128

typedef unsigned long ulong;

bool isEven(ulong k) {
	if (k % 2 == 0) {
		return true;
	} else {
		return false;
	}
}

ulong mthPowerOfTen(ulong m)
{
	ulong out = 1;
	for (ulong i = 1; i < m + 1; i++) {
		out *= 10;
	}
	return out;
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

bool checkIfInvalid(ulong number) {
	std::string str = std::to_string(number);
	int howManyDigits = str.length();
	if (isEven(howManyDigits)) {
		if (number / mthPowerOfTen(howManyDigits / 2) == number % mthPowerOfTen(howManyDigits / 2)) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
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

	//for given test input it shall return 1227775554
	std::cout << toString(output);
}
