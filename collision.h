//=============================================================================
//
// �����蔻��
// Author : Yuda Katito
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "object.h"

namespace Collision
{

enum class RECTANGLE_DIRECTION
{
	TOP = 0,
	DOWN,
	LEFT,
	RIGHT
};

// ��`�Ƌ�`
bool RectangleAndRectangle(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2);

// ��`�̐������m
bool RectangleSegment(const RECTANGLE_DIRECTION direction, const CObject* object1, const CObject* object2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool RectangleSegment(const RECTANGLE_DIRECTION direction, const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);

// �������m�̓����蔻��
bool SegmentAndSegment(const D3DXVECTOR3& start1, const D3DXVECTOR3& vec1, const D3DXVECTOR3& start2, const D3DXVECTOR3& vec2, D3DXVECTOR3* OutPos, float* t1, float* t2);

// ��`�㑤�̐����Ƌ�`
bool SegmentAndRectangleTop(const CObject* object1, const CObject* object2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool SegmentAndRectangleTop(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);

// ��`�����̐����Ƌ�`
bool SegmentAndRectangleDown(const CObject* object1, const CObject* object2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool SegmentAndRectangleDown(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);

// ��`�����̐����Ƌ�`
bool SegmentAndRectangleLeft(const CObject* object1, const CObject* object2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool SegmentAndRectangleLeft(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);

// ��`�E���̐����Ƌ�`
bool SegmentAndRectangleRight(const CObject* object1, const CObject* object2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool SegmentAndRectangleRight(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);

bool PointAndRectangle(const D3DXVECTOR3& pointPos, const D3DXVECTOR3& rectanglePos, const D3DXVECTOR3& rectangleSize);	// �_�Ƌ�`
bool Circle2DAndCircle2D(const D3DXVECTOR3& Pos1, float fRadius1, const D3DXVECTOR3& Pos2, float fRadius2);	// �~���m�̓����蔻��

};

#endif
