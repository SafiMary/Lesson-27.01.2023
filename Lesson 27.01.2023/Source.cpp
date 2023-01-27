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

		//upcast(неявное преобразование типов разрешено)
		Parent* pParent = &child;//стек нежелательно 
		Parent* pParent2 = new Child();//куча
		//downcast работает только потому что pParent указывает на &child
		Child* pChild = (Child*)pParent;
		//с-style каст выполняет первый успешный каст
		// в порядке:
		// const_cast снимает константность
		// static_cast кастует инт в дабл, но кастовать классы он не может
		// static_cast->const_cast
		// reinterpret_cast
		//  reinterpret_cast->const_cast
		// 
		//если классы в иерархии наследовании не вирт-е, то можно кастовать через static_cast
		//UB -необъяснимое поведение. так делать нельзя
		//Child *pChild2 = (Child*)&pParent;//&pParent вызвать адрес переменной

		pParent->sleep();//sleep() //childsleep-если virtual metod
		pChild->sleep();//Child sleep()
		//pChild2->sleep();

		//delete pParent;
		delete pParent2;

		//снятие константности
		//static_cast
		int a = 5;
		std::cout << "a: " << a << std::endl;
		double b = static_cast<double>(a);//Раньше double(a) или  (double)a

		std::cout << "b: " << b << std::endl;
		int c = 6;
		const int* pC = &c;
		int* ppC = const_cast<int*>(pC);

		std::cout << *ppC << std::endl;
		*ppC = 4;
		std::cout << *ppC << " " << c << std::endl;

		//dynamic_cast
		//для работы с вирт классами
		//если каст не произойдет, то указатель будет указывать на nullptr
		//UB  если кастим классы которые не находятся в одной иерархии и не явяляются виртуальными
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
		//не работает с ромбовидным наследование(где нет виртуального наследования)




}