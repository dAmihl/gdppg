/* gdppg.h */

#ifndef GdPPG_H
#define GdPPG_H

#include "core/reference.h"
#include "core/print_string.h"
#include "Yaml2Puzzle.h"
#include "PuzzGen.h"
#include "PPGNodeRef.h"
#include "PPGUpdateListener.h"

class GdPPG : public Reference {
    GDCLASS(GdPPG, Reference);

	void initGdPPG();

	PPG::UPtr<PPG::Puzzle> currentPuzzle;
	PPG::WfcGenerator puzzGen;
	PPG::Context currentContext;

	HashMap<String, PPG::Ptr<PPG::Event>> events_map;
	HashMap<String, PPG::Object> objects_map;
	HashMap<String, PPG::State> states_map;

	Ref<PPGNodeRef> map_puzzlegraphnode_for_gdscript(PPG::GraphNode* node);

	PPGUpdateListener* update_listener;

protected:
    static void _bind_methods();

public:
	void generate_puzzle();
	void add_object(Variant objectData);
	void add_rule(Variant ruleData);
	String get_puzzle_textual_representation();
	Ref<PPGNodeRef> get_puzzle_graph_representation();
	void handle_event(String event_name);
	void generate_puzzle_by_yaml_string(String yaml_str);
	void generate_puzzle_by_yaml_file(String file_name);

private:
	void generate_events_map(PPG::EventVec events);

    GdPPG();
};

#endif // GdPPG_H
