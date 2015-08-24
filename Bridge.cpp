#include<iostream>

//ʵ�ֵĽӿ�
class Drawing
{
public:
	virtual void DrawingLine(){};
	virtual void DrawCircle(){};
};
//�����������ʵ��
class V1Drawing:public Drawing
{
public:
	virtual void DrawingLine()
	{
		std::cout<<"ʹ��V1����һ����\n";
	}
	virtual void DrawCircle()
	{
		std::cout<<"ʹ��V1����һ��Բ\n";
	}
};

class V2Drawing:public Drawing
{
public:
	virtual void DrawingLine()
	{
		std::cout<<"ʹ��V2����һ����\n";
	}
	virtual void DrawCircle()
	{
		std::cout<<"ʹ��V2����һ��Բ\n";
	}
};

//����Ľӿ�
class Shape
{
private :
	Drawing* DrawingOfTool;//���ó�Ա�����ڹ��캯���б��ʼ��
protected:
	//���ｫʵ����������,���:"һ������(����)ֻʵ��һ��!!"
	void Drawline()
	{
		DrawingOfTool->DrawingLine();
	}
	void DrawCricle()
	{
		DrawingOfTool->DrawCircle();
	}
public:
	Shape(Drawing* tool ):DrawingOfTool(tool){};
	virtual void Draw(){};

};

class Rect:public Shape
{
public:
	Rect(Drawing* tool):Shape(tool){};
	virtual void Draw()
	{
		std::cout<<"����һ������\n";
		Drawline();
		Drawline();
		Drawline();
		Drawline();
	};
};

class Circle:public Shape
{
public:
	Circle(Drawing* tool):Shape(tool){};
	virtual void Draw()
	{
		std::cout<<"����һ��Բ��\n";
		DrawCricle();
	};
};

class Tri:public Shape
{
public:
	Tri(Drawing* tool):Shape(tool){}
	void Draw()
	{
		std::cout<<"����һ��������\n";
		Drawline();
		Drawline();
		Drawline();
	}
};

int main (int argc,char* argv[])
{
	//����ʵ��
	Drawing* pV1=new V1Drawing();
	Drawing* pV2=new V2Drawing();
	//ʹ��V1��Բ��������,����
	Shape* s1=new Rect(pV1);
	Shape* s2=new Circle(pV2);
	Shape* s3=new Tri(pV2);
	//��ͼ
	s1->Draw();
	s2->Draw();
	s3->Draw();
	system("pause");
	return 0;
}