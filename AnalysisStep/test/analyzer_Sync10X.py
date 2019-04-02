
#DATA_TAG = "ReReco" # Change to PromptReco for Run2016 period H
LEPTON_SETUP = 2018  # current default = 2018 
ELECORRTYPE = "None" # "None" to switch off
ELEREGRESSION = "None" # "None" to switch off
APPLYMUCORR = False  # Switch off muon scale corrections
APPLYJEC = False     #
APPLYJER = False     #
RECORRECTMET = False #
KINREFIT = False    # control KinZFitter (very slow)
PROCESS_CR = False   # Uncomment to run CR paths and trees
#ADDLOOSEELE = True  # Run paths for loose electrons
APPLYTRIG = False    # Skip events failing required triggers. They are stored with sel<0 if set to False 
#KEEPLOOSECOMB = True # Do not skip loose lepton ZZ combinations (for debugging)
ADDZTREE = False      # Add tree for Z analysis

# tau parameters
TAUCUT = "pt>15"
APPLYTESCORRECTION = False # shift the central value of the tau energy scale before computing up/down variations
TAUDISCRIMINATOR = "byIsolationMVA3oldDMwoLTraw"


PD = ""
MCFILTER = ""


XSEC    = 33.49 # fb 
GENXSEC = XSEC
GENBR   = 0.00014    # 4lbb
#GENBR  = 0.000015   # 4ltautau
#GENBR  = 0.0000023  # 6l2nu
#GENBR  = 0.00000054 # 4lgammagamma



#For DATA: 
#IsMC = False
#PD = "DoubleMu"


# Get absolute path
import os
PyFilePath = os.environ['CMSSW_BASE'] + "/src/ZZXAnalysis/AnalysisStep/test/"

### ----------------------------------------------------------------------
### Standard sequence
### ----------------------------------------------------------------------

execfile(PyFilePath + "analyzer.py")
execfile(PyFilePath + "prod/pyFragments/RecoProbabilities.py")

if not IsMC:
	process.source.inputCommands = cms.untracked.vstring("keep *", "drop LHERunInfoProduct_*_*_*", "drop LHEEventProduct_*_*_*") ###FIXME In 9X this removes all collections for MC

### ----------------------------------------------------------------------
### Replace parameters
### ----------------------------------------------------------------------

process.source.fileNames = cms.untracked.vstring(


### HH files
    'root://eoscms//eos/cms/store/user/covarell/HH/SM/4lbb/testMINIAOD_HHSM_4lbb_1.root'
    #'root://eoscms//eos/cms/store/user/covarell/HH/SM/4lgammagamma/testMINIAOD_HHSM_4lgammagamma_1.root'
    #'root://eoscms//eos/cms/store/user/covarell/HH/SM/4ltautau/testMINIAOD_HHSM_4ltautau_0.root' 
    #'root://eoscms//eos/cms/store/user/covarell/HH/SM/6l2nu/testMINIAOD_HHSM_4lWW_1.root'


    )

#process.calibratedPatElectrons.isSynchronization = cms.bool(True)
process.calibratedMuons.isSynchronization = cms.bool(True)

process.maxEvents.input = -1
#process.source.skipEvents = cms.untracked.uint32(5750)

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


### ----------------------------------------------------------------------
### Analyzer for Plots
### ----------------------------------------------------------------------


#process.source.eventsToProcess = cms.untracked.VEventRange("1:8670")

# Debug
process.dumpUserData =  cms.EDAnalyzer("dumpUserData",
     dumpTrigger = cms.untracked.bool(True),
     muonSrcs = cms.PSet(
#       slimmedMuons = cms.InputTag("slimmedMuons"),
        muons = cms.InputTag("appendPhotons:muons"),
     ),
     electronSrcs = cms.PSet(
#       slimmedElectron = cms.InputTag("slimmedElectrons"),
        electrons = cms.InputTag("appendPhotons:electrons"),
#        RSE = cms.InputTag("appendPhotons:looseElectrons"),
#        TLE = cms.InputTag("appendPhotons:electronstle"), 
     ),
     candidateSrcs = cms.PSet(
        Z     = cms.InputTag("ZCand"),
#        ZRSE     = cms.InputTag("ZCandlooseEle"),
#        ZTLE     = cms.InputTag("ZCandtle"),
        ZZ  = cms.InputTag("ZZCand"),
#        ZZRSE     = cms.InputTag("ZZCandlooseEle"),
#        ZZTLE     = cms.InputTag("ZZCandtle"),
        ZLL  = cms.InputTag("ZLLCand"),
        ZL  = cms.InputTag("ZlCand"),
     ),
     jetSrc = cms.InputTag("cleanJets"),
     photonSrc = cms.InputTag("pikaPhotons"),
)

# Create lepton sync file
#process.PlotsZZ.dumpForSync = True;
#process.p = cms.EndPath( process.PlotsZZ)

# Keep all events in the tree, even if no candidate is selected
#process.ZZTree.skipEmptyEvents = False

# replace the paths in analyzer.py
#process.trees = cms.EndPath(process.ZZTree)

#Dump reconstructed variables
#process.appendPhotons.debug = cms.untracked.bool(True)
#process.fsrPhotons.debug = cms.untracked.bool(True)
#process.dump = cms.Path(process.dumpUserData)

#Print MC history
#process.mch = cms.EndPath(process.printTree)


#Monitor memory usage
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#    ignoreTotal = cms.untracked.int32(1)
#)
