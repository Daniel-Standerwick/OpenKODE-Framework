#ifndef __cocos2dx_studio_h__
#define __cocos2dx_studio_h__

#include "XMJs/jsapi.h"
#include "XMJs/jsfriendapi.h"


extern JSClass  *jsb_ActionManagerEx_class;
extern JSObject *jsb_ActionManagerEx_prototype;

JSBool js_cocos2dx_studio_ActionManagerEx_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ActionManagerEx_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ActionManagerEx(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_ActionManagerEx_playActionByName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ActionManagerEx_getActionByName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ActionManagerEx_releaseActions(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ActionManagerEx_purgeActionManager(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ActionManagerEx_shareManager(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_Bone_class;
extern JSObject *jsb_Bone_prototype;

JSBool js_cocos2dx_studio_Bone_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Bone_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Bone(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_Bone_isTransformDirty(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_isIgnoreMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_updateZOrder(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setTransformDirty(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getDisplayRenderNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_addChildBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getWorldInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getTween(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getParentBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getBlendType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_updateColor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setOpacity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getDisplayRenderNodeType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_removeDisplay(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_updateDisplayedOpacity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setParentBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setZOrder(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getColliderFilter(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setIgnoreMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_removeFromParent(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getChildArmature(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_update(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getTweenData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setColliderFilter(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getColliderBodyList(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setArmature(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_addDisplay(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getNodeToWorldTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setColor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_removeChildBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setChildArmature(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getNodeToArmatureTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getDisplayManager(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getArmature(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_setBlendType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_changeDisplayByIndex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_updateDisplayedColor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_getBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Bone_Bone(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_BatchNode_class;
extern JSObject *jsb_BatchNode_prototype;

JSBool js_cocos2dx_studio_BatchNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_BatchNode_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_BatchNode(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_BatchNode_addChild(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_BatchNode_getTexureAtlasWithTexture(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_BatchNode_removeChild(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_BatchNode_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ArmatureAnimation_class;
extern JSObject *jsb_ArmatureAnimation_prototype;

JSBool js_cocos2dx_studio_ArmatureAnimation_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ArmatureAnimation_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ArmatureAnimation(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_ArmatureAnimation_getSpeedScale(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_play(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_pause(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_getUserObject(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_setAnimationInternal(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_gotoAndPause(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_resume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_stop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_setAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_setSpeedScale(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_update(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_getAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_playByIndex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_getMovementCount(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_setUserObject(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureAnimation_ArmatureAnimation(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ArmatureDataManager_class;
extern JSObject *jsb_ArmatureDataManager_prototype;

JSBool js_cocos2dx_studio_ArmatureDataManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ArmatureDataManager_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ArmatureDataManager(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_ArmatureDataManager_getAnimationDatas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_removeAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_addArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_getTextureDatas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_getTextureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_getAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_addAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_removeArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_getArmatureDatas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_removeTextureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_addTextureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_destoryInstance(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ArmatureDataManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_Armature_class;
extern JSObject *jsb_Armature_prototype;

JSBool js_cocos2dx_studio_Armature_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Armature_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Armature(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_Armature_getBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_changeBoneParent(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getTexureAtlasWithTexture(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_setAnimation(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getBoneAtPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getArmatureTransformDirty(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_setVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_updateOffsetPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_setColliderFilter(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_setName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_removeBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getNodeToParentTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_setParentBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getBoundingBox(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_setBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_draw(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_setArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_setTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_addBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_update(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getParentBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getAnimation(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getBoneDic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_getTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Armature_Armature(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_Skin_class;
extern JSObject *jsb_Skin_prototype;

JSBool js_cocos2dx_studio_Skin_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Skin_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Skin(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_Skin_getBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_getNodeToWorldTransformAR(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_getNodeToWorldTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_updateTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_getDisplayName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_updateArmatureTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_initWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_initWithFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_setBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_Skin_Skin(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ComAttribute_class;
extern JSObject *jsb_ComAttribute_prototype;

JSBool js_cocos2dx_studio_ComAttribute_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComAttribute_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComAttribute(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_ComAttribute_getFloat(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAttribute_setFloat(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAttribute_setCString(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAttribute_getCString(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAttribute_getBool(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAttribute_setInt(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAttribute_getInt(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAttribute_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAttribute_setBool(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAttribute_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ComAudio_class;
extern JSObject *jsb_ComAudio_prototype;

JSBool js_cocos2dx_studio_ComAudio_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComAudio_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComAudio(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_ComAudio_stopAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_getEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_stopEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_end(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_isEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_stopBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_pauseBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_isLoop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_pauseAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_preloadBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_playBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_playEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_resumeAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_unloadEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_rewindBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_preloadEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_pauseEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_resumeBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_setFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_setEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_getFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_resumeEffect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComAudio_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_InputDelegate_class;
extern JSObject *jsb_InputDelegate_prototype;

JSBool js_cocos2dx_studio_InputDelegate_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_InputDelegate_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_InputDelegate(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_InputDelegate_setKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_InputDelegate_getTouchMode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_InputDelegate_isKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_InputDelegate_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_InputDelegate_setTouchPriority(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_InputDelegate_getTouchPriority(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_InputDelegate_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_InputDelegate_setTouchMode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ComController_class;
extern JSObject *jsb_ComController_prototype;

JSBool js_cocos2dx_studio_ComController_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComController_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComController(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_ComController_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComController_isEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComController_update(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComController_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComController_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComController_ComController(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ComRender_class;
extern JSObject *jsb_ComRender_prototype;

JSBool js_cocos2dx_studio_ComRender_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComRender_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComRender(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_ComRender_getNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_ComRender_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_GUIReader_class;
extern JSObject *jsb_GUIReader_prototype;

JSBool js_cocos2dx_studio_GUIReader_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_GUIReader_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_GUIReader(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_GUIReader_widgetFromJsonFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_GUIReader_getVersionInteger(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_GUIReader_purgeGUIReader(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_GUIReader_shareReader(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_SceneReader_class;
extern JSObject *jsb_SceneReader_prototype;

JSBool js_cocos2dx_studio_SceneReader_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_SceneReader_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_SceneReader(JSContext *cx, JSObject *global);
void register_all_cocos2dx_studio(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_studio_SceneReader_purgeSceneReader(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_SceneReader_createNodeWithSceneFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_SceneReader_sceneReaderVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_studio_SceneReader_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
#endif

