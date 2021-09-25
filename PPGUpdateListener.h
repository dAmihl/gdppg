#pragma once

#ifndef PPGUpdateListener_H
#define PPGUpdateListener_H

#include "PuzzGen.h"
#include "core/object.h"
#include "PPGNodeRef.h"

class PPGUpdateListener : public Object , public PPG::UpdateListener  {
	GDCLASS(PPGUpdateListener, Object);

private:
	Object *manager;

	Ref<PPGNodeRef> map_puzzlenode_to_noderef(PPG::Node& N);

public:
	PPGUpdateListener(Object* mgr);

	virtual void onPuzzleComplete() override;
	virtual void onObjectStateChange(PPG::Object& Obj) override;
	virtual void onNodeActive(PPG::Node& N) override;
	virtual void onNodeComplete(PPG::Node& N) override;
	virtual void onNodeIncomplete(PPG::Node& N) override;
	virtual void onNoEffect(PPG::Object& Obj) override;

};
#endif
