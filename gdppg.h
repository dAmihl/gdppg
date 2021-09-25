/* gdppg.h */

#ifndef GdPPG_H
#define GdPPG_H

#include "core/reference.h"
#include "core/print_string.h"
#include "PuzzGen.h"
#include "PPGUpdateListener.h"
#include "Yaml2Puzzle.h"

class GdPPG : public Reference {
    GDCLASS(GdPPG, Reference);

	PPG::UPtr<PPG::Puzzle> currentPuzzle;
	PPG::Generator puzzGen;
	PPG::Context c;

	HashMap<String, PPG::Ptr<PPG::Event>> events_map;
	HashMap < String, PPG::Ptr<PPG::Object>> objects_map;
	HashMap<String, PPG::State > states_map;

	Ref<PPGNodeRef> map_puzzlegraphnode_for_gdscript(PPG::GraphNode *node);
	PPGUpdateListener* update_listener;

protected:
    static void _bind_methods();

public:
	GdPPG() { update_listener = new PPGUpdateListener(this); }

	void generate_puzzle();
	void add_object(Variant objectData);
	void add_rule(Variant ruleData);
	String get_puzzle_textual_representation();
	Ref<PPGNodeRef> get_puzzle_graph_representation();
	void handle_event(String event_name);
	void generate_puzzle_by_yaml_string(String yaml_str);
	void generate_puzzle_by_yaml_file(String file_name);

private:
	void generate_events_map(PPG::Vec<PPG::Ptr<PPG::Event> > events);
};

#endif // GdPPG_H
