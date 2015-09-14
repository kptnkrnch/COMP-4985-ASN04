#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

int main() {
	string message = "MESSAGE: Hello Deimied, I see you are minoring in CPSC; how do you like it?";
	string response = "";
	cout << message << endl;
	cin >> response;

	if (response.length() > 0) {
		cout << endl << "RESPONSE: " << response << endl << endl;
	}

	cout << "PS: This has got to be one of the geekiest/nerdiest greetings ever." << endl;
	cout << "The only way I could make this more geeky/nerdy is if I set " 
		<< endl << "it up with a socket and had it transmit this message via the internet"
		<< endl << "(not really feasible because I would need to "
		<< endl << "know what operating system you are using)"
	    << endl << "or if I had it send the response to some database I suppose throwing "
		<< endl << "in a Star Trek reference or something like that would work too, "
		<< endl << "but honestly, I don't follow that series enough to even be able "
		<< endl << "to quote them adequately (hell hath no fury like a Trekky scorned)."
		<< endl << endl << "Ramble Ramble Ramble...";

	_getch();
	return 0;
}

