#include <iostream>
#include <string>
#include <conio.h>
#include <sstream>
#include <cstdlib>
#include <cstdint>

using namespace std;

class BigInt {
public:
	int data[256];
	static const int size = 256;

	BigInt() {
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
	}

	BigInt(int number) {
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}

		if (number != 0) {
			string temp = "";
			stringstream ss;
			ss << number;
			temp = ss.str();

			if (temp.size() <= size) {
				int index = size - temp.size();
				for (int i = 0; index < size; i++, index++) {
					char num = temp.at(i);
					data[index] = atoi(&num);
				}
			}
		}
	}

	void Init() {
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
	}

	static void Copy(BigInt source, BigInt * destination) {
		for (int i = 0; i < size; i++) {
			destination->data[i] = source.data[i];
		}
	}

	void SetNumber(int number) {
		Init();
		if (number != 0) {
			string temp = "";
			stringstream ss;
			ss << number;
			temp = ss.str();

			if (temp.size() <= size) {
				int index = size - temp.size();
				for (int i = 0; index < size; i++, index++) {
					char num = temp.at(i);
					data[index] = atoi(&num);
				}
			}
		}
	}

	void SetNumber(int number[]) {
		Init();
		for (int i = 0; i < size; i++) {

		}
	}

	void Power(int exponent) {
		BigInt temp;
		Copy(*this, &temp);
		if (exponent == 0) {
			temp.SetNumber(1);
		}
		for (int i = 0; i < exponent - 1; i++) {
			temp.Multiply(*this);
			//temp.PrintNumber();
		}
		Copy(temp, this);
	}

	void Multiply(BigInt number) {
		BigInt numbers[size];
		for (int i = 0; i < size; i++) {
			numbers[i].Init();
		}

		for (int n = 0; n < size; n++) {
			for (int i = size - 1; i >= 0; i--) {
				int temp = number.data[(size - 1 - n)] * data[i];
				if (temp < 10 && temp != 0) {
					int addtemp = temp + numbers[n].data[i - n];
					if (addtemp < 10) {
						numbers[n].data[i - n] = addtemp;
					} else {
						for (int tempIa = i - 1 - n; tempIa >= 0; tempIa--) {
							int temp1a = ((addtemp - (addtemp % 10))/10);
							int temp2a = (addtemp % 10);
						
							numbers[n].data[tempIa + 1] = temp2a;
							addtemp = numbers[n].data[tempIa] + temp1a;
							if (addtemp < 10) {
								numbers[n].data[tempIa] = addtemp;
								break;
							}
						}
					}
				} else {
					for (int tempI = i - 1 - n; tempI >= 0; tempI--) {
						int temp1 = ((temp - (temp % 10))/10);
						int temp2 = (temp % 10);
						
						int addtemp = numbers[n].data[tempI + 1] + temp2;
						if (addtemp < 10) {
							numbers[n].data[tempI + 1] = addtemp;
						} else {
							for (int tempIa = tempI; tempIa >= 0; tempIa--) {
								int temp1a = ((addtemp - (addtemp % 10))/10);
								int temp2a = (addtemp % 10);
						
								numbers[n].data[tempIa + 1] = temp2a;
								addtemp = numbers[n].data[tempIa] + temp1a;
								if (addtemp < 10) {
									numbers[n].data[tempIa] = addtemp;
									break;
								}
							}
						}

						temp = numbers[n].data[tempI] + temp1;
						if (temp < 10) {
							numbers[n].data[tempI] = temp;
							break;
						}
					}
				}
			}
		}

		Init();
		for (int i = 0; i < size; i++) {
			Add(numbers[i]);
		}
	}

	void Multiply2(BigInt number) {
		BigInt numbers[size];
		for (int i = 0; i < size; i++) {
			numbers[i].Init();
		}
		PrintNumber();
		cout << "--------------------------------------------------------" << endl;
		for (int n = 0; n < size; n++) {
			for (int i = size - 1; i >= 0; i--) {
				int temp = number.data[(size - 1 - n)] * data[i];
				if (temp < 10 && temp != 0) {
					int addtemp = temp + numbers[n].data[i - n];
					if (addtemp < 10) {
						numbers[n].data[i - n] = addtemp;
					} else {
						for (int tempIa = i - 1 - n; tempIa >= 0; tempIa--) {
							int temp1a = ((addtemp - (addtemp % 10))/10);
							int temp2a = (addtemp % 10);
						
							numbers[n].data[tempIa + 1] = temp2a;
							addtemp = numbers[n].data[tempIa] + temp1a;
							if (addtemp < 10) {
								numbers[n].data[tempIa] = addtemp;
								break;
							}
						}
					}
				} else {
					for (int tempI = i - 1 - n; tempI >= 0; tempI--) {
						int temp1 = ((temp - (temp % 10))/10);
						int temp2 = (temp % 10);
						
						int addtemp = numbers[n].data[tempI + 1] + temp2;
						if (addtemp < 10) {
							numbers[n].data[tempI + 1] = addtemp;
						} else {
							for (int tempIa = tempI; tempIa >= 0; tempIa--) {
								int temp1a = ((addtemp - (addtemp % 10))/10);
								int temp2a = (addtemp % 10);
						
								numbers[n].data[tempIa + 1] = temp2a;
								addtemp = numbers[n].data[tempIa] + temp1a;
								if (addtemp < 10) {
									numbers[n].data[tempIa] = addtemp;
									break;
								}
							}
						}

						temp = numbers[n].data[tempI] + temp1;
						if (temp < 10) {
							numbers[n].data[tempI] = temp;
							break;
						}
					}
				}
			}
		}

		Init();
		for (int i = 0; i < 10; i++) {
			numbers[i].PrintNumber();
			Add(numbers[i]);
		}
	}

	void Add(BigInt number) {
		if (number.size == size) {
			for (int i = size - 1; i >= 0; i--) {
				int temp = number.data[i] + data[i];
				if (temp < 10) {
					data[i] = temp;
				} else {
					for (int tempI = i - 1; tempI >= 0; tempI--) {
						int temp1 = ((temp - (temp % 10))/10);
						int temp2 = (temp % 10);
						
						data[tempI + 1] = temp2;
						temp = data[tempI] + temp1;
						if (temp < 10) {
							data[tempI] = temp;
							break;
						}
					}
				}
			}
		}
	}

	void Subtract(BigInt number) {
		for (int i = size - 1; i >= 0; i--) {
			int temp = data[i];
			if (temp >= number.data[i]) {
				data[i] = temp - number.data[i];
			} else {
				for (int tempI = i - 1; tempI >= 0; tempI--) {
					if (data[tempI] > 0) {
						data[tempI] -= 1;
						for (tempI = tempI + 1; tempI < i; tempI++) {
							data[tempI] += 9;
						}
						data[i] += 10;
						break;
					}
				}
				data[i] -= number.data[i];
			}
		}
	}

	void Mod(BigInt number) {
		BigInt temp;
		Copy(*this, &temp);
		while (!temp.IsNegative()) {
			temp.Subtract(number);
			if (!temp.IsNegative()) {
				Copy(temp, this);
			}
		}
	}

	int Modulo(BigInt number) {
		BigInt div;
		int mod = 0;
		int num = number.ToInt();
		int length = 0;
		for (; length < size; length++) {
			if (number.data[length] != 0) {
				break;
			}
		}
		length = size - length;
		int index = 0;
		for (; index < size; index++) {
			if (data[index] != 0) {
				break;
			}
		}
		if (index < size) {
			bool first = true;
			if (index > (size - length)) {
				mod = data[index];
			}
			for (; index <= size - length; index++) {
				int tempNum = 0;
				for (int i = length - 1; i >= 0; i--) {
					if (first) {
						tempNum += data[index + (length - i - 1)] * (int)pow((double)10, i);
						first = false;
					} else if (i == length - 1) {
						tempNum += mod * (int)pow((double)10, i);
					} else {
						tempNum += data[index + (length - i - 1)] * (int)pow((double)10, i);
					}
				}
				int modNum = tempNum % num;
				int divNum = tempNum / num;

				mod = modNum;
			}
		}
		return mod;
	}

	static void CreateNumber(int number, BigInt * bigint) {
		string temp = "";
		stringstream ss;
		ss << number;
		temp = ss.str();

		if (temp.size() <= bigint->size) {
			int index = bigint->size - temp.size();
			for (int i = 0; index < bigint->size; i++, index++) {
				char num = temp.at(i);
				bigint->data[index] = atoi(&num);
			}
		}
	}

	void PrintNumber() {
		for (int i = 0; i < size; i++) {
			cout << data[i];
		}
		cout << endl;
	}

	bool IsNegative() {
		for (int i = 0; i < size; i++) {
			if (data[i] < 0) {
				return true;
			}
		}
		return false;
	}

	int ToInt() {
		int number = 0;
		for (int i = size - 1, n = 0; i >= 0; i--, n++) {
			number += data[i] * (int)pow((double)10, n);
		}
		return number;
	}

	static bool Compare(BigInt a, BigInt b) {
		for (int i = 0; i < size; i++) {
			if (a.data[i] != b.data[i]) {
				return false;
			}
		}
		return true;
	}
};

