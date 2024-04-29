#pragma once
#pragma once

#include "Map/TMap.h"
#include "Utilities/FileStream.h"

class Base11 : public IObject {
public:
	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	TMap* GrassLandBase = nullptr;
	TMap* GrassLandBorderDown = nullptr;
	TMap* GrassLandBorderLeft = nullptr;
	TMap* GrassLandBorderRight = nullptr;
	TMap* GrassLandBorder = nullptr;
	TMap* GrassLandBorderUp = nullptr;
};