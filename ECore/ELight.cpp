#include "ELight.h"

namespace E3D 
{
    ELight::ELight(EInt LightId, LIGHT_TYPE type) :id(LightId),lightOn(true),lightType(type),
    ambient(255,255,255),diffuse(255,255,255),specular(255,255,255),position(0,0,0),dirction(0,0,1),
        kc(1.0f),kl(1.0f),kq(1.0f),spot_inner(45.0f),spot_outer(60.0f),power(1.0f),shadowFactor(0.05f){}

    std::vector<ELight*>* GLights = NULL;

    EInt E3D::CreateLight(LIGHT_TYPE lightType)
    {
        if (GLights==NULL)
        {
            GLights = new std::vector<ELight*>;
        }
        if ((EInt)GLights->size()> MAX_LIGHTS)
        {
            return -1;
        }

        EInt id = (EInt)GLights->size();
        GLights->push_back(new ELight(id,lightType));
    }

    ELight* E3D::GetLight(EInt id)
    {
        if (GLights==NULL||(EInt)GLights->size()>MAX_LIGHTS||id<0||id>GLights->size()-1)
        {
            return NULL;
        }
        return GLights->at(id);
    }

    EInt E3D::GetLightSize()
    {
        return GLights->size();
    }

    void E3D::DestoryAllLight()
    {
        for (LightItr itr = GLights->begin(); itr !=GLights->end(); ++itr)
        {
            SafeDelete((*itr));
        }
        GLights->clear();
        SafeDelete(GLights);
    }
   
}

