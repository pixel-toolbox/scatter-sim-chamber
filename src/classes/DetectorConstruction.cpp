#include "DetectorConstruction.hpp"

namespace SoEiXRS {

DetectorConstruction::DetectorConstruction() :
		G4VUserDetectorConstruction(), nist(G4NistManager::Instance()) {

	double world_sizeXY = 2*m;
	double world_sizeZ = 10*m;

	/*Die Wandstärke ist 30mm (Edelstahl)
	 * die Abmessungen sind 2m x 1m
	 * mit einer Höhe von ca. 1m*/

	double wall_thickness = 30*mm;
	double size_x = 0.5*m;
	double size_y = 0.5*m;
	double size_z = 1*m;

	/// https://books.google.de/books?id=8REhrrTKZKwC&pg=PA25#v=onepage&q&f=false

	double a = 14.01 * g / mole;
	G4Element* elN = new G4Element("Nitrogen", "N", 7., a);
	a = 16.00 * g / mole;
	G4Element* elO = new G4Element("Oxygen", "O", 8., a);

	double density = 1.290 * mg / cm3;
	G4Material* air = new G4Material("Air", density, 2);
	air->AddElement(elN, 78.084 * perCent);
	air->AddElement(elO, 20.942 * perCent);

	density = 1.290 * mg / cm3;
	G4Material* vac = new G4Material("CustomVacuum", density, 2, kStateGas,
			293.15 * kelvin, atmosphere / ((double) pow(10, (5+3))));
	vac->AddElement(elN, 78.084 * perCent);
	vac->AddElement(elO, 20.942 * perCent);

	G4Box* solidWorld = new G4Box("WorldBox", 0.5 * world_sizeXY,
			0.5 * world_sizeXY, 0.5 * world_sizeZ);
	G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air,
			"WorldVolume");
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,
			"WorldPhysVolume", 0, false, 0, true);

	auto steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

	/// build the vacuum walls
	G4Box* vac_wall_box = new G4Box("VacChamberWallBox", size_x+wall_thickness,
			size_y+wall_thickness, size_z+wall_thickness);
	G4LogicalVolume* vac_wall_vol = new G4LogicalVolume(vac_wall_box, steel,
			"VacChamberWallVolume");
	G4VPhysicalVolume* vac_wall_physvol = new G4PVPlacement(0,
			G4ThreeVector(0, 0, -size_z), vac_wall_vol,
			"VacChamberWallPhysVolume", logicWorld, false, 0, true);

	/// build the vacuum chamber
	G4Box* vac_box = new G4Box("VacChamberBox", size_x,
			size_y, size_z);
	G4LogicalVolume* vac_vol = new G4LogicalVolume(vac_box, vac,
			"VacChamberVolume");
	G4VPhysicalVolume* vac_physvol = new G4PVPlacement(0,
			G4ThreeVector(0, 0, 0), vac_vol,
			"VacChamberPhysVolume", vac_wall_vol, false, 0, true);

	auto led = nist->FindOrBuildMaterial("G4_Pb");
	/// block where the filter would be
	G4Box* vac_blocker_box = new G4Box("VacBlockerBox", 4*cm,
			4*cm, wall_thickness/2);
	G4LogicalVolume* vac_blocker_vol = new G4LogicalVolume(vac_blocker_box, led,
			"VacBlockerVolume");
	G4VPhysicalVolume* vac_blocker_physvol = new G4PVPlacement(0,
			G4ThreeVector(0, 0, size_z+wall_thickness/2), vac_blocker_vol,
			"VacBlockerPhysVolume", vac_wall_vol, false, 0, true);

	/// build detector
	G4Box* det_box = new G4Box("DetectorBox", world_sizeXY*0.49,
			world_sizeXY*0.49, .5 * mm);
	G4LogicalVolume* det_vol = new G4LogicalVolume(det_box,
			nist->FindOrBuildMaterial("G4_Si"), "DetectorVolume");
	G4VPhysicalVolume* det_physvol = new G4PVPlacement(0,
			G4ThreeVector(0, 0, 3.75*m-0.5*m), det_vol,
			"DetectorPhysVolume", logicWorld, false, 0, true);

	scoringVolume = det_vol;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
	return physWorld;
}

DetectorConstruction::~DetectorConstruction() {
	// TODO Auto-generated destructor stub
}

} /* namespace SoEiXRS */
