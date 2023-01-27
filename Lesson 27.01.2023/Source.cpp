#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

class Parent {
	public:
		virtual void sleep() {
			std::cout << "sleep()" << std::endl;
		}
		virtual ~Parent(){}
	};
	class Child : public Parent {
	public:
		void sleep() override{
			std::cout << "Child sleep()" << std::endl;
		}
		void gotoSchool() {
			std::cout << "gotoSchool()" << std::endl;
		}
	};

	int main() {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		Parent parent;
		Child child;

		//upcast(������� �������������� ����� ���������)
		Parent* pParent = &child;//���� ������������ 
		Parent* pParent2 = new Child();//����
		//downcast �������� ������ ������ ��� pParent ��������� �� &child
		Child* pChild = (Child*)pParent;
		//�-style ���� ��������� ������ �������� ����
		// � �������:
		// const_cast ������� �������������
		// static_cast ������� ��� � ����, �� ��������� ������ �� �� �����
		// static_cast->const_cast
		// reinterpret_cast
		//  reinterpret_cast->const_cast
		// 
		//���� ������ � �������� ������������ �� ����-�, �� ����� ��������� ����� static_cast
		//UB -������������ ���������. ��� ������ ������
		//Child *pChild2 = (Child*)&pParent;//&pParent ������� ����� ����������

		pParent->sleep();//sleep() //childsleep-���� virtual metod
		pChild->sleep();//Child sleep()
		//pChild2->sleep();

		//delete pParent;
		delete pParent2;

		//������ �������������
		//static_cast
		int a = 5;
		std::cout << "a: " << a << std::endl;
		double b = static_cast<double>(a);//������ double(a) ���  (double)a

		std::cout << "b: " << b << std::endl;
		int c = 6;
		const int* pC = &c;
		int* ppC = const_cast<int*>(pC);

		std::cout << *ppC << std::endl;
		*ppC = 4;
		std::cout << *ppC << " " << c << std::endl;

		//dynamic_cast
		//��� ������ � ���� ��������
		//���� ���� �� ����������, �� ��������� ����� ��������� �� nullptr
		//UB  ���� ������ ������ ������� �� ��������� � ����� �������� � �� ��������� ������������
		Child* pChild3 = dynamic_cast<Child*>(&parent);
		if (pChild3 == nullptr) {
			std::cout << "pChild3 is nullptr" << std::endl;
		}
		/*Parent* pParent3 = new Child();
		Child* pChild4 = dynamic_cast<Child*>(pParent3);

		delete pParent3;*/
		try{
		Child &pChild5 = dynamic_cast<Child&>(parent);
		}
		catch (std::bad_cast& e) {
			std::cout << "cast parent to child results in bad_cast\n";
				std::cout << e.what() << std::endl;
		}
		//�� �������� � ����������� ������������(��� ��� ������������ ������������)




}