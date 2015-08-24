#include<iostream>

//实现的接口
class Drawing
{
public:
	virtual void DrawingLine(){};
	virtual void DrawCircle(){};
};
//具体的若干种实现
class V1Drawing:public Drawing
{
public:
	virtual void DrawingLine()
	{
		std::cout<<"使用V1画了一条线\n";
	}
	virtual void DrawCircle()
	{
		std::cout<<"使用V1画了一个圆\n";
	}
};

class V2Drawing:public Drawing
{
public:
	virtual void DrawingLine()
	{
		std::cout<<"使用V2画了一条线\n";
	}
	virtual void DrawCircle()
	{
		std::cout<<"使用V2画了一个圆\n";
	}
};

//抽象的接口
class Shape
{
private :
	Drawing* DrawingOfTool;//引用成员必须在构造函数列表初始化
protected:
	//这里将实现提至基类,遵从:"一个规则(方法)只实现一次!!"
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
		std::cout<<"绘制一个矩形\n";
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
		std::cout<<"绘制一个圆形\n";
		DrawCricle();
	};
};

class Tri:public Shape
{
public:
	Tri(Drawing* tool):Shape(tool){}
	void Draw()
	{
		std::cout<<"绘制一个三角形\n";
		Drawline();
		Drawline();
		Drawline();
	}
};

int main (int argc,char* argv[])
{
	//两种实现
	Drawing* pV1=new V1Drawing();
	Drawing* pV2=new V2Drawing();
	//使用V1画圆与三角形,矩形
	Shape* s1=new Rect(pV1);
	Shape* s2=new Circle(pV2);
	Shape* s3=new Tri(pV2);
	//绘图
	s1->Draw();
	s2->Draw();
	s3->Draw();
	system("pause");
	return 0;
}