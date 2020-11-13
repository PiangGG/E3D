#pragma once
//用于自定义结构体声明
/*定义这个头文件主要是把引擎用到的自定义结构体，如颜色，二维向量,三维向量，游戏对象，三维平面，矩阵，多边形
，渲染列表，透视体等在头文件中声明
在写代码之前先通过模块化把需要实现的内容画出来，这样对要实现的内容一目了然
*/
namespace E3D 
{
	struct	EColor;//颜色
	struct EVector2D;//二维向量
	struct EVector3D;//三维向量
	struct EVector4D;//四维向量
	struct EMatrix44;//4*4矩阵

	struct EVertex4D;//顶点
	struct EPolyon4D;//基于顶点的多边形
	struct EPolyonF4D;//基于索引的多边形
	struct EObject;//对象
	struct EPlane; //三维平面
	struct ERenderList4D;//渲染列表

	struct EFrustum;//透视体
}