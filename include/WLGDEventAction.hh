#ifndef WLGDEventAction_h
#define WLGDEventAction_h 1

#include <vector>
#include <algorithm>
#include <numeric>

#include "G4THitsMap.hh"
#include "G4ThreeVector.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class WLGDEventAction : public G4UserEventAction
{
public:
  WLGDEventAction()          = default;
  virtual ~WLGDEventAction() = default;

  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);

  // to create columns for Ntuple
  std::vector<G4double>& GetHitEdep() { return edep; }
  std::vector<G4double>& GetHitTime() { return thit; }
  std::vector<G4double>& GetHitxLoc() { return xloc; }
  std::vector<G4double>& GetHityLoc() { return yloc; }
  std::vector<G4double>& GetHitzLoc() { return zloc; }

  // tajectory methods
  std::vector<G4int>&    GetTrjPDG() { return trjpdg; }
  std::vector<G4int>&    GetTrjEntries() { return trjnpts; }
  std::vector<G4double>& GetTrjXVtx() { return trjxvtx; }
  std::vector<G4double>& GetTrjYVtx() { return trjyvtx; }
  std::vector<G4double>& GetTrjZVtx() { return trjzvtx; }
  std::vector<G4double>& GetTrjXPos() { return trjxpos; }
  std::vector<G4double>& GetTrjYPos() { return trjypos; }
  std::vector<G4double>& GetTrjZPos() { return trjzpos; }

private:
  // methods
  G4THitsMap<G4int>*         GetIntHitsCollection(G4int hcID, const G4Event* event) const;
  G4THitsMap<G4double>*      GetHitsCollection(G4int hcID, const G4Event* event) const;
  G4THitsMap<G4ThreeVector>* GetVecHitsCollection(G4int hcID, const G4Event* event) const;

  std::vector<int> FilterTrajectories(int item, std::vector<G4int>& tid, std::vector<G4int>& pid)
  {
    int idx = 0;
    int pidx = 0;
    std::vector<int> result;
    auto it = std::find(tid.begin(), tid.end(), item);

    while (it != tid.end()) // find all links in the chain
    {
      idx = (it - tid.begin()); // location of id
      result.push_back(idx);

      pidx = pid.at(idx); // next to look for
      it = std::find(tid.begin(), tid.end(), pidx);
    }

    return result;
  }

  // data members
  // hit data
  G4int                 fTidID  = -1;
  G4int                 fPidID  = -1;
  G4int                 fLocID  = -1;
  G4int                 fTimeID = -1;
  G4int                 fEdepID = -1;
  std::vector<G4int>    htrid;
  std::vector<G4int>    hpaid;
  std::vector<G4double> edep;
  std::vector<G4double> thit;
  std::vector<G4double> xloc;
  std::vector<G4double> yloc;
  std::vector<G4double> zloc;

  // trajectory data
  std::vector<G4int>    trjpdg;
  std::vector<G4int>    trjnpts;
  std::vector<G4double> trjxvtx;
  std::vector<G4double> trjyvtx;
  std::vector<G4double> trjzvtx;
  std::vector<G4double> trjxpos;
  std::vector<G4double> trjypos;
  std::vector<G4double> trjzpos;
};

#endif
