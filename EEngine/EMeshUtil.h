#pragma once
#include "../ECore/ECommon.h"
#include "../ECore/ECore.h"
#include "EOgreMeshInfo.h"
#include <fstream>

namespace E3D 
{
	//从stream中读取字符串
	//表示要读取字符串的个数，如果size=-1,则读取一行字符串
	EString ReadString(std::ifstream &in,EInt size=-1);

	//读取Ogre mesh文件时使用
	//从stream中读取下一个标识符，对应OGREMESHID
	EUShort ReadChunk(std::ifstream &in);

	//从stream中读取一个bool型数值
	EBool ReadBool(std::ifstream &in);

	//从stream中读取一个unsined int类型数值
	EUShort ReadShort(std::ifstream &in);

	//从stream中读取一组T类型的一组数组
	template<typename T>
	std::vector<T>ReadArray(std::ifstream& in, EInt size) 
	{
		std::vector<T>v(size,0);

		in.read((char*)&v[0], sizeof(T) * size);
		return v;
	}
	//这个函数加载一个orge.mesh 二进制文件,函数实现了对Ogre.mesh文件的静态模型的静态读取
	//可以通过获取模型的顶点索引和顶点数据等模型数据，并返回一个EObject对象，如果模型有多个submesh，
	//则课通过EObject。nextobj来获取下一个submesh的指针
	EObject4D* LoadOgreMesh(const EString& meshname, const EVector4D& worldPos = EVector4D::ZERO, const EVector4D& scale = EVector4D(1, 1, 1));
}