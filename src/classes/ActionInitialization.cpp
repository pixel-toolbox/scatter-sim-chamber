#include "ActionInitialization.hpp"

namespace SoEiXRS {

ActionInitialization::ActionInitialization() :
		primaryGeneratorAction(
				new PrimaryGeneratorAction()), steppingAction(new SteppingAction()) {
}

void ActionInitialization::Build() const {
	SetUserAction(primaryGeneratorAction);

	SetUserAction(steppingAction);
}

ActionInitialization::~ActionInitialization() {
}

PrimaryGeneratorAction* ActionInitialization::getPrimaryGeneratorAction() {
	return primaryGeneratorAction;
}

SteppingAction* ActionInitialization::getSteppingAction() {
	return steppingAction;
}

} /* namespace SoEiXRS */
