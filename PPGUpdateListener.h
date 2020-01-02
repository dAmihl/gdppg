#pragma once

#ifndef PPGUpdateListener_H
#define PPGUpdateListener_H

#include "core/object.h"
#include "ppg-core/include/PuzzleUpdateListener.h"

class PPGUpdateListener : public Object, public PuzzleUpdateListener {
	GDCLASS(PPGUpdateListener, Object);

private:
	Object *manager;

public:

	PPGUpdateListener(Object* mgr);
	~PPGUpdateListener();

	virtual void onPuzzleComplete() override;
	virtual void onObjectStateChange(PuzzleObject *Obj) override;
	virtual void onNodeActive(PuzzleNode *N) override;
	virtual void onNodeComplete(PuzzleNode *N) override;
	virtual void onNodeIncomplete(PuzzleNode *N) override;
	virtual void onNoEffect(PuzzleObject *Obj) override;

};
#endif
