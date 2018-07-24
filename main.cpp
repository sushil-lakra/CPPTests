

#include <fstream>
#include <iostream>

#include <iostream>
#include <thread>
#include <winsock.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

#include <iomanip>
#include <algorithm>
#include <atomic>

void ClientCommThread(SOCKET clientSocket)
{
	while (1)
	{

	}
}

int AcceptClients()
{
	WSADATA wsadata;
	SOCKET _socket;

	int error = WSAStartup(0x0202, &wsadata);

	if (error)
	{
		return false;
	}

	if (wsadata.wVersion != 0x0202) //Wrong Winsock version?
	{
		WSACleanup();
		return false;
	}

	SOCKADDR_IN addr; // The address structure for a TCP socket

	addr.sin_family = AF_INET;      // Address family
	addr.sin_port = htons(15000);   // Assign port to this socket

	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_socket == INVALID_SOCKET)
	{
		return false; //Don't continue if we couldn't create a //socket!!
	}

	if (bind(_socket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		//We couldn't bind (this will happen if you try to bind to the same  
		//socket more than once)
		return false;
	}

	//Now we can start listening (allowing as many connections as possible to  
	//be made at the same time using SOMAXCONN). You could specify any 
	//integer value equal to or lesser than SOMAXCONN instead for custom 
	//purposes). The function will not //return until a connection request is 
	//made
	error = listen(_socket, SOMAXCONN);

	if (error == SOCKET_ERROR)
	{
		wprintf(L"listen failed with error: %ld\n", WSAGetLastError());
		closesocket(_socket);
		WSACleanup();
		return 1;
	}

	while (1)
	{	
		SOCKET clientSocket;

		clientSocket = accept(_socket, NULL, NULL);

		if (clientSocket == INVALID_SOCKET)
		{
			wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
			closesocket(_socket);
			WSACleanup();
			return 1;
		}
		else
			wprintf(L"Client connected.\n");

		std::thread thr(ClientCommThread, clientSocket);
	}
}

void AcceptClientsThread()
{
	AcceptClients();
}


void InitServer()
{

}
void InitClient()
{

}

void ServerThread()
{

}

void ClientThread()
{

}

/*
template <typename T>
void InitPointers(char* head, T*& t)
{
	t = (T*)head;
}

void InitPointers(char* head, char*& t, int len)
{
	t = head;
}

template <typename ... Param>
void InitPointers(char* head, char*& t, const int32_t len, Param& ... params)
{
	t = head;
	InitPointers(head + len, params...);
}

template <typename T, typename ... Param>
void InitPointers(char* head, T*& t, Param& ... params)
{
	t = (T*)head;
	InitPointers(head + sizeof(T), params...);
}

void TestingVariadicInitializationOfPointers()
{
	char buffer[1000];
	std::cout << (int)&buffer << std::endl;

	int* p1;
	int* p2;
	char* p3;
	int len = 100;
	bool* p4;
	int64_t* p5;
	char* p6;
	int p6len = 1;
	int* p7;

	InitPointers(buffer, p1, p2, p3, len, p4, p5, p6, p6len, p7);
	std::cout << "p1 : " << (int)p1 << std::endl;
	std::cout << "p2 : " << (int)p2 << std::endl;
	std::cout << "p3 : " << (int)p3 << std::endl;
	std::cout << "p4 : " << (int)p4 << std::endl;
	std::cout << "p5 : " << (int)p5 << std::endl;
	std::cout << "p6 : " << (int)p6 << std::endl;
	std::cout << "p7 : " << (int)p7 << std::endl;
}
*/

template <typename T, typename ... Param>
void Any(char* buf, int64_t& sz, T*& v, Param... params);

template <typename T>
void Any(char* buf, int64_t& sz, T*& v);

template <typename ... Param>
void Any(char* buf, int64_t& sz, char*& v, int len, Param... params);

void Any(char* buf, int64_t& sz, char*& v, int len)
{
	std::cout << "char*" << std::endl;
}

template <typename ... Param>
void Any(char* buf, int64_t& sz, char*& v, int len, Param... params)
{
	std::cout << "char* variadic" << std::endl;
	Any(buf, sz, params...);
}

/*
void Any(char* buf, int64_t& sz, char*& v, int len)
{
	std::cout << "char*" << std::endl;
}

template <typename ... Param>
void Any(char* buf, int64_t& sz, char*& v, int len, Param... params)
{
	std::cout << "char* variadic" << std::endl;
	Any(buf, sz, params...);
}
*/
template <typename T>
void Any(char* buf, int64_t& sz, T*& v)
{
	std::cout << "Single T*" << std::endl;
}

template <typename T, typename ... Param>
void Any(char* buf, int64_t& sz, T*& v, Param... params)
{
	std::cout << "T* variadic" << std::endl;
	Any(buf, sz, params...);
}

void TestingTemplate()
{
	char buffer[1000];

	
	int i = 10;

	//func(buffer, i);

	int*j = &i;
	*j = 100;

	//func(buffer, j);

	int *k = nullptr;

	//func(buffer, j, k);

	//func(buffer, j, k, 10);

	char* ptr = nullptr;
	int len = 10;
	//initPointers(buffer, ptr, i, 10);
	int64_t sz = 100;

	int32_t* p1 = nullptr;
	int64_t* p2 = nullptr;
	
	char* p3 = nullptr;;
	int len3 = 100;
	long long* p4 = nullptr;;
	uint32_t* p5 = nullptr;;

	//Any(buffer, sz, ptr, 10, &i, (long long)10);
	Any(buffer, sz, ptr, len, p1, p2, p3, len3, p4, p5);
	
	/*
	int32_t* p1;
	int64_t* p2;
	char* p3;
	int len = 100;
	long long* p4;
	uint32_t* p5;

	int sz = 0;
	Any(buffer, sz, p1, p2, p3, len, p4, p5);
	*/
}

template <typename T>
void PrintPointer(T* ptr)
{
	std::cout << "ptr : " << ptr << std::endl;
}

template <typename T, typename ...Params>
void PrintPointer(T* ptr, Params* ... params)
{
	std::cout << "ptr : " << ptr << std::endl;
	PrintPointer(params...);
}

void TestingMacroCreationOfCommaSeparatedArrayPointers()
{
#define PARAMS_1(var, ind) var[ind]
#define PARAMS_2(var, ind) var[ind], PARAMS_1(var, ind + 1)
#define PARAMS_3(var, ind) var[ind], PARAMS_2(var, ind + 1)
#define PARAMS_4(var, ind) var[ind], PARAMS_3(var, ind + 1)
#define PARAMS_5(var, ind) var[ind], PARAMS_4(var, ind + 1)
#define PARAMS_6(var, ind) var[ind], PARAMS_5(var, ind + 1)
#define PARAMS_7(var, ind) var[ind], PARAMS_6(var, ind + 1)
#define PARAMS_8(var, ind) var[ind], PARAMS_7(var, ind + 1)
#define PARAMS_9(var, ind) var[ind], PARAMS_8(var, ind + 1)
#define PARAMS_10(var, ind) var[ind], PARAMS_9(var, ind + 1)
#define PARAMS_11(var, ind) var[ind], PARAMS_10(var, ind + 1)
#define PARAMS_12(var, ind) var[ind], PARAMS_11(var, ind + 1)
#define PARAMS_13(var, ind) var[ind], PARAMS_12(var, ind + 1)
#define PARAMS_14(var, ind) var[ind], PARAMS_13(var, ind + 1)
#define PARAMS_15(var, ind) var[ind], PARAMS_14(var, ind + 1)
#define PARAMS_16(var, ind) var[ind], PARAMS_15(var, ind + 1)


	int* arr[15];
	/*
	for (int i = 0; i < 15; ++i)
		arr[i] = (int*)i;
		*/
	PrintPointer(PARAMS_15(arr, 0));
}

void TransformBase64Str(std::string& ref)
{
	for (int i = 0; i < ref.length(); ++i)
	{
		//std::cout << i << " : " << ref[i];
		char temp = ref[i];
		if (temp >= 'A' && temp <= 'Z')
		{
			ref[i] = temp - 'A';
		}

		if (temp >= 'a' && temp <= 'z')
		{
			ref[i] = temp - 'a' + 26;
		}
		if (temp >= '0' && temp <= '9')
		{
			ref[i] = temp - '0' + 52;
		}

		if (temp == '+')
		{
			ref[i] = 62;
		}

		if (temp == '/')
		{
			ref[i] = 63;
		}

		if (temp == '=')
		{
			ref[i] = 0;
			break;
		}
		//std::cout << " : " << ref[i] << std::endl;
	}
}

