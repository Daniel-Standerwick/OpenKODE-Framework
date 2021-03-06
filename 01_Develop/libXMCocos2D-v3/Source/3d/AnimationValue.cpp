#include "3d/Base.h"
#include "3d/AnimationValue.h"

namespace cocos3d
{

AnimationValue::AnimationValue(unsigned int componentCount)
  : _componentCount(componentCount), _componentSize(componentCount * sizeof(float))
{
    _value = new float[_componentCount];
}

AnimationValue::~AnimationValue()
{
    SAFE_DELETE_ARRAY(_value);
}

float AnimationValue::getFloat(unsigned int index) const
{
    assert(index < _componentCount);

    return _value[index];
}

void AnimationValue::setFloat(unsigned int index, float value)
{
    assert(index < _componentCount);

    _value[index] = value;
}


}
