#include "PPGUpdateListener.h"

Ref<PPGNodeRef> PPGUpdateListener::map_puzzlenode_to_noderef(PuzzleNode *N) {
	Ref<PPGNodeRef> ref;
	ref.instance();
	ref->set_object_name(String(N->getRelatedObject()->getObjectName().c_str()));
	ref->set_current_state(String(N->getRelatedObject()->getCurrentState().getStateName().c_str()));
	return ref;
}

PPGUpdateListener::PPGUpdateListener(Object *mgr) {
	this->manager = mgr;
}

PPGUpdateListener::~PPGUpdateListener() {
}

void PPGUpdateListener::onPuzzleComplete() {
	this->manager->emit_signal("ppg_puzzle_complete");
}

void PPGUpdateListener::onObjectStateChange(PuzzleObject *Obj) {
	this->manager->emit_signal("ppg_object_state_change", Obj->getObjectName().c_str(), Obj->getCurrentState().getStateName().c_str());
}

void PPGUpdateListener::onNodeActive(PuzzleNode *N) {
	Ref<PPGNodeRef> ref = this->map_puzzlenode_to_noderef(N);
	this->manager->emit_signal("ppg_node_active", ref);
}

void PPGUpdateListener::onNodeComplete(PuzzleNode *N) {
	Ref<PPGNodeRef> ref = this->map_puzzlenode_to_noderef(N);
	this->manager->emit_signal("ppg_node_complete", ref);
}

void PPGUpdateListener::onNodeIncomplete(PuzzleNode *N) {
	Ref<PPGNodeRef> ref = this->map_puzzlenode_to_noderef(N);
	this->manager->emit_signal("ppg_node_incomplete", ref);
}

void PPGUpdateListener::onNoEffect(PuzzleObject *Obj) {
	this->manager->emit_signal("ppg_event_no_effect", Obj->getObjectName().c_str());
}
