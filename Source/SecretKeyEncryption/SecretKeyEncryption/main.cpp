#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <sstream>

using namespace std;

/* BigInt class, used to store large integers that would otherwise not fit into
 * a standard integer data type.
 * Provides some mathematical functions such as addition, subtraction,
 * multiplication, and modulo.
 * 
 * data array, size is 256 ints
 * each index in the data array represents a number from 0-9
 * ie, 256 would look like [0][0][0]...[0][0][2][5][6]
 */
class BigInt {
public:
	int data[256]; //container for representing large numbers
	static const int size = 256; //size of the data array

	/*Default Constructor, initializes the data array to all 0s*/
	BigInt() {
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
	}

	/*Constructor that sets the data array to equal a number
	 *IE, BigInt(5) - 0000...005
	 */
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

	/*Reinitializes the data array to all 0s*/
	void Init() {
		for (int i = 0; i < size; i++) {
			data[i] = 0;
		}
	}

	/*Copies the data contents of the source BigInt into the destination BigInt (pointer)*/
	static void Copy(BigInt source, BigInt * destination) {
		for (int i = 0; i < size; i++) {
			destination->data[i] = source.data[i];
		}
	}

	/*Sets the current BigInt to the desired number*/
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

	/*Sets the BigInt that it is called on to the number specified*/
	void SetNumber(int number[]) {
		Init();
		for (int i = 0; i < size; i++) {

		}
	}

	/*Takes the current BigInt's data value and raises it to the power of the desired exponent*/
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

	/*Takes the current BigInt's data value and multiplies it by the desired
	  BigInt in the number field, this value is stored in the current BigInt*/
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

	/*FOR TESTING PURPOSES, DEPRECATED*/
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

	/*Takes the current BigInt and adds the number BigInt to it,
	  this data is automatically stored in the current BigInt*/
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

	/*Takes the current BigInt and subtracts the number BigInt from it,
	  this data is automatically stored in the current BigInt*/
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

	/*Used for creating a new BigInt number, the integer number is converted and
	  stored in the bigint pointer*/
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

	/*Prints out the value of the number*/
	void PrintNumber() {
		for (int i = 0; i < size; i++) {
			cout << data[i];
		}
		cout << endl;
	}

	/*Because BigInts in this class can only ever be positive,
	  this checks if the currrent BigInt has been corrupted with negative values*/
	bool IsNegative() {
		for (int i = 0; i < size; i++) {
			if (data[i] < 0) {
				return true;
			}
		}
		return false;
	}

	/*Converts the current BigInt into a standard integer value,
	  this integer value is returned by this function*/
	int ToInt() {
		int number = 0;
		for (int i = size - 1, n = 0; i >= 0; i--, n++) {
			number += data[i] * (int)pow((double)10, n);
		}
		return number;
	}

	/*Checks if two BigInts are equal to each other, used for testing purposes.*/
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
	string data = "HELLO WORLD THIS IS THE DATA";
	
	BigInt n(3);
	BigInt q(17);
	for (int z = 0; z < 50; z++) {
		string encrypted = "";
	string decrypted = "";
	BigInt xa(rand() % 200);
	BigInt xb(rand() % 200);

	BigInt ya;	
	BigInt::Copy(n, &ya);
	ya.Power(xa.ToInt());
	ya = BigInt(ya.Modulo(q));

	BigInt yb;
	BigInt::Copy(n, &yb);
	yb.Power(xb.ToInt());
	yb = BigInt(yb.Modulo(q));

	BigInt ka;
	BigInt::Copy(yb, &ka);
	ka.Power(xa.ToInt());
	ka = BigInt(ka.Modulo(q));
	//ka.PrintNumber();
	cout << ka.ToInt() << endl;

	BigInt kb;
	BigInt::Copy(ya, &kb);
	kb.Power(xb.ToInt());
	kb = BigInt(kb.Modulo(q));
	//kb.PrintNumber();
	cout << kb.ToInt() << endl;

	for (int i = 0; i < data.size(); i++) {
		char c = data.at(i);
		c=c^ka.ToInt();
		c += ka.ToInt() * 2;
		encrypted += c;
	}
	cout << encrypted << endl;

	for (int i = 0; i < encrypted.size(); i++) {
		char c = encrypted.at(i);
		c -= kb.ToInt() * 2;
		c = c^kb.ToInt();
		decrypted += c;
	}
	cout << decrypted << endl << endl << endl;
	}

	_getch();
	return 0;
}