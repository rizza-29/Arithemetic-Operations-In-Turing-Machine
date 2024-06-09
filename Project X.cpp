#include<iostream>
using namespace std;

class Node {
public:
	char a;
	Node* next;
	Node* prev;
	Node() {
		a = ' ';
		next = NULL;
		prev = NULL;
	}
	Node(char b) {
		a = b;
		next = NULL;
		prev = NULL;
	}
	Node(char b, Node* next, Node* prev) {
		a = b;
		this->next = next;
		this->prev = prev;
	}
};

class tape {
public:
	Node* head, * tail;
	tape() {
		head = NULL;
		tail = NULL;
	}
	void InsertAtHead(char a) {
		if (head == NULL) {
			head = new Node(a);
		}
		else {
			Node* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = new Node(a);
			temp->next->prev = temp;
		}
	}
	void Add() {
		Node* temp = head;
		while (temp->a != '+') {
			temp = temp->next;
		}
		temp = temp->next;
		temp = temp->next;
		int i = 1, j = 1, num = 0, n = 1, carry = 0, sum = 0, flag = 0;
		while (flag == 0 || temp->a != '+') {
			num = carry;
			carry = 0;
			while (temp->a != '+') {
				temp = temp->prev;
			}
			while (temp->a != 's' && i > 0) {
				temp = temp->prev;
				i /= 10;
			}
			if (temp->a != 's') {
				num += (temp->a % 48);
			}
			else {
				flag = 1;
			}
			while (temp->a != 'e') {
				temp = temp->next;
			}
			while (temp->a != '+' && j > 0) {
				temp = temp->prev;
				j /= 10;
			}
			if (temp->a != '+') {
				num += (temp->a % 48);
			}
			if (num > 9) {
				carry = num / 10;
				num = num % 10;
			}
			num *= n;
			n *= 10;
			i = n;
			j = n;
			sum += num;
		}
		cout << "The sum of the given string is : " << sum << endl;
	}
	void Subtract() {
		Node* temp = head;
		while (temp->a != '-') {
			temp = temp->next;
		}
		temp = temp->next;
		temp = temp->next;
		int i = 1, j = 1, num = 0, n = 1, borrow = 0, sub = 0, flag = 0, bflag = 0 ;
		while (flag == 0 || temp->a != '-') {
			num = 0;
			num -= borrow;
			borrow = 0;
			while (temp->a != '-') {
				temp = temp->prev;
			}
			while (temp->a != 's' && i > 0) {
				temp = temp->prev;
				i /= 10;
			}
			if (temp->a != 's') {
				num += (temp->a % 48);
			}
			else {
				flag = 1;
			}
			if (temp->prev != NULL && temp->prev->a == 's') {
				bflag = 1;
			}
			while (temp->a != 'e') {
				temp = temp->next;
			}
			while (temp->a != '-' && j > 0) {
				temp = temp->prev;
				j /= 10;
			}
			if (temp->a != '-') {
				if (bflag == 0 && num < (temp->a%48)) {
					num += 10;
					borrow = 1;
				}
				num -= (temp->a % 48);
			}
			num *= n;
			n *= 10;
			i = n;
			j = n;
			sub += num;
		}
		cout << "The subtraction of the given string is : " << sub << endl;
	}
	void Modulus() {
		Node* temp = head;
		int i = 1, j = 1, num = 0, num1 = 0, n = 1, carry = 0, mod = 0, flag = 0;
		while (temp->next->a != 'e') {
			temp = temp->next;
		}
		while (temp->a != '%') {
			num1 += ((temp->a % 48)*j);
			temp = temp->prev;
			j *= 10;
		}
		temp = temp->prev;
		while (temp->a != 's') {
			if (temp->a == 's')
				break;
			else {
				num += ((temp->a % 48) * n);
			}
			if (num >= num1) {
				num %= num1;
			}
			n *= 10;
			i = 1;
			temp = temp->prev;
		}
		cout << "The modulus of the given string is : " << num << endl;
	}
	void Division() {
		Node* temp = head;
		float div = 0, num = 0, num1 = 0, j = 1 , i = 1, n = 1, val = 48;
		while (temp->next->a != 'e') {
			temp = temp->next;
		}
		while (temp->a != '/') {
			num1 += ((temp->a % 48) * j);
			temp = temp->prev;
			j *= 10;
		}
		temp = temp->prev;
		while (temp->a != 's') {
			if (temp->a == 's')
				break;
			else {
				num = ((temp->a % 48) * n);
			}
			div += (num*10) / (num1*10);
			n *= 10;
			temp = temp->prev;
		}
		cout << "The division of the given string is : " << div << endl;
	}
	void Multiplication() {
		Node* temp = head;
		int i = 1, j = 1, n = 1;
		float mul = 0, num = 0, num1 = 0;
		while (temp->next->a != 'e') {
			temp = temp->next;
		}
		while (temp->a != '*') {
			num1 += ((temp->a % 48) * j);
			temp = temp->prev;
			j *= 10;
		}
		temp = temp->prev;
		while (temp->a != 's') {
			if (temp->a == 's')
				break;
			else {
				num = ((temp->a % 48) * n);
			}
			mul += num * num1;
			n *= 10;
			i = 1;
			temp = temp->prev;
		}
		cout << "The multiplication of the given string is : " << mul << endl;
	}
	void print() {
		Node* temp = head;
		while (temp != NULL) {
			cout << temp->a;
			temp = temp->next;
		}
	}
};
int main() {
	string str;
	cout << "Enter string : ";
	cin >> str;
	tape t;
	t.InsertAtHead('s');
	for (int i = 0; i < str.length(); i++) {
		t.InsertAtHead(str[i]);
	}
	t.InsertAtHead('e');
	t.print();
	cout << endl;
	Node* temp = t.head;
	while (temp != NULL) {
		if (temp->a == '+') {
			t.Add();
			break;
		}
		else if (temp->a == '-') {
			t.Subtract();
			break;
		}
		else if (temp->a == '*') {
			t.Multiplication();
			break;
		}
		else if (temp->a == '/') {
			t.Division();
			break;
		}
		else if (temp->a == '%') {
			t.Modulus();
			break;
		}
		temp = temp->next;
	}
	if (temp == NULL) {
		cout << "No operators in the string !" << endl;
	}
}