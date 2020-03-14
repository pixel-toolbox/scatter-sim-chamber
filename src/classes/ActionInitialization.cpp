#include "ActionInitialization.hpp"

namespace SoEiXRS {

ActionInitialization::ActionInitialization(double energy, double energyFluc,
		double sourcePosition, double filtCollSize) :
		primaryGeneratorAction(
				new PrimaryGeneratorAction(energy, energyFluc, sourcePosition,
						filtCollSize)), steppingAction(new SteppingAction()) {
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
