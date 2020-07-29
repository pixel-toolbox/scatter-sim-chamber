#ifndef SoEiXRS_CLASSES_DETECTORCONSTRUCTION_HPP_
#define SoEiXRS_CLASSES_DETECTORCONSTRUCTION_HPP_ 1

#include <tuple>

#include "G4VUserDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

namespace SoEiXRS {

class DetectorConstruction: public G4VUserDetectorConstruction {

public:
	DetectorConstruction();

	inline G4LogicalVolume* GetScoringVolume() const { return scoringVolume; }
	inline G4LogicalVolume* GetBlockingVolume() const { return blockingVolume; }

	G4VPhysicalVolume* Construct();

	virtual ~DetectorConstruction();

protected:

private:
	G4NistManager* nist;

	G4VPhysicalVolume* physWorld;

	G4LogicalVolume* scoringVolume = NULL;
	G4LogicalVolume* blockingVolume = NULL;
};

} /* namespace SoEiXRS */

#endif /* SoEiXRS_CLASSES_DETECTORCONSTRUCTION_HPP_ */