int main() {
	BigInt n(3);
	BigInt q(17);
	int count = 0;
	for (int i = 0; i < 1; i++) {
		BigInt xa(15);
		//xa.PrintNumber();
		BigInt xb(13);
		//xb.PrintNumber();

		BigInt ya;	
		BigInt::Copy(n, &ya);
		ya.Power(xa.ToInt());
		ya = BigInt(ya.Modulo(q));
		//ya.PrintNumber();
		//cout << endl;

		BigInt yb;
		BigInt::Copy(n, &yb);
		//yb.PrintNumber();
		yb.Power(xb.ToInt());
		//yb.PrintNumber();
		//yb.Mod(q);
		yb = BigInt(yb.Modulo(q));
		//yb.PrintNumber();
		//cout << endl;

		BigInt ka;
		BigInt::Copy(yb, &ka);
		ka.Power(xa.ToInt());
		//ka.Mod(q);
		ka = BigInt(ka.Modulo(q));
		ka.PrintNumber();
		cout << endl;

		BigInt kb;
		BigInt::Copy(ya, &kb);
		kb.Power(xb.ToInt());
		//kb.Mod(q);
		kb = BigInt(kb.Modulo(q));
		kb.PrintNumber();
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;

		if (BigInt::Compare(ka, kb)) {
			count++;
		} else {
			/*xa.PrintNumber();
			cout << endl;
			xb.PrintNumber();
			cout << endl << endl << endl;
			ya.PrintNumber();
			cout << endl;
			yb.PrintNumber();
			cout << endl << endl << endl;
			ka.PrintNumber();
			cout << endl;
			kb.PrintNumber();
			cout << endl;
			break;*/
		}
	}

	//cout << count << endl << endl;
	/*for (int i = 0; i <= 0; i++) {
		BigInt test1(10);
		BigInt test2(0);

		test1.Power(test2.ToInt());
		test1.PrintNumber();
		//test1 = BigInt(test1.Modulo(q));
		//test1.PrintNumber();
		//if (test1.ToInt() == i) {
			//count++;
		//}
	}*/
	//cout << count << endl;
	_getch();
	return 0;
}