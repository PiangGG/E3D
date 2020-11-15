#include "EUtil.h"

namespace E3D 
{
	std::ofstream* GLogStream = NULL;

	
	bool InitLog(const EString& fileName)
	{
		if (GLogStream==NULL)
		{
			GLogStream = new std::ofstream();
			GLogStream->open(fileName.c_str());
			if (GLogStream->good())
			{
				return true;
			}
			return false;
		}

		return true;
	}

	void Log(const EChar* string, ...)
	{
		if (GLogStream==NULL)
		{
			return;
		}
		EChar buffer[256];

		//保证两者都不为空
		if (!string||!GLogStream)
		{
			return;
		}

		va_list arglist;//可变参数列表
		//利用栈上的可变参数列表打印输出字符串
		va_start(arglist,string);
		vsprintf_s(buffer,string,arglist);
		va_end(arglist);

		EString info(buffer);
		//输出流信息
		*GLogStream << info << std::endl;
		GLogStream->flush();
	}
	
	void CLoseLog()
	{
		GLogStream->close();
		SafeDelete(GLogStream);
	}

}