#include "G4RunManager.hh"

#include <iostream>
#include <vector>
#include <tuple>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

#include "include.hh"
#include "define.hh"

#include "FTFP_BERT.hh"

#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4EmPenelopePhysics.hh"

using namespace SoEiXRS;

int main(int argc, char* argv[]) {

	// construct the default run manager
	G4RunManager* runManager = new G4RunManager();

	// set mandatory initialization classes
	G4VModularPhysicsList* physicsList = new FTFP_BERT;
	runManager->SetUserInitialization(physicsList);
	runManager->SetUserInitialization(new DetectorConstruction());
	ActionInitialization* actionInitialization = new ActionInitialization();
	runManager->SetUserInitialization(actionInitialization);

	// get the pointer to the UI manager and set verbosities
	G4UImanager* UI = G4UImanager::GetUIpointer();
	UI->ApplyCommand("/run/verbose 0");
	UI->ApplyCommand("/event/verbose 0");
	UI->ApplyCommand("/tracking/verbose 0");
	UI->ApplyCommand("/run/setCut  0.00001 mm");
	UI->ApplyCommand("/cuts/setLowEdge 250 eV");
	UI->ApplyCommand("/process/em/fluo true");

	runManager->Initialize();


	/*G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialise();
	UI->ApplyCommand("/control/execute vis.mac");
	UI->ApplyCommand("/vis/verbosity 2");*/

	PrimaryGeneratorAction* primaryGeneratorAction = actionInitialization->getPrimaryGeneratorAction();

	SteppingAction* steppingAction = actionInitialization->getSteppingAction();

	int energies[] = {50, 75, 100, 150, 200, 300, 500, 1000, 2000, 3000};
	std::vector<std::string> incomingParticleType = {"gamma", "e-"};

	UI->ApplyCommand("/control/execute setup.mac");
	for (int energy : energies) {
		for (std::string particleType : incomingParticleType) {
			std::cout << energy << "keV " << particleType << "s:";
			std::cout.flush();

			std::vector<energyPositionInformation> resultElectronPosEnergy;
			std::vector<energyPositionInformation> resultPhotonPosEnergy;

			resultElectronPosEnergy.reserve(1000);
			resultPhotonPosEnergy.reserve(1000);

			steppingAction->resultElectronPosEnergy = &resultElectronPosEnergy;
			steppingAction->resultPhotonPosEnergy = &resultPhotonPosEnergy;

			//primaryGeneratorAction->setEnergy(energy);
			UI->ApplyCommand("/gps/ene/mono " + std::to_string(energy) + " keV");
			UI->ApplyCommand("/gps/particle " + particleType);

			int runs = 1000;
			for (int r = 0; r < runs; r++) {
				// start a run
				if (r % 10 == 0) {
					std::cout << ".";
					std::cout.flush();
				}
				runManager->BeamOn(1000);

				/*std::string s;

				std::cout << "done >";
				std::cout.flush();
				std::cin >> s;*/
			}

			std::cout << std::endl << "writing output file ..." << std::endl;

			std::ofstream output_electron_file(
					"output_" + particleType + "_" + std::to_string(energy) + "keV.ele.dat");
			std::ofstream output_photon_file(
					"output_" + particleType + "_" + std::to_string(energy) + "keV.pho.dat");

			for (auto res : resultElectronPosEnergy) {
				output_electron_file << res.x << " " << res.y << " "
						<< res.energyInkeV << std::endl;
			}

			for (auto res : resultPhotonPosEnergy) {
				output_photon_file << res.x << " " << res.y << " "
						<< res.energyInkeV << std::endl;
			}

			output_electron_file.close();
			output_photon_file.close();
		}
	}


	/*std::string s;

	std::cout << "done >";
	std::cout.flush();
	std::cin >> s;*/

	// job termination
	delete runManager;
	//delete visManager;

	return 0;
}
