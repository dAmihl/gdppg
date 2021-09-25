/* gdppg.cpp */

#include "gdppg.h"

void GdPPG::generate_puzzle() {
	currentPuzzle = puzzGen.generatePuzzle(c);
	currentPuzzle->setUpdateListener(update_listener);
}

void GdPPG::generate_puzzle_by_yaml_file(String file_name) {

	Yaml2Puzzle y2p;
	currentPuzzle = y2p.generatePuzzleByFile(file_name.ascii().get_data());
	currentPuzzle->setUpdateListener(this->update_listener);
	generate_events_map(currentPuzzle->getContext().getEvents());
}

void GdPPG::generate_puzzle_by_yaml_string(String yaml_str) {

	Yaml2Puzzle *y2p = new Yaml2Puzzle();
	currentPuzzle = y2p->generatePuzzleByString(yaml_str.ascii().get_data());
	currentPuzzle->setUpdateListener(update_listener);
	generate_events_map(currentPuzzle->getContext().getEvents());
}

void GdPPG::add_object(Variant objectData) {

	String object_name = objectData.call("get_object_name");
	Array states = objectData.call("get_states");
	Dictionary transitions = objectData.call("get_transitions");
	String default_state = objectData.call("get_default_state");
	Dictionary events_reversible = objectData.call("get_events_reversible");

	auto tmpObject = c.add<PPG::Object>(object_name.ascii().get_data());
	tmpObject->setTemplateName(object_name.ascii().get_data());

	HashMap<String, PPG::State> stateMap;
	Vector<PPG::State> statesList;

	for (int i = 0; i < states.size(); i++) {
		String stateName = states[i];
		PPG::State tmpState(stateName.ascii().get_data());
		stateMap.set(stateName, tmpState);
		statesList.push_back(tmpState);
	}

	PPG::StateTransition *stateTransition = new PPG::StateTransition();

	for (int j = 0; j < transitions.size(); j++) {
		String event_name = transitions.get_key_at_index(j);
		Array state_pairs = transitions.get_value_at_index(j);

		for (int i = 0; i < state_pairs.size(); i++) {
			Array state_pair = state_pairs.get(i);
			String left_state = state_pair.get(0);
			String right_state = state_pair.get(1);

			auto& tmpS1 = stateMap.get(left_state);
			auto& tmpS2 = stateMap.get(right_state);
			/*states_map.set(left_state, tmpS1);
			states_map.set(right_state, tmpS2);*/
			stateTransition->addTransition(event_name.ascii().get_data(), tmpS1, tmpS2);
		}

		auto tmpEvent = c.add<PPG::Event>(event_name.ascii().get_data(), tmpObject);
		bool reversible = events_reversible.get(event_name, false);
		tmpEvent->setIsReversible(reversible);
		events_map.set(event_name, tmpEvent);
	}
	tmpObject->setStateTransition(*stateTransition);

	PPG::State defSt = PPG::STATE_ANY;
	if (default_state.empty()) {
		defSt = statesList.get(0);
	} else {
		defSt = stateMap.get(default_state);
	}
	// First state in array is default state
	tmpObject->setCurrentState(defSt);

	objects_map.set(object_name, tmpObject);
}

void GdPPG::add_rule(Variant ruleData) {
	String lh_object = ruleData.call("get_lh_object");
	String lh_state = ruleData.call("get_lh_state");
	String rh_object = ruleData.call("get_rh_object");
	String rh_state = ruleData.call("get_rh_state");
	String rule_type = ruleData.call("get_rule_type");

	PPG::Ptr<PPG::Object> lh_ppg_object = objects_map.get(lh_object);
	PPG::State lh_ppg_state = PPG::STATE_ANY;
	if (!lh_state.empty()) {
		lh_ppg_state = states_map.get(lh_state);
	}

	PPG::Ptr<PPG::Object> rh_ppg_object = objects_map.get(rh_object);
	PPG::State rh_ppg_state = PPG::STATE_ANY;
	if (!rh_state.empty()) {
		rh_ppg_state = states_map.get(rh_state);
	}

	PPG::Rule::EPuzzleRuleType type;
	type = PPG::Rule::EPuzzleRuleType::BEFORE;

	if (rule_type == "AFTER") {
		type = PPG::Rule::EPuzzleRuleType::AFTER;
	} else if (rule_type == "STRICT_BEFORE") {
		type = PPG::Rule::EPuzzleRuleType::STRICT_BEFORE;
	} else if (rule_type == "STRICT_AFTER") {
		type = PPG::Rule::EPuzzleRuleType::STRICT_AFTER;
	}

	c.addRule(lh_ppg_object, lh_ppg_state, rh_ppg_object, rh_ppg_state, type);
}

String GdPPG::get_puzzle_textual_representation() {
	return String(this->currentPuzzle->getExtendedTextualRepresentation().c_str());
}

Ref<PPGNodeRef> GdPPG::get_puzzle_graph_representation() {
	PPG::Vec<PPG::GraphNode*> rootNodes = currentPuzzle->getGraphRepresentation();

	PPG::GraphNode* root = rootNodes.at(0);

	Ref<PPGNodeRef> ref = map_puzzlegraphnode_for_gdscript(root);

	return ref;
}

void GdPPG::handle_event(String event_name) {
	PPG::Ptr<PPG::Event> tmpEvent = events_map.get(event_name);
	currentPuzzle->handleEvent(*tmpEvent);
}


Ref<PPGNodeRef> GdPPG::map_puzzlegraphnode_for_gdscript(PPG::GraphNode *node) {
	Ref<PPGNodeRef> nodeRef;
	nodeRef.instance();

	PPG::Object& tmpObj = node->getObject();

	nodeRef->set_object_name(String(tmpObj.getObjectName().c_str()));
	nodeRef->set_template_name(String(tmpObj.getTemplateName().c_str()));
	nodeRef->set_current_state(String(tmpObj.getCurrentState().getName().c_str()));

	PPG::Vec<PPG::GraphNode*> children = node->getChildren();

	for (auto& c: children) {
		Ref<PPGNodeRef> child = map_puzzlegraphnode_for_gdscript(c);
		nodeRef->add_child(child);
	}

	return nodeRef;
}

void GdPPG::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_object", "ppg_object_data"), &GdPPG::add_object);
	ClassDB::bind_method(D_METHOD("add_rule", "ppg_rule_data"), &GdPPG::add_rule);
	ClassDB::bind_method(D_METHOD("generate_puzzle"), &GdPPG::generate_puzzle);
	ClassDB::bind_method(D_METHOD("generate_puzzle_by_yaml_file", "file_name"), &GdPPG::generate_puzzle_by_yaml_file);
	ClassDB::bind_method(D_METHOD("generate_puzzle_by_yaml_string", "yaml_string"), &GdPPG::generate_puzzle_by_yaml_string);
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

void GdPPG::generate_events_map(PPG::Vec<PPG::Ptr<PPG::Event>> events) {
	for (auto& it: events) {
		String obj_name = it->getRelatedObject().getObjectName().c_str();
		String event_name = it->getEventName().c_str();
		String key = obj_name + ":" + event_name;
		events_map.set(key, it);
	}
}



