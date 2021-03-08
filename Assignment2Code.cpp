#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
//function prototype
int printmenu();
void encodeMessageStream(string);
void generateHammingCode(bool arr[], int SIZE);
void decodeMessageStream(string);
int checkMessageParity(bool arr1[], int SIZE);
int main()
{
	int userselection = 0;
	string FileToEncode;
	string FileToDecode;
	userselection = printmenu();
	if (userselection == 1)
	{
		cout << "Enter File Name for the messages to be encoded" << endl;
		cin >> FileToEncode;
		encodeMessageStream(FileToEncode);
	}
	else if (userselection == 2)
	{
		cout << "Enter File Name for the messages to be decoded" << endl;
		cin >> FileToDecode;
		decodeMessageStream(FileToDecode);
	}
	else
		exit(0);
	system("pause");
	return (0);
}
int printmenu()
{
	int USERSELECTION = 0;

	cout << "Select from the following menu: " << endl;
	cout << "1) Encode a message " << endl;
	cout << "2) Decode a message " << endl;
	cout << "3) Exit " << endl;
	do
	{
		cout << "Please make a selection: ";
		cin >> USERSELECTION;
		if (USERSELECTION < 1 || USERSELECTION > 3)
			cout << "Invalid Selection " << endl;
	} while ((USERSELECTION < 1 || USERSELECTION > 3));
	return USERSELECTION;
}
void encodeMessageStream(string EncodeFile)
{
# define size 7
	bool message[size];
	char ch;
	ifstream file1;
	file1.open(EncodeFile, ios::in);
	if (file1.fail())
	{
		cerr << "File failed to open" << endl;
		exit(1);
	}
	ofstream file2;
	file2.open("encodedMessages.txt", ios::out);
	if (file2.fail())
	{
		cerr << "Error creating the file " << endl;
		exit(0);
	}

	while (!file1.eof())
	{
		for (int i = 0; i < 4; i++)
		{

			file1.get(ch);
			message[i] = ch - 48;
		}
		generateHammingCode(message, size);
		for (int i = 0; i < size; i++)
			file2 << message[i];
		cout << "Encoded Message: " << message[0] << message[1] << message[2] <<

			message[3] << message[4] << message[5] << message[6] << endl;

		file1.get(ch);
	}
	file2.close();
	file1.close();
	cout << "Messages are successfully encoded, check encoded messages file " << endl;
}
void generateHammingCode(bool arr[], int SIZE)
{
	bool p1, p2, p4;
	p1 = arr[0] ^ arr[2] ^ arr[3];
	p2 = arr[0] ^ arr[1] ^ arr[3];
	p4 = arr[0] ^ arr[1] ^ arr[2];
	arr[4] = arr[3];
	arr[3] = p4;
	arr[5] = p2;
	arr[6] = p1;
}
void decodeMessageStream(string DecodeFile)
{
#define size 7
	bool encodedmessage[size], x[size];
	char ch;
	char lastChar('z');
	int errorposition = 0;
	ifstream file1;
	file1.open(DecodeFile, ios::in);
	if (file1.fail())
	{
		cerr << "File failed to open" << endl;
		exit(1);
	}

	ofstream file2;
	file2.open("decodedMessages.txt", ios::out);
	if (file2.fail())
	{
		cerr << "Error creating the file " << endl;
		exit(0);
	}
	cout << "Encoded" << " | " << "Corrected" << " | " << "Decoded" << " | " << "Status" << endl;
	while (!file1.eof())
	{
		for (int i = 0; i < size; i++)
		{
			file1.get(ch);

			x[i] = ch - 48;
			encodedmessage[i] = ch - 48;
		}
		if (ch != lastChar) {
			errorposition = checkMessageParity(encodedmessage, size);
			if (errorposition == -1)
			{
				file2 << x[0] << x[1] << x[2] << x[3] << x[4] << x[5] << x[6] << "|" <<
					encodedmessage[0] << encodedmessage[1] << encodedmessage[2] << encodedmessage[3]
					<< encodedmessage[4] << encodedmessage[5] << encodedmessage[6] << "|" <<
					encodedmessage[0] << encodedmessage[1] << encodedmessage[2] << encodedmessage[4]
					<< "|" << "NO_ERROR" << endl;

				cout << x[0] << x[1] << x[2] << x[3] << x[4] << x[5] << x[6] << "|" <<
					encodedmessage[0] << encodedmessage[1] << encodedmessage[2] << encodedmessage[3]
					<< encodedmessage[4] << encodedmessage[5] << encodedmessage[6] << "|" <<
					encodedmessage[0] << encodedmessage[1] << encodedmessage[2] << encodedmessage[4]
					<< "|" << "NO_ERROR" << endl;

			}
			else
			{
				file2 << x[0] << x[1] << x[2] << x[3] << x[4] << x[5] << x[6] << "|" <<
					encodedmessage[0] << encodedmessage[1] << encodedmessage[2] << encodedmessage[3]
					<< encodedmessage[4] << encodedmessage[5] << encodedmessage[6] << "|" <<
					encodedmessage[0] << encodedmessage[1] << encodedmessage[2] << encodedmessage[4]
					<< "|" << "ERROR_" << errorposition << endl;

				cout << x[0] << x[1] << x[2] << x[3] << x[4] << x[5] << x[6] << "|" <<
					encodedmessage[0] << encodedmessage[1] << encodedmessage[2] << encodedmessage[3]
					<< encodedmessage[4] << encodedmessage[5] << encodedmessage[6] << "|" <<

					encodedmessage[0] << encodedmessage[1] << encodedmessage[2] << encodedmessage[4]
					<< "|" << "ERROR_" << errorposition << endl;

			}
			file1.get(ch);
			if (ch == '\n') {
				lastChar = ch;
			}
		}
	}
	cout << "Messages are successfully decoded, check decoded messages file " << endl;
	file2.close();
	file1.close();
}
int checkMessageParity(bool arr1[], int SIZE)
{
	int errorbit = 0, x = 0;
	bool p1, p2, p4;
	p1 = arr1[0] ^ arr1[2] ^ arr1[4] ^ arr1[6];
	p2 = arr1[0] ^ arr1[1] ^ arr1[4] ^ arr1[5];
	p4 = arr1[0] ^ arr1[1] ^ arr1[2] ^ arr1[3];
	errorbit = (1 * p1) + (2 * p2) + (4 * p4);
	if (errorbit != 0) {
		if (arr1[7 - errorbit] == 0)
			arr1[7 - errorbit] = 1;
		else
			arr1[7 - errorbit] = 0;

	}
	if (errorbit == 0)
		errorbit = -1;
	return errorbit;
}
