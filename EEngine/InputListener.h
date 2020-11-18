#pragma once
#include "../ECore/ECommon.h"
namespace E3D 
{
	//鼠标键盘监听事件
	class InputListener
	{
	public:
		virtual EBool keyPress(EInt key) = 0;
		virtual EBool keyRlease(EInt key) = 0;

		virtual EBool mouseButtonDown(EInt mouseButton) = 0;
		virtual EBool mouseButtonRlease(EInt mouseButton) = 0;

		virtual EBool mouseMove(EInt x,EInt y)=0;
		virtual EBool mouseWheel(EInt delta)=0;
		
		virtual ~InputListener() {};

	private:

	};
}