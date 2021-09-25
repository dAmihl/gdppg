#include "PPGUpdateListener.h"


Ref<PPGNodeRef> PPGUpdateListener::map_puzzlenode_to_noderef(PPG::Node& N) {
	Ref<PPGNodeRef> ref;
	ref.instance();
	ref->set_object_name(String(N.getRelatedObject().getObjectName().c_str()));
	ref->set_current_state(String(N.getRelatedObject().getCurrentState().getName().c_str()));
	return ref;
}

PPGUpdateListener::PPGUpdateListener(Object *mgr) {
	this->manager = mgr;
}

void PPGUpdateListener::onPuzzleComplete() {
	this->manager->emit_signal("ppg_puzzle_complete");
}

void PPGUpdateListener::onObjectStateChange(PPG::Object& Obj) {
	this->manager->emit_signal("ppg_object_state_change", Obj.getObjectName().c_str(), Obj.getCurrentState().getName().c_str());
}

void PPGUpdateListener::onNodeActive(PPG::Node& N) {
	Ref<PPGNodeRef> ref = map_puzzlenode_to_noderef(N);
	this->manager->emit_signal("ppg_node_active", ref);
}

void PPGUpdateListener::onNodeComplete(PPG::Node& N) {
	Ref<PPGNodeRef> ref = map_puzzlenode_to_noderef(N);
	this->manager->emit_signal("ppg_node_complete", ref);
}

void PPGUpdateListener::onNodeIncomplete(PPG::Node& N) {
	Ref<PPGNodeRef> ref = map_puzzlenode_to_noderef(N);
	this->manager->emit_signal("ppg_node_incomplete", ref);
}

void PPGUpdateListener::onNoEffect(PPG::Object& Obj) {
	this->manager->emit_signal("ppg_event_no_effect", Obj.getObjectName().c_str());
}


