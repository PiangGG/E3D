#pragma once
#include "../ECore/ECommon.h"
#include "../ECore/ELight.h"
#include "../ECore/ECore.h"
#include "EMesh.h"
#include "ECamera.h"

namespace E3D 
{
	class ESceneManager 
	{
		typedef std::map<EString, EMesh*>::iterator MeshIter;

	public:

		ESceneManager();

		~ESceneManager();

		//绘制文字
		void drawString(const EString &str,EInt x,EInt y,const EColor &c=EColor(255,255,255));

		//创建一个模型实体
		EMesh* createMesh(const EString &name,const EString &meshName);
		//获取获取指定模型实体
		EMesh* getMesh(const EString &name);

		void destroyMesh(const EString &name);

		void clearMesh();
		//指定开启/关闭灯光(全局)
		void enableLights(EBool);

		EBool isLightEnable()const { return mLightEnable; };

		ELight* createLight(LIGHT_TYPE lightType);

		//获得一盏灯光，如果灯光不存在，则返回null
		ELight* getLight(EInt id);

		//获得摄像机指针
		ECamera* getCamera() { return mCamera; }
		//获取所有可见/不可见的物体个数
		EInt getTotalObjectNumber()const { return mMeshs.size(); }
		//获取当前可见物体个数 
		EInt getVisibleObjectNumber()const { return mVisibleObjectNumber; }
		//获取所有(可见/不可见) 多边形个数
		EInt getTotalPolyonNumber()const { return mTotalPolyonNumber; }

		//创建地形
		EMesh* createTerrain(const EString& rawFileName, const EString& heightMapFileName,
			EFloat uTitle = 1, EFloat vTitle = 1, EFloat blockSize = 5.0f);
		EMesh* getTerrain() { return mTerrainMesh; }

		//更新
		void update();
	protected:
		std::map<EString, EMesh*> mMeshs;
		std::map<EString, EMesh*>mUsedMesh;

		ERenderList4D* mRenderList;
		EMesh* mTerrainMesh;
		ECamera* mCamera;
		EBool mLightEnable;

		EInt mVisibleObjectNumber;
		EInt mVisiblePolyonNumber;
		EInt mTotalPolyonNumber;
	};
}