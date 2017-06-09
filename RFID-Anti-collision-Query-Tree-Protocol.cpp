#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<stack>
#include<fstream>

using namespace std;


int IDENTIFICATION = 0; //1개의 노드가 응답한 횟수

//스택
class Reader { // 질의 주머니

	int cycle; // 2개이상 노드가 응답한 횟수
	int IDLE; // 0개의 노드가 응답한 횟수
	int COLLISION;

	string temp; // 스택에서 꺼낸 수를 저장
	stack<string> g;

public:
	Reader();//기본생성자
	Reader(int); // 변환생성자
	Reader(Reader& R);//복사생성자

	void result();
	void creatQuery(int);  //태그들에게 보낼 질의 메세지를 만드는 함수
	string sendQuery();   //태그들에게 질의 메세지를 보내는 함수
	void responsQuery(int); //태그들로 부터 오는 응답메세지를 처리하는 함수
};
Reader::Reader() // 기본생성자
{
	cycle = 0;
	IDLE = 0;
	COLLISION = 0;
}

Reader::Reader(int n)//변환 생성자
{
	cout << "변환생성자" << endl;
}
Reader::Reader(Reader &R)//복사생성자
{
	cout << "복사생성자" << endl;
}

void Reader::creatQuery(int tagNum)//태그들에게 보낼 질의 메세지를 만드는 함수
{


	if (tagNum > 1)
	{
		g.push(temp + "1");
		g.push(temp + "0");
		temp = g.top();
		g.pop();
	}
	if (tagNum == 1 || tagNum == 0)
	{
		temp = g.top();
		g.pop();
	}

}

string Reader::sendQuery()//태그들에게 질의 메세지를 보내는 함수
{
	cout << "\n";
	cycle++;
	cout << "==== " << cycle << " cycle" << " ====" << endl;
	return temp;
}
void Reader::responsQuery(int tagNum)//태그들로 부터 오는 응답메세지를 처리하는 함수
{
	if (tagNum == 1)
	{
		IDENTIFICATION++;
	}
	else if (tagNum == 0)
	{
		IDLE++;
	}
	else
	{
		COLLISION++;
	}
}
void Reader::result()
{
	cout << "\n";
	cout << "Total " << cycle << " Cycle<s>" << endl;
	cout << IDLE << " IDLE Cycle<s>" << endl;
	cout << COLLISION << " COLLISON Cycles<s>" << endl;
	cout << IDENTIFICATION << " IDENTIFICATION Cycles<s>" << endl;
}











class Tag  // 태그 아이디를 담고 있는 변수
{
	string ID[10];
	int num; // 태그의 갯수
	int count;

public:
	Tag(); // 기본생성자
	Tag(int); // 변환생성자
	Tag(Tag& T); // 복사생성자

	void receiveQuery(string); //질의를 수신하고 처리하는 함수
	int sendReader(); //리더에게 메세지를 보내는 함수
	void tagprint(); // 태그의 정보(태그 이름과 아이디)를 출력하는 함수
	void creat_bin(int); // 태그의 아이디를 만드는 함수
};
Tag::Tag() // 기본 생성자
{
	char c;
	int i = 0;
	int n = 1;
	string buffer[6];

	ifstream is;

	is.open("qt.dat"); // 파일을 읽는다.
	cout << "\n";
	if (!is.fail()){
		cerr << "qt.dat 로부터 성공적으로 태그를 읽었습니다!" << endl;
	}

	is.get(c);
	while (!is.eof()) // 읽고 분리해서 배열에 넣는다.
	{
		if (c != 44)
		{
			buffer[i] += c;
			n++;
		}
		else
		{
			i++;
		}

		is.get(c);
	}

	num = (int)buffer[0].at(0)-'0'; // 첫번재 5를 개수에 넣는다.
	for (int i = 1; i < 6; i++) // 나머지는 태그에 넣는다
	{
		ID[i-1] = buffer[i];
		cout << "Tag"<<i-1<<": " <<ID[i - 1] << endl;
	}
	count = -1;

	is.close();

}
Tag::Tag(int n) // 변환 생성자
{
	num = n;
	creat_bin(n);
	count = -1;
}
Tag::Tag(Tag& T) // 복사생성자
{
	cout << "복사생성자" << endl;
}

