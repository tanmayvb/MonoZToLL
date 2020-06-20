from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config, getUsernameFromSiteDB

config = Configuration()

config.section_("General")
config.General.requestName = 'NanoPost'
config.General.transferLogs=True
config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.scriptExe = 'crab_ana.sh'
config.JobType.inputFiles = ['FrameworkJobReport.xml','untuplizer.h','xAna_nano_nssm.C','NCU_ana.py','../scripts/haddnano.py'] #hadd nano will not be needed once nano tools are in cmssw
config.JobType.outputFiles = ['histo.root']
config.JobType.sendPythonFolder	 = True
config.JobType.allowUndistributedCMSSW = True
config.section_("Data")
config.Data.inputDataset ='/NMSSM_XToYHTo4b_MX-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16NanoAODv6-PUMoriond17_Nano25Oct2019_RP_102X_mcRun2_asymptotic_v7-v2/NANOAODSIM'
#config.Data.inputDBS = 'phys03'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 4

#config.Data.splitting = 'Automatic'
#eventsPerLumi = 100
#timePerEv = 4
#desiredTime = 60*60*100
#config.Data.unitsPerJob = desiredTime / (eventsPerLumi*timePerEv)



#config.Data.outLFNDirBase = '/store/user/%s/NanoPost' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'NanoTestPost'
config.section_("Site")
#config.Site.storageSite = "T2_CH_CERN"
#config.Site.storageSite = "T3_TW_NCU"

config.Site.storageSite = "T2_TW_NCHC"
#config.section_("User")
#config.User.voGroup = 'dcms'