void Base64ToHex(std::string inp, unsigned char*& out, int& outLen)
{
	const int FIRST_2 = 48;
	const int LAST_4 = 15;
	const int FIRST_4 = 60;
	const int LAST_2 = 3;

	out = new unsigned char[2048]{ 0 };
	outLen = 0;

	TransformBase64Str(inp);

	int outInd = 0;
	int i = 0;
	for (; i < inp.length() - 4; ++i)
	{
		out[outInd] = inp[i++];
		out[outInd] <<= 2;
		out[outInd] |= ((inp[i] & FIRST_2) >> 4);

		++outInd;

		out[outInd] = inp[i++] & LAST_4;
		out[outInd] <<= 4;
		out[outInd] |= ((inp[i] & FIRST_4) >> 2);

		++outInd;

		out[outInd] = inp[i++] & LAST_2;
		out[outInd] <<= 6;
		out[outInd] |= inp[i];

		++outInd;
	}

	out[outInd] = inp[i++];
	out[outInd] <<= 2;
	out[outInd] |= ((inp[i] & FIRST_2) >> 4);

	++outInd;

	if (i < inp.length())
	{
		out[outInd] = inp[i++] & LAST_4;
		out[outInd] <<= 4;
		out[outInd] |= ((inp[i] & FIRST_4) >> 4);

		++outInd;

		if (i < inp.length())
		{
			out[outInd] = inp[i++] & LAST_2;
			out[outInd] <<= 6;
			out[outInd] |= inp[i];

			++outInd;
		}
	}

	outLen = outInd;
}

const unsigned char* SkipHdr(const unsigned char* head)
{
	const unsigned char* ptr = head;

	if (*ptr != 0x30)
		return nullptr;

	++ptr;

	while (*ptr++ != 0x30);

	int oidLen = *ptr;
	ptr += oidLen;
	
	if (*ptr++ != 0)
		return nullptr;

	if (*ptr != 0x3)
		return nullptr;

	//find 02
	while (*ptr++ != 0x2);

	return --ptr;
}

void ParseModExp(const unsigned char* inp,
	int inpLen,
	unsigned char*&  modulus, 
	int& modulsLen,
	int& exp)
{
	const unsigned char* ptr = inp;

	ptr = SkipHdr(ptr);

	if (*ptr != 0x2)
		return;

	ptr++;
	int modLen = 0;
	switch (*ptr)
	{
	case 129:
	{
		++ptr;
		modLen = *ptr;
		break;
	}
		//return 2;

	case 130:
	{
		++ptr;
		modLen = (int)*ptr;
		modLen <<= 8;
		++ptr;
		modLen |= (int)*ptr;
		break;
	}
		//return 3;

	case 131:
	{
		//Later
		return;
		break;
	}
		//return 4;

	case 132:
	{
		return;
		break;
	}
		//return 5;

	case 128:
	default:
	{
		return;
		break;
	}
		//return 1;
	}


	++ptr; //skip last length byte
	++ptr; //skip 00

	//std::cout << "ModLen : " << modLen << std::endl;

	modulus = new unsigned char[modLen];
	unsigned char* mod = modulus;
	modulsLen = modLen - 1;

	while (modLen--)
	{
		*mod++ = *ptr++;
	}

	if (*ptr != 0x3)
		return;

	++ptr; //skip 03

	int expLen = inpLen - (ptr - inp) - 1;
	exp = *ptr;
	
	while (expLen--)
	{
		exp <<= 8;
		++ptr;
		exp |= *ptr;
	}

	std::cout << "exp : " << exp << std::endl;
	return;
}

void testBase64ToHex()
{
	std::string pubKey_ =
		"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEApYItxYQSnbyHc2yLIKDs"
		"TFLyXlmWjYhnW6IP/ADOm6I8Wc7VkRWPayd6qJwuJbhbotmc8PJAaCsBKep5Swn5"
		"7J9jLYFF5/AZcRzbVgN5r3ei47NZf55jK8B+Qq3VM/mAThmfmt//hh/oEvkBgDWr"
		"fwc382x+tzKo1KlZcId9KiJTbKsNJ6V2QhVAHsoNCfl6PYnqOR+q9jt3+ebIb+om"
		"mk8zv5AkurGp6tA15ML7wMTFqb9lAZGNQaIuTVB037tPNnhl8+I1PJP0JvGvSxTF"
		"cNUVl2F5BIaUaybKNr/HFTZ8lOIJuwc/T8pAFDluqoG55lvxduzoCpzVEFL3RyHC"
		"qwIDAQAB";

	unsigned char* out = nullptr;
	int len = 0;
	Base64ToHex(pubKey_, out, len);

	if (len > 0)
	{
		for (int i = 0, x = 0; i < len; ++x, ++i)
		{
			if (x == 15)
			{
				std::cout << "\n";
				x = 0;
			}

			//std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)out[i] << " ";
		}
	}

	unsigned char* mod = nullptr;
	int modLen = 0;
	int exp = 0;
	ParseModExp(out, len, mod, modLen, exp);

	for (int i = 0; i < modLen; ++i)
	{
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)mod[i] << " ";
	}
}

#include <vector>

void TestVector()
{
	std::vector<int> vec;
	vec[0] = 1;

	vec.reserve(100);
	std::cout << vec[0] << std::endl;
}

