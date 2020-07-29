#include "PrimaryGeneratorAction.hpp"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Electron.hh"
#include "G4SystemOfUnits.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "Randomize.hh"

#include "../define.hh"

namespace SoEiXRS {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
		G4VUserPrimaryGeneratorAction(), fParticleGun(0), de(
				time(0))/*, directDist(-3.14, +3.14)*/ {
	fParticleGun = new G4GeneralParticleSource();
	/*G4int n_particle = PARTICLES_IN_GUN;
	fParticleGun = new G4ParticleGun(n_particle);

	G4ParticleDefinition* particle = G4Gamma::GammaDefinition();
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	fParticleGun->SetParticlePosition(
			G4ThreeVector(0, 0, -0.5*m));*/
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
	delete fParticleGun;
}

/*void PrimaryGeneratorAction::setEnergy(double energy) {
	fParticleGun->SetParticleEnergy(energy);
}*/

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
	/*double angle_x = 3.14;
	double angle_y = 3.14;

	angle_x = directDist(de);
	angle_y = directDist(de);

	double vec_x = sin(angle_x);
	double vec_y = sin(angle_y);
	double vec_z = 1-sqrt(vec_x*vec_x+vec_y*vec_y);

	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(vec_x, vec_y, vec_z));*/
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

} /* namespace SoEiXRS */