void Tag::receiveQuery(string querybag) // 질의를 수신하고 처리하는 함수
{
	int i = 0;

	if (querybag.empty())
	{
		cout << "Query: e" << endl;
		for (int i = 0; i < num; i++)
		{
			cout << "Response: " << ID[i] << " <TAG" << i << ">" << endl;
		}
		count = 4;
	}
	else
	{
		cout << "Query : " << querybag << endl;
		count = 0;
		for (int i = 0; i < num; i++)
		{
			if (querybag.length() == 4)
			{
				if (querybag.at(0) == ID[i].at(0) && querybag.at(1) == ID[i].at(1) && querybag.at(2) == ID[i].at(2) && querybag.at(3) == ID[i].at(3))//네번째 수
				{
					cout << "Response: " << ID[i] << " <TAG" << i << ">" << endl;
					count++;
				}

			}
			else if (querybag.length() == 3)
			{
				if (querybag.at(0) == ID[i].at(0) && querybag.at(1) == ID[i].at(1) && querybag.at(2) == ID[i].at(2))//세번째 수
				{
					cout << "Response: " << ID[i] << " <TAG" << i << ">" << endl;
					count++;
				}
			}
			else if (querybag.length() == 2)
			{
				if (querybag.at(0) == ID[i].at(0) && querybag.at(1) == ID[i].at(1))//두번째 수
				{
					cout << "Response: " << ID[i] << " <TAG" << i << ">" << endl;
					count++;
				}
			}
			else if (querybag.length() == 1)
			{
				if (querybag.at(0) == ID[i].at(0))// 첫번째 수
				{
					cout << "Response: " << ID[i] << " <TAG" << i << ">" << endl;
					count++;
				}
			}
			else
			{
				cout << "오류!!" << endl;
			}
		}
	}
}
int Tag::sendReader() // 리더에게 메시지를 보내는 함수
{
	return count;
}
void Tag::tagprint()  // 태그의 정보를 출력하는 함수
{
	for (int i = 0; i < num; i++)
	{
		cout << "Tag" << i << ": " << ID[i] << endl;
	}
}

void Tag::creat_bin(int n) // 십진수를 랜덤으로 뽑아서 2진수로 만든  
{
	int temp1[10]; //정수를 램덤으로 뽑아 저장하는 배열
	char temp2[5];

	for (int i = 0; i < n; i++)// 십진수를 0부터 15까지 태그의 개수만큼 랜덤으로 뽑는다.
	{
		temp1[i] = rand() % 15; //0~15까지 랜덤으로 뽑는다.

		for (int j = 0; j < i; j++)//중복검사
		{
			if (temp1[i] == temp1[j])
			{
				i--;
			}
		}
		_itoa_s(temp1[i], temp2, 2);

		ID[i] = temp2;

		//문자열에 4자리를 맞추기위해서 앞에 0을 넣는다.
		if (ID[i].length() == 1)
		{
			ID[i].insert(0, "000");
		}
		if (ID[i].length() == 2)
		{
			ID[i].insert(0, "00");
		}
		if (ID[i].length() == 3)
		{
			ID[i].insert(0, "0");
		}
	}
}







class Simulator {
	int num;

public:
	void start(); // 시작
	Simulator(); // 기본생성자
};
Simulator::Simulator()
{
	num = 0;
}
void Simulator::start()
{
	char a;

	cout << "<1> 파일 실행<qt.dat>" << endl;
	cout << "<2> 사용자 입력 실행" << endl;
	cout << "->";
	cin >> num;
	while (1)
	{
		if (num == 1) // 파일 실행 <qt.dat>
		{
			Tag T;
			Reader R;

			cout << "계속 진행하기 위해서 아무키를 입력하세요: ";
			cin >> a;

			while (IDENTIFICATION < 5)
			{
				R.creatQuery(T.sendReader());
				T.receiveQuery(R.sendQuery());
				R.responsQuery(T.sendReader());
			}
			R.result();

			break;
		}
		else if (num == 2) // 사용자 입력 실행
		{
			int n = 0; //태그 개수

			while (1)
			{
				cout << "\n";
				cout << "태그의 개수를 입력 하세요: ";
				cin >> n;

				if (n > 4 && n < 11)
				{
					break;
				}
				else
				{
					cout << "5 ~ 10 사이의 숫자를 입력하세요" << endl;
				}
			}

			Tag T(n);
			Reader R;

			T.tagprint();
			cout << "계속 진행하기 위해서 아무키를 입력하세요: ";
			cin >> a;

			while (IDENTIFICATION < n)
			{
				R.creatQuery(T.sendReader());
				T.receiveQuery(R.sendQuery());
				R.responsQuery(T.sendReader());
			}
			R.result();

			break;
		}
		else
		{
			cout << "오류!! 다시입력하세요!" << endl;
		}
	}

}












// 메인함수
int main()
{
	srand((unsigned int)time(NULL));

	Simulator S;
	S.start();






	return 0;
}