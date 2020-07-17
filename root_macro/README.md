# How to run this macro

You can find an example root file at /afs/cern.ch/work/s/syu/public/forTiKai/nssm_nano.root

First you need to download the untuplizer.h and xAna_nano_nssm.C from the github. Then, run

```
root -q -b 'xAna_nano_nssm.C++("nssm_nano.root")'
```

Note, if you need to find out more details about the definition of each variables. Within ROOT, type:
```
Events->GetBranch("SoftActivityJetNjets5")->GetTitle()
```

Or check more detailed correponding variables in the miniAOD by going through the python files in
```
 $CMSSW_RELEASE_BASE/src/PhysicsTools/NanoAOD/python/
```

For example, the jet and b-tagging related variables are defined here:
```
$CMSSW_RELEASE_BASE/src/PhysicsTools/NanoAOD/python/jets_cff.py
```