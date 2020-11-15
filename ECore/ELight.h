#pragma once

#include "ECommon.h"
#include "EVector.h"

namespace E3D
{
	enum LIGHT_TYPE
	{
		LIGHT_AMBIENT=0,	//环境光
		LIGHT_DIRECTION=1,	//平行光
		LIGHT_POINT=2,		//点光源
	};

	struct ELight
	{
		EInt id;				//灯光分配的id全局唯一
		EBool lightOn;			//灯光是否启用

		LIGHT_TYPE lightType;	//灯光类型

		EFloat power;			//灯光强度，默认1.0f
		EFloat shadowFactor;	//灯光背面强度，默认为0.05f;

		EColor ambient;			//灯光环境色
		EColor diffuse;			//灯光漫反射颜色
		EColor specular;		//灯光高光颜色

		EVector4D position;		//灯光世界坐标位置
		EVector4D dirction;		//光源朝向，点光源无效

		EVector4D transPosion;	//灯光摄像机位置
		EVector4D transDirction;//摄像机光源朝向，点光源无效

		EFloat kc, kl, kq;		//衰减因子

		EFloat spot_inner;		//聚光灯内锥角
		EFloat spot_outer;		//聚光灯外锥角
		EFloat pf;				//聚光灯指数因子

		ELight(EInt LightId, LIGHT_TYPE type);
	};

	//最大灯光数
	#define MAX_LIGHTS 8
	//全局灯光管理
	extern std::vector<ELight*>* GLights;
	
	typedef std::vector<ELight*>::iterator LightItr;

	//创建一个新的灯光，创建成功fan'hui灯光ID(全局唯一),创建失败返回-1;
	//场景内最大灯光数为 MAX_LIGHTS
	extern EInt CreateLight(LIGHT_TYPE lightType);

	//获得一个灯光，如果灯光不存在，则返回NULL
	extern ELight* GetLight(EInt id);
	extern EInt GetLightSize();
	//清除全部光源
	extern void DestoryAllLight();
};