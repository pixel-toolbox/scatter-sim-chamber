#include "SteppingAction.hpp"

#include "DetectorConstruction.hpp"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"

#define USE_MAX true

namespace SoEiXRS {

SteppingAction::SteppingAction(){}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
	if (!fScoringVolume) {
		const DetectorConstruction* detectorConstruction =
				static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
		fScoringVolume = detectorConstruction->GetScoringVolume();
	}

	// get volume of the current step
	G4LogicalVolume* volume =
			step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

	// check if we are in scoring volume
	if (volume != fScoringVolume)
		return;

	auto energy = step->GetTrack()->GetKineticEnergy() / keV;

	//std::cout << energy << std::endl;
	resultVector->push_back(energy);

	//std::cout << "energy: " << energy << std::endl;

	step->GetTrack()->SetTrackStatus(fStopAndKill);
}

} /* namespace SoEiXRS */
