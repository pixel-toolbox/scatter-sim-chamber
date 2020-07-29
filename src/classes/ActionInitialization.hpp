#ifndef SoEiXRS_CLASSES_ACTIONINITIALIZATION_HPP_
#define SoEiXRS_CLASSES_ACTIONINITIALIZATION_HPP_ 1

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.hpp"
#include "SteppingAction.hpp"

namespace SoEiXRS {

class ActionInitialization: public G4VUserActionInitialization {
public:
	ActionInitialization();

	virtual void Build() const;

	virtual ~ActionInitialization();

	PrimaryGeneratorAction* getPrimaryGeneratorAction();
	SteppingAction* getSteppingAction();
private:

	PrimaryGeneratorAction* primaryGeneratorAction;
	SteppingAction* steppingAction;
};

} /* namespace SoEiXRS */

#endif /* SoEiXRS_CLASSES_ACTIONINITIALIZATION_HPP_ */