#include <chrono>

void TestChrono()
{
	std::chrono::milliseconds milis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch());
	std::cout << "milis : " << milis.count() << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::chrono::milliseconds milis1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch());

	std::cout << "slept for : " << (milis1 - milis).count() << std::endl;
	std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration dtn = tp.time_since_epoch();

	std::cout << "dtn : " << dtn.count() * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den << std::endl;
}

void switchTest()
{
	int var = 2;
	switch (var)
	{
	if (var == 2)
		std::cout << "Hello 2" << std::endl;
	else
		std::cout << "Hello!" << std::endl;
	case 0:
	{
		break;
	}
	if (var == 2)
		std::cout << "Hello 0" << std::endl;
	else
		std::cout << "Hello 0!" << std::endl;
	case 1:
	{
		break;
	}
	case 2:
	{
		std::cout << "Hello 0!" << std::endl;
		break;
	}
	}
}
template <typename T, int SZ = 100>
class Sample
{
	int var;

public:

	Sample()
	{
		var = 1000;
	}

	class VarReader
	{
		Sample<T, SZ>& sample;
	public:
		VarReader(Sample<T, SZ>& s) :
			sample{ s }
		{}

		void Print()
		{
			std::cout << sample.var << std::endl;
		}
	};
};


class Excution6hr
{
	//thread sleeps for this much time before executing the queued requests
	
public:

	long long sleep_seconds_;
	std::thread thr_;

	void Execute()
	{
		sleep_seconds_ = 1;
		while (1)
		{
			std::cout << "Here : " << sleep_seconds_ << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(sleep_seconds_));
		}
	}

	Excution6hr() :
		thr_{ [=] {Execute(); } }
	{
		//1849820
		long long  seconds = std::chrono::duration_cast<std::chrono::seconds>
			(std::chrono::steady_clock::now().time_since_epoch()).count();

		//1849820 / 60 = 30830
		long long mins = seconds / 60;
		//1849820 - (30830 * 60)
		long long remaining_seconds = seconds - (mins * 60);

		//30830 / 60 = 513
		long long hours = mins / 60;
		//30830 - (513 * 60) = 50
		long long remaining_mins = mins - (hours * 60);

		//513 % 6 = 
		long long remaining_of_6_hour = hours % 6;

		sleep_seconds_ = ((remaining_of_6_hour * 60) * 60)
			+ (remaining_mins * 60)
			+ remaining_seconds;
	}
};


void Execute()
{
	long long sleep_seconds_ = 10000;
	while (1)
	{
		//std::cout << "Here : " << sleep_seconds_ << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(sleep_seconds_));
	}
}

void TemplateTest()
{
	Sample<int, 133> sample;
	Sample<int, 133>::VarReader reader(sample);

	reader.Print();
}

void MaskTest()
{
	uint64_t val = 0xFFFFFFFF;
	std::cout << (val << 32) << std::endl;
}

void main()
{
	/*
	char arr[100];

	memcpy(arr,  "o9\0\n9ds9.i", 10);

	ofstream ofs("tmp.txt");

	ofs.seekp(0, ios::beg);
	ofs.write(arr, 10);

	memcpy(arr, "1o9\0\n9ds9.i", 11);

	ofs.write(arr, 11);

	ofs.close();

	ifstream ifs("tmp.txt");

	char buffer[100];

	ifs.seekg(0, ios::beg);
	ifs.read(buffer, 20);

	for (int i = 0; i < 20; ++i)
		cout << buffer[i] << endl;
	*/

	/*for (int i = 0; std::cout << "comp" << std::endl, i < 5; std::cout << "inc" << std::endl, ++i)
		std::cout << "opr" << std::endl;
	*/

	//TestingMacroCreationOfCommaSeparatedArrayPointers();
	//testBase64ToHex();

	/*
	Excution6hr var;
	var.thr_.join();
	*/

	/*std::vector<std::thread*> thread;

	int i = 0;
	for (;;)
	{
		thread.push_back(new std::thread(Execute));
		std::cout << "i " << ++i << std::endl;
	}
	std::cout << "sizeof (long long) : " << sizeof(uint64_t) << std::endl;
	

	int data[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int* arr[10]{data, data+1, data+2, data+3, data+4, data+5, data+6, data+7, data+8, data+9};

	int** ptr = arr;

	std::random_shuffle(arr, arr + 10);

	for (int i = 0; i < 10; ++i)
	{
		std::cout << *ptr[i] << std::endl;
	}*/

	//MaskTest();

	//std::cout << (1 << 10) << std::endl                                                                                                                                                                                                                                                                                                                                                                                   ;

	TestingTemplate();

	int x;
	std::cin >> x;
}

