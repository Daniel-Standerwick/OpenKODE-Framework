#ifndef JOINT_H_
#define JOINT_H_

#include "3d/C3DNode.h"

namespace cocos3d
{
	
class C3DAnimation;

class AnimationValue;
class C3DAnimationChannel;
/**
 * Defines a basic hierachial structure of transformation spaces.
 */
class C3DBone : public C3DNode
{
    friend class C3DNode;
    friend class C3DMeshSkin;
    friend class C3DResourceLoader;
	friend class C3DAnimationClip;

public:

    /**
     * @see C3DNode::getType()
     */
    C3DNode::Type getType() const;

    /**
     * Returns the inverse bind pose matrix for this joint.
     * 
     * @return Inverse bind pose matrix.
     */
    const C3DMatrix& getInverseBindPose();
	
	/**
     * Get animation by id.
     */
	C3DAnimation* getAnimation(const char* id = NULL);

	/**
     * Add AnimationChannel.
     */
	void addChannel(C3DAnimationChannel* channel);

	/**
     * Remove AnimationChannel.
     */
    void removeChannel(C3DAnimationChannel* channel);

	/**
     * Get AnimationChannel by specified  id.
     */
    C3DAnimationChannel* getChannel(const char* id) const;

	/**
     * Set AnimationValue.
     */
	void setAnimationValue(AnimationValue* value, float blendWeight = 1.0f);

	bool getSelect(){return _bSelect;}
	void setSelect(bool bSelect){_bSelect = bSelect;}
protected:
	/**
     * Constructor.
     */
    C3DBone(const char* id);

	/**
     * Destructor.
     */
    virtual ~C3DBone();

	/**
     * Creates C3DBone.
     */
    static C3DBone* create(const char* id);

    /**
     * Sets the inverse bind pose matrix.
     * 
     * @param m C3DMatrix representing the inverse bind pose for this Joint.
     */
    void setInverseBindPose(const C3DMatrix& m);

    /**
     * Updates the joint matrix.
     * 
     * @param bindShape The bind shape matrix.
     * @param matrixPalette The matrix palette to update.
     */
    void updateJointMatrix(const C3DMatrix& bindShape, C3DVector4* matrixPalette);

    /**
     * Called when this Joint's transform changes.
     */
    void transformChanged();	

	 /**
     * Clone.
     */
    virtual C3DNode* clone(C3DNode::CloneContext& context) const;    


protected:   
	/**
     * Copy frome other.
     */
    virtual void copyFrom(const C3DTransform* other, CloneContext& context);

protected:

    /** 
     * The C3DMatrix representation of the Joint's bind pose.
     */
    C3DMatrix _bindPose;
    
    /** 
     * Flag used to mark if the Joint's matrix is dirty.
     */
    bool _jointMatrixDirty;
    
    /** 
     * The number of MeshSkin's influencing the Joint.
     */
    unsigned int _skinCount;
	
	std::vector<C3DAnimationChannel*>* _animationChannels;   // Collection of all animation channels

	bool _bSelect; // for editor
    
};

}

#endif
