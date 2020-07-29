#ifndef SoEiXRS_CLASSES_SteppingAction_HPP_
#define SoEiXRS_CLASSES_SteppingAction_HPP_ 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <fstream>
#include <vector>

class B1EventAction;

class G4LogicalVolume;

namespace SoEiXRS {

struct energyPositionInformation {
	inline energyPositionInformation(double x, double y, double energyInkeV) :
			x(x), y(y), energyInkeV(energyInkeV) {
	}
	double x, y; // in meter
	double energyInkeV;
};

class SteppingAction: public G4UserSteppingAction {

public:
	SteppingAction();
	virtual ~SteppingAction();

	virtual void UserSteppingAction(const G4Step*);

	std::vector<energyPositionInformation>* resultElectronPosEnergy = NULL;
	std::vector<energyPositionInformation>* resultPhotonPosEnergy = NULL;

private:
	G4LogicalVolume* fScoringVolume = NULL;
	G4LogicalVolume* blockingVolume = NULL;
};

} /* namespace SoEiXRS */

#endif /* SoEiXRS_CLASSES_SteppingAction_HPP_ */
