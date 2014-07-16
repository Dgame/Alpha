#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

int readNumber(const std::string& buf) {
	int num = 0;

	const char* pos = &buf[0];
	const char* const end = &buf[buf.size()] + 1;

	bool negate = false;
	if (*pos == '-') {
		negate = true;
		pos++;
	}

	do {
		num *= 10;
		num += *pos - '0';

		++pos;
	} while (pos != end && std::isdigit(*pos));

	if (negate)
		num *= -1;

	return num;
}

bool EndsWith(const std::string& a, const std::string& b) {
	if (b.size() > a.size())
		return false;

	return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

int main() {
	std::cout << "Remove old results..." << std::endl;

	remove("test_results.txt");

	std::cout << "Testing..." << std::endl;

	freopen("test_results.txt", "w", stdout);
	system("test.bat");
	fclose(stdout);
	freopen("CONOUT$", "w", stdout);

	std::cout << "Compare..." << std::endl;

	const std::vector<int> expected_results = {
		42, 6, -2, 8, 2, 2, 7, 9, 14, 23, 23, 6,
		-2, 8, 2, 0, 4, 0, 4, 1, 1, 44, -40, 84,
		21, 2, 2, 8, 6, 10, 22, 10, 10, 3, 88, 99
	};

	std::ifstream test("test_results.txt");

	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

	for (unsigned int i = 0; i < 39; i++) {
		const bool inside = i < expected_results.size();
		std::string buf;
		std::getline(test, buf);

		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << "#" << i;

		if (inside) {
			std::cout << " Get: " << buf << "\t\t Expected: " << expected_results[i] << "\t -> ";
		} else {
			std::cout << " just a check for correct compilation -> ";
		}

		if (!inside) {
			if (buf.size() == 0) {
				SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
				std::cout << "Compiled" << std::endl;
			} else {
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "Error" << std::endl;
			}
		} else if (readNumber(buf) == expected_results[i]) {
			SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
			std::cout << "Valid" << std::endl;
		} else {
			SetConsoleTextAttribute(handle, FOREGROUND_RED);

			if (buf.substr(0, 5) == "Error" || EndsWith(buf, "denied"))
				std::cout << "Error" << std::endl;
			else
				std::cout << "Invalid" << std::endl;
		}
	}

	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Finish" << std::endl;

	return 0;
}