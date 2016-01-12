from Bjontegaard import *
from Utilities import *
import Configuration
import os
from joblib import Parallel, delayed  


for gopStructure in Configuration.gopStructureList:
	bdRateFile = makeBDRateFile(gopStructure)
	rdValuesFile = makeRDValuesFile(gopStructure)
	acValuesFile = makeACValuesFile(gopStructure)
	for [sequence, numFrames] in Configuration.sequenceList:
		print >> bdRateFile, sequence,

		refBDResults = []
		refTimeResults = []
		optParams = Configuration.optParamsRef
		pathToBin = Configuration.pathToRefBin
		rdFileLine = {}
		acFileLines = {}
		if Configuration.RUN_REFERENCE:
			if Configuration.RUN_PARALLEL:
				Parallel(n_jobs=Configuration.NUM_THREADS)(delayed(runParallelSims)(sequence,numFrames, gopStructure, qp, pathToBin, optParams, 'ref') for qp in Configuration.qpList)
			else:
				for qp in Configuration.qpList:
					runParallelSims(sequence,numFrames, gopStructure, qp, pathToBin, optParams, 'ref') 

		for qp in Configuration.qpList:
			[gopPath, seqPath, resultsPath] = treatConfig(sequence, gopStructure, qp, 'ref')
			parsed = parseOutput(resultsPath)
			if parsed:
				[bd, time] = parsed
				acLines = parseACOutput(resultsPath)
			else:
				[bd, time] = [['N/A'], 'N/A']
				acLines = ['N/A','N/A','N/A','N/A']

			rdFileLine[qp] = '\t'.join([str(x) for x in [sequence]+[qp]+bd+[time]]) + '\t'
			acFileLines[qp] = []
			for line in acLines:
				acFileLines[qp].append('\t'.join([str(x) for x in [sequence,qp]+ line]) + '\t') 
			refBDResults.append(bd)
			refTimeResults.append(time)
		

		for testIdx in range(Configuration.N_TESTS):
			testBDResults = []
			testTimeResults = []
			optParams = Configuration.optParamsTestList[testIdx]
			pathToBin = Configuration.pathToTestBinList[testIdx]
			testName = Configuration.testNameList[testIdx]
			if Configuration.RUN_TEST:
				if Configuration.RUN_PARALLEL:
					Parallel(n_jobs=Configuration.NUM_THREADS)(delayed(runParallelSims)(sequence,numFrames, gopStructure, qp, pathToBin, optParams, 'test', testIdx) for qp in Configuration.qpList)	
				else:
					for qp in Configuration.qpList:
						runParallelSims(sequence,numFrames, gopStructure, qp, pathToBin, optParams, 'test', testIdx)


			for qp in Configuration.qpList:
				[gopPath, seqPath, resultsPath] = treatConfig(sequence, gopStructure, qp, 'test', testIdx)
				parsed = parseOutput(resultsPath)
				if parsed:
					[bd, time] = parsed
					acLines = parseACOutput(resultsPath)
				else:
					[bd, time] = [['N/A'], 'N/A']
					acLines = ['N/A','N/A','N/A','N/A']

				rdFileLine[qp] += '\t'.join([str(x) for x in bd+[time]]) + '\t'
				#acFileLines[qp] = []
				i = 0
				for line in acLines:
					acFileLines[qp][i] += ('\t'.join([str(x) for x in line]) + '\t') 
					i += 1
				testBDResults.append(bd)
				testTimeResults.append(time)

			calcAndPrintBDRate(refTimeResults,refBDResults,testTimeResults,testBDResults, bdRateFile)
		for qp in Configuration.qpList:
			print >> rdValuesFile, rdFileLine[qp]
			for line in acFileLines[qp]:
				print >> acValuesFile, line

		print >> bdRateFile, '\n',

	bdRateFile.close()
	rdValuesFile.close()
	acValuesFile.close()
