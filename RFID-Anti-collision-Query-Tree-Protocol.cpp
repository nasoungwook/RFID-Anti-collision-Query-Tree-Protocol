#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<stack>
#include<fstream>

using namespace std;


int IDENTIFICATION = 0; //1���� ��尡 ������ Ƚ��

//����
class Reader { // ���� �ָӴ�

	int cycle; // 2���̻� ��尡 ������ Ƚ��
	int IDLE; // 0���� ��尡 ������ Ƚ��
	int COLLISION;

	string temp; // ���ÿ��� ���� ���� ����
	stack<string> g;

public:
	Reader();//�⺻������
	Reader(int); // ��ȯ������
	Reader(Reader& R);//���������

	void result();
	void creatQuery(int);  //�±׵鿡�� ���� ���� �޼����� ����� �Լ�
	string sendQuery();   //�±׵鿡�� ���� �޼����� ������ �Լ�
	void responsQuery(int); //�±׵�� ���� ���� ����޼����� ó���ϴ� �Լ�
};
Reader::Reader() // �⺻������
{
	cycle = 0;
	IDLE = 0;
	COLLISION = 0;
}

Reader::Reader(int n)//��ȯ ������
{
	cout << "��ȯ������" << endl;
}
Reader::Reader(Reader &R)//���������
{
	cout << "���������" << endl;
}

void Reader::creatQuery(int tagNum)//�±׵鿡�� ���� ���� �޼����� ����� �Լ�
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

string Reader::sendQuery()//�±׵鿡�� ���� �޼����� ������ �Լ�
{
	cout << "\n";
	cycle++;
	cout << "==== " << cycle << " cycle" << " ====" << endl;
	return temp;
}
void Reader::responsQuery(int tagNum)//�±׵�� ���� ���� ����޼����� ó���ϴ� �Լ�
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











class Tag  // �±� ���̵� ��� �ִ� ����
{
	string ID[10];
	int num; // �±��� ����
	int count;

public:
	Tag(); // �⺻������
	Tag(int); // ��ȯ������
	Tag(Tag& T); // ���������

	void receiveQuery(string); //���Ǹ� �����ϰ� ó���ϴ� �Լ�
	int sendReader(); //�������� �޼����� ������ �Լ�
	void tagprint(); // �±��� ����(�±� �̸��� ���̵�)�� ����ϴ� �Լ�
	void creat_bin(int); // �±��� ���̵� ����� �Լ�
};
Tag::Tag() // �⺻ ������
{
	char c;
	int i = 0;
	int n = 1;
	string buffer[6];

	ifstream is;

	is.open("qt.dat"); // ������ �д´�.
	cout << "\n";
	if (!is.fail()){
		cerr << "qt.dat �κ��� ���������� �±׸� �о����ϴ�!" << endl;
	}

	is.get(c);
	while (!is.eof()) // �а� �и��ؼ� �迭�� �ִ´�.
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

	num = (int)buffer[0].at(0)-'0'; // ù���� 5�� ������ �ִ´�.
	for (int i = 1; i < 6; i++) // �������� �±׿� �ִ´�
	{
		ID[i-1] = buffer[i];
		cout << "Tag"<<i-1<<": " <<ID[i - 1] << endl;
	}
	count = -1;

	is.close();

}
Tag::Tag(int n) // ��ȯ ������
{
	num = n;
	creat_bin(n);
	count = -1;
}
Tag::Tag(Tag& T) // ���������
{
	cout << "���������" << endl;
}

void Tag::receiveQuery(string querybag) // ���Ǹ� �����ϰ� ó���ϴ� �Լ�
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
				if (querybag.at(0) == ID[i].at(0) && querybag.at(1) == ID[i].at(1) && querybag.at(2) == ID[i].at(2) && querybag.at(3) == ID[i].at(3))//�׹�° ��
				{
					cout << "Response: " << ID[i] << " <TAG" << i << ">" << endl;
					count++;
				}

			}
			else if (querybag.length() == 3)
			{
				if (querybag.at(0) == ID[i].at(0) && querybag.at(1) == ID[i].at(1) && querybag.at(2) == ID[i].at(2))//����° ��
				{
					cout << "Response: " << ID[i] << " <TAG" << i << ">" << endl;
					count++;
				}
			}
			else if (querybag.length() == 2)
			{
				if (querybag.at(0) == ID[i].at(0) && querybag.at(1) == ID[i].at(1))//�ι�° ��
				{
					cout << "Response: " << ID[i] << " <TAG" << i << ">" << endl;
					count++;
				}
			}
			else if (querybag.length() == 1)
			{
				if (querybag.at(0) == ID[i].at(0))// ù��° ��
				{
					cout << "Response: " << ID[i] << " <TAG" << i << ">" << endl;
					count++;
				}
			}
			else
			{
				cout << "����!!" << endl;
			}
		}
	}
}
int Tag::sendReader() // �������� �޽����� ������ �Լ�
{
	return count;
}
void Tag::tagprint()  // �±��� ������ ����ϴ� �Լ�
{
	for (int i = 0; i < num; i++)
	{
		cout << "Tag" << i << ": " << ID[i] << endl;
	}
}

void Tag::creat_bin(int n) // �������� �������� �̾Ƽ� 2������ ����  
{
	int temp1[10]; //������ �������� �̾� �����ϴ� �迭
	char temp2[5];

	for (int i = 0; i < n; i++)// �������� 0���� 15���� �±��� ������ŭ �������� �̴´�.
	{
		temp1[i] = rand() % 15; //0~15���� �������� �̴´�.

		for (int j = 0; j < i; j++)//�ߺ��˻�
		{
			if (temp1[i] == temp1[j])
			{
				i--;
			}
		}
		_itoa_s(temp1[i], temp2, 2);

		ID[i] = temp2;

		//���ڿ��� 4�ڸ��� ���߱����ؼ� �տ� 0�� �ִ´�.
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
	void start(); // ����
	Simulator(); // �⺻������
};
Simulator::Simulator()
{
	num = 0;
}
void Simulator::start()
{
	char a;

	cout << "<1> ���� ����<qt.dat>" << endl;
	cout << "<2> ����� �Է� ����" << endl;
	cout << "->";
	cin >> num;
	while (1)
	{
		if (num == 1) // ���� ���� <qt.dat>
		{
			Tag T;
			Reader R;

			cout << "��� �����ϱ� ���ؼ� �ƹ�Ű�� �Է��ϼ���: ";
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
		else if (num == 2) // ����� �Է� ����
		{
			int n = 0; //�±� ����

			while (1)
			{
				cout << "\n";
				cout << "�±��� ������ �Է� �ϼ���: ";
				cin >> n;

				if (n > 4 && n < 11)
				{
					break;
				}
				else
				{
					cout << "5 ~ 10 ������ ���ڸ� �Է��ϼ���" << endl;
				}
			}

			Tag T(n);
			Reader R;

			T.tagprint();
			cout << "��� �����ϱ� ���ؼ� �ƹ�Ű�� �Է��ϼ���: ";
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
			cout << "����!! �ٽ��Է��ϼ���!" << endl;
		}
	}

}












// �����Լ�
int main()
{
	srand((unsigned int)time(NULL));

	Simulator S;
	S.start();






	return 0;
}