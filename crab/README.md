# How to submit NanoAOD analysis jobs using CRAB

## Create a CMSSW work area and download NanoAODTools
log on to lxplus7 machine and go to your AFS work area at /afs/cern.ch/work/
```
cmsrel CMSSW_10_2_18
cd CMSSW_10_2_18/src
cmsenv
git cms-init   
git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools
scram b
cd PhysicsTools/NanoAODTools/crab
```

## Prepare input files

```
git clone -b 2016ana git@github.com:syuvivida/XtoYH.git

mv XtoYH/root_macro/* .
mv XtoYH/crab/*.sh .
mv XtoYH/crab/*.py .
mv XtoYH/crab/*.xml .
rm -rf XtoYH
```

## Submit jobs
Modify your favorite storage site, dataset, directory name in crab_cfg.py
Note, the T2 and T3 sites at Taiwan sometimes have corrupted files.
Although the jobs finish properly, some root files cannot be opened.
Sometimes it also takes a long time to transfer files from the woring tiers to
Taiwan tiers.
```
source /cvmfs/cms.cern.ch/crab3/crab_standalone.sh
cmsenv
voms-proxy-init -voms cms
crab submit crab_cfg.py
```

Check the status via
```
crab status -d <directoryName>
```

## Get job output
Open another terminal
```
cd CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/crab
source /cvmfs/cms.cern.ch/crab3/crab_standalone.sh
voms-proxy-init -voms cms
crab getoutput -d <directoryName>
```

If crab getoutput doesn't work somehow, you need to open a new terminal and run the script ./gfalListDataFile.sh
```
voms-proxy-init -voms cms
./gfalCopyDataFile.sh NMSSM_XToYHTo4b_MX-1000_TuneCUETP8M1_13TeV-madgraph-pythia8 histo nchc syu
```