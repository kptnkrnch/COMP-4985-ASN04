#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main() {
	int sameCount = 0;
	int totalRuns = 10000000;
	for (int i = 0; i < totalRuns; i++) {
		int count = 0;
		for (int n = 0; n < 3; n++) {
			int roll = rand() % 2;
			if (roll == 0) {
				count++;
			}
		}
		if (count == 3) {
			if (totalRuns < 1000) {
				cout << "All the same!" << endl;
			}
			sameCount++;
		} else {
			if (totalRuns < 1000) {
				cout << "Not the same!" << endl;
			}
		}
	}
	double odds = ((double)sameCount) / totalRuns;
	cout << "The odds are: " << odds << endl;
	_getch();
	return 0;
}
