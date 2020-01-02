/* gdppg.cpp */

#include "gdppg.h"

void GdPPG::generate_puzzle() {
	this->currentPuzzle = this->puzzGen->generatePuzzle(this->objects, this->events, this->rules);
	this->currentPuzzle->setUpdateListener(this->update_listener);
}

void GdPPG::add_object(Variant objectData) {

	String object_name = objectData.call("get_object_name");
	Array states = objectData.call("get_states");
	Dictionary transitions = objectData.call("get_transitions");
	String default_state = objectData.call("get_default_state");

	PuzzleObject *tmpObject = new PuzzleObject(object_name.ascii().get_data());
	tmpObject->setTemplateName(object_name.ascii().get_data());

	HashMap<String, PuzzleState *> stateMap;
	PuzzleList<PuzzleState *>::Type statesList;

	for (int i = 0; i < states.size(); i++) {
		String stateName = states[i];
		PuzzleState *tmpState = new PuzzleState(stateName.ascii().get_data());
		stateMap.set(stateName, tmpState);
		statesList.push_back(tmpState);
	}

	StateTransition *stateTransition = new StateTransition();

	for (int j = 0; j < transitions.size(); j++) {
		String event_name = transitions.get_key_at_index(j);
		Array state_pairs = transitions.get_value_at_index(j);

		for (int i = 0; i < state_pairs.size(); i++) {
			Array state_pair = state_pairs.get(i);
			String left_state = state_pair.get(0);
			String right_state = state_pair.get(1);

			PuzzleState *tmpS1 = stateMap.get(left_state);
			PuzzleState *tmpS2 = stateMap.get(right_state);

			stateTransition->addTransition(event_name.ascii().get_data(), *tmpS1, *tmpS2);
		}

		PuzzleEvent *tmpEvent = new PuzzleEvent(event_name.ascii().get_data(), tmpObject);
		this->events_map.set(event_name, tmpEvent);
		this->events.push_back(tmpEvent);
	}
	tmpObject->setStateTransition(*stateTransition);

	PuzzleState *defSt;
	if (default_state.empty()) {
		defSt = statesList.at(0);
	} else {
		defSt = stateMap.get(default_state);
	}
	// First state in array is default state
	tmpObject->setCurrentState(*defSt);

	this->objects.push_back(tmpObject);
}

String GdPPG::get_puzzle_textual_representation() {
	return String(this->currentPuzzle->getExtendedTextualRepresentation().c_str());
}

Ref<PPGNodeRef> GdPPG::get_puzzle_graph_representation() {
	T_PuzzleGraphNodeList rootNodes = this->currentPuzzle->getGraphRepresentation();

	PuzzleGraphNode *root = rootNodes.at(0);

	Ref<PPGNodeRef> ref = map_puzzlegraphnode_for_gdscript(root);

	return ref;
}

void GdPPG::handle_event(String event_name) {
	PuzzleEvent* tmpEvent = this->events_map.get(event_name);
	this->currentPuzzle->handleEvent(*tmpEvent);
}

Ref<PPGNodeRef> GdPPG::map_puzzlegraphnode_for_gdscript(PuzzleGraphNode *node) {
	Ref<PPGNodeRef> nodeRef;
	nodeRef.instance();

	PuzzleObject* tmpObj = node->getObject();

	nodeRef->set_object_name(String(tmpObj->getObjectName().c_str()));
	nodeRef->set_template_name(String(tmpObj->getTemplateName().c_str()));
	nodeRef->set_current_state(String(tmpObj->getCurrentState().getStateName().c_str()));

	T_PuzzleGraphNodeList children = node->getChildren();

	for (T_PuzzleGraphNodeList::iterator c = children.begin(); c != children.end(); ++c) {
		Ref<PPGNodeRef> child = map_puzzlegraphnode_for_gdscript(*c);
		nodeRef->add_child(&child);
	}

	return nodeRef;
}

void GdPPG::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_object", "ppg_object_data"), &GdPPG::add_object);
	ClassDB::bind_method(D_METHOD("generate_puzzle"), &GdPPG::generate_puzzle);
	ClassDB::bind_method(D_METHOD("get_puzzle_textual_representation"), &GdPPG::get_puzzle_textual_representation);
	ClassDB::bind_method(D_METHOD("get_puzzle_graph_representation"), &GdPPG::get_puzzle_graph_representation);
	ClassDB::bind_method(D_METHOD("handle_event", "event_name"), &GdPPG::handle_event);

	ADD_SIGNAL(MethodInfo("ppg_puzzle_complete"));
	ADD_SIGNAL(MethodInfo("ppg_object_state_change", PropertyInfo(Variant::STRING, "object_name"), PropertyInfo(Variant::STRING, "new_state_name")));
	ADD_SIGNAL(MethodInfo("ppg_node_active", PropertyInfo(Variant::OBJECT, "noderef")));
	ADD_SIGNAL(MethodInfo("ppg_node_complete", PropertyInfo(Variant::OBJECT, "noderef")));
	ADD_SIGNAL(MethodInfo("ppg_node_incomplete", PropertyInfo(Variant::OBJECT, "noderef")));
	ADD_SIGNAL(MethodInfo("ppg_event_no_effect", PropertyInfo(Variant::STRING, "object_name")));
	//ADD_SIGNAL(MethodInfo("network_peer_packet", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::POOL_BYTE_ARRAY, "packet")));

}

GdPPG::GdPPG() {
	this->initGdPPG();
}

void GdPPG::initGdPPG() {
	this->update_listener = new PPGUpdateListener(this);
	this->puzzGen = new PuzzleGenerator();
}
