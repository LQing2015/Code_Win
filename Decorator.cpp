#include<iostream>

using namespace std;

class Component
{
public:
	virtual void Operation()=0;
};

class ConcreteComponent:public Component
{
public:
	void Operation()
	{
		cout<<"Base Func\n";
	}
};

class Decorator:public Component
{
protected:
	Component* pComponent;
	void CallOperation()
	{
		pComponent->Operation();
	}
public:
	Decorator(Component* _pComponent):pComponent(_pComponent){};
};

class DecoratorA:public Decorator
{
public:
	DecoratorA(Component* p):Decorator(p){};
	void Operation()
	{
		cout<<"A"<<endl;
		CallOperation();
	}
};

class DecoratorB:public Decorator
{
public:
	DecoratorB(Component* p):Decorator(p){};
	void Operation()
	{
		cout<<"B"<<endl;
		CallOperation();
	}
};
int main()
{
	Component* m_Component=new DecoratorA(new DecoratorB(new ConcreteComponent()));
	m_Component->Operation();
	system("pause");
	return 0;
}