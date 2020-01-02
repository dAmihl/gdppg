#include "PPGUpdateListener.h"

PPGUpdateListener::PPGUpdateListener(Object* mgr) {
	this->manager = mgr;
}

PPGUpdateListener::~PPGUpdateListener() {
}

void PPGUpdateListener::onPuzzleComplete() {
	this->manager->emit_signal("ppg_puzzle_complete");
}

void PPGUpdateListener::onObjectStateChange(PuzzleObject *Obj) {
	this->manager->emit_signal("ppg_object_state_change", Obj->getObjectName().c_str());
}

void PPGUpdateListener::onNodeActive(PuzzleNode *N) {
	this->manager->emit_signal("ppg_node_active", "");
}

void PPGUpdateListener::onNodeComplete(PuzzleNode *N) {
	this->manager->emit_signal("ppg_node_complete", "");
}

void PPGUpdateListener::onNodeIncomplete(PuzzleNode *N) {
	this->manager->emit_signal("ppg_node_incomplete", "");
}

void PPGUpdateListener::onNoEffect(PuzzleObject *Obj) {
	this->manager->emit_signal("ppg_event_no_effect", Obj->getObjectName().c_str());
}
