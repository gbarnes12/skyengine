#pragma once

class skyImageFilter : public skyRefBaseClass 
{
	SKY_PROPERTY_GETSET(skyBool, m_bActive, Active);

public:
	skyImageFilter()
		: m_bActive(SKY_TRUE)
	{
	}

	virtual ~skyImageFilter()
	{
	}

	virtual skyVoid skyImageFilter::Update(skyGfxRenderBatch* a_Batch) { }
	//skyVoid skyImageFilter::AddEffect ( skyImageEffect* a_pEffect );

private:
	skyBool m_bActive;
	//std::vector<skyImageEffect*> m_arrImageEffects;
};


class skySceneImageFilter : public skyImageFilter
{
public:
	virtual skyVoid skySceneImageFilter::Update(skyGfxRenderBatch* a_Batch);
private:
	skyGfxDefaultTechnique m_Technique;
};

class skyDebugImageFilter : public skyImageFilter
{
public:
	virtual skyVoid skyDebugImageFilter::Update(skyGfxRenderBatch* a_Batch);
private:
	skyGfxDebugTechnique m_Technique;
};