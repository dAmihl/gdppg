#include "PPGNodeRef.h"

void PPGNodeRef::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_object_name"), &PPGNodeRef::get_object_name);
	ClassDB::bind_method(D_METHOD("get_template_name"), &PPGNodeRef::get_template_name);
	ClassDB::bind_method(D_METHOD("get_current_state"), &PPGNodeRef::get_current_state);
	ClassDB::bind_method(D_METHOD("get_children"), &PPGNodeRef::get_children);
}

String PPGNodeRef::get_object_name() {
	return this->object_name;
}

String PPGNodeRef::get_template_name() {
	return this->template_name;
}

String PPGNodeRef::get_current_state() {
	return this->current_state;
}

Array PPGNodeRef::get_children() {
	return this->children;
}

void PPGNodeRef::set_object_name(String object_name) {
	this->object_name = object_name;
}

void PPGNodeRef::set_template_name(String template_name) {
	this->template_name = template_name;
}

void PPGNodeRef::set_current_state(String current_state) {
	this->current_state = current_state;
}

void PPGNodeRef::set_children(Array children) {
	this->children = children;
}

void PPGNodeRef::add_child(Ref<PPGNodeRef>* child) {
	this->children.append(child);
}
