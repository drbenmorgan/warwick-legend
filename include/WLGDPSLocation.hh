#ifndef WLGDPSLocation_h
#define WLGDPSLocation_h 1

#include <map>
#include "G4THitsMap.hh"
#include "G4ThreeVector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4TrackLogger.hh"

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This is a primitive scorer class for scoring energy deposit location
//
///////////////////////////////////////////////////////////////////////////////

class WLGDPSLocation : public G4VPrimitiveScorer
{
public:
  WLGDPSLocation(G4String name, G4int depth = 0);  // default unit
  WLGDPSLocation(G4String name, const G4String& unit, G4int depth = 0);
  virtual ~WLGDPSLocation();

protected:  // with description
  virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);

public:
  virtual void Initialize(G4HCofThisEvent*);
  virtual void EndOfEvent(G4HCofThisEvent*);
  virtual void clear();
  virtual void DrawAll();
  virtual void PrintAll();

  virtual void SetUnit(const G4String& unit);

private:
  G4int                          HCID;
  G4THitsMap<G4ThreeVector>*     EvtMap;
  std::map<G4int, G4TrackLogger> fCellTrackLogger;
};
#endif
