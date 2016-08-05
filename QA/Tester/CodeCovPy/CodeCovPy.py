
import os, sys

#loop and record all .vtf files in this folder
def VisitDir(folderpath):
    vtffilelist = []
    for root,dirs,files in os.walk(folderpath):
        for filespath in files:
            if( filespath[-4:] == '.vtf' ):
                vtffilelist.append(os.path.join(root,filespath))
    return vtffilelist

                
#parse replay map file
def ParseReplayMap(replayMapFile):
    if os.path.isfile(replayMapFile) == False:
        print 'please input a valid file path'
        exit 
    replayFuncList = []
    filehandle = open(replayMapFile)
    for line in filehandle.readlines():
        beginNum = line.find('ADD_PARSER(replay_')
        if beginNum != -1:
            endNum = line.find(');')
            beginNum += len('ADD_PARSER(replay_')
            replayFuncList.append(line[beginNum:endNum])
    return replayFuncList
 
     
def InputCaseFolder():
    folderpath = raw_input('please input the folder path your test case is in: \n')
    if os.path.isdir(folderpath) == True:
        print 'your test case is in: ' + folderpath + '\n'
        return folderpath
    else:
        print 'please input a valid folder path'
        exit
   
    
#key is replay function name while obj is a list of all .vtf files which call these functions      
def GenReplayfunc2CasefileTable(vtffilelist, replayFuncList):
    Table = {}.fromkeys(replayFuncList)  
        
    for filename in vtffilelist:
        filehandle = open(filename)
        for line in filehandle.readlines():
            for replayFunc in replayFuncList:
                if (replayFunc+'(') in line:
                    # key has no objects 
                    
                    if Table[replayFunc] == None:
                        Table[replayFunc] = [filename]  
                    else:
                        origObjList = Table[replayFunc]
                        origObjList.append(filename)
                        Table[replayFunc] = [origObjList]
    return Table              
                
                    
def FindUncalledFunc(replayFuncList, Table):
    UncalledReplayFunc = []        
    for replayFunc in replayFuncList:
        if Table[replayFunc] == None:
            UncalledReplayFunc.append(replayFunc)
    return UncalledReplayFunc
 
                    
if __name__ == '__main__':   
    vtffilelist = VisitDir(InputCaseFolder())
    print 'Case files are '
    print vtffilelist
    print '\n'
        
    replayFuncList = ParseReplayMap('S:\QA\VCSTester\VCSTester\VTxVCSParserMap.cpp')
    print 'Replay functions are '
    print replayFuncList
    print '\n'
    
    Table = GenReplayfunc2CasefileTable(vtffilelist, replayFuncList)
    print 'Replay function to case files table is '
    #print Table
    print '\n'
    
    UncalledReplayFunc = FindUncalledFunc(replayFuncList, Table)
    print 'Uncalled replay functions are '
    print UncalledReplayFunc
    print '\n'
    
    