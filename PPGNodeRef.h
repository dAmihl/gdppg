#pragma once

#ifndef PPGNodeRef_H
#define PPGNodeRef_H

#include "core/reference.h"

class PPGNodeRef : public Reference {

	GDCLASS(PPGNodeRef, Reference);

public:
	String get_object_name();
	String get_template_name();
	String get_current_state();
	Array get_children();

	void set_object_name(String object_name);
	void set_template_name(String template_name);
	void set_current_state(String current_state);
	void set_children(Array children);

	void add_child(Ref<PPGNodeRef> *child);

private:
	String object_name;
	String template_name;
	String current_state;
	Array children;

protected:
	static void _bind_methods();

};

#endif
