
import os, sys
import shutil

#copy files in VTxFailedCopy.lis and VTxFailedXML.lis
def CopyFiles(lisfile, folder):
    shutil.copyfile('pvt_RunTime\VTxFailed.lis', folder + '\VTxFailed.lis')
    shutil.copyfile('pvt_RunTime\VTxFailedXML.lis', folder + '\VTxFailedXML.lis')
    shutil.copyfile('pvt_RunTime\VTxFailedCopy.lis', folder + '\VTxFailedCopy.lis')
    filehandle = open(lisfile)
    for line in filehandle:
        targetfile = line.split('\\')[-1]
        #targetfile = line[:3] + folder + '\\' + line[3:-1]
        line = line[:-1]
        targetfile = line[:3] + folder + '\\' +targetfile[:-1]
        print line
        print targetfile
        shutil.copyfile(line, targetfile)
    filehandle.close()

#Generate VTxFailedCopy.lis based on VTxFailed.lis
def CreateFailedCopylisFile(FailedlisFile):
    filehandlecopy = open('pvt_RunTime\VTxFailedCopy.lis', 'w')
    filehandle = open(FailedlisFile)
    for line in filehandle:
        if line[:15]=='Z:\Transcripts\\':
            line = line[:15] + line[16:]
            filehandlecopy.write(line)
    filehandlecopy.close()
    filehandle.close()

#Generate VTxFailedXML.lis based on VTxFailed.lis
def CreateFailedXMLlisFile(FailedlisFile, outfolder):
    filehandlecopy = open('pvt_RunTime\VTxFailedXML.lis', 'w')
    filehandle = open(FailedlisFile)
    for line in filehandle:
        line = line[:15] + outfolder + '\\' + line[15:-5]
        line1 = line + '.baseline.xml\n'
        line2 = line + '.compare.xml\n'
        filehandlecopy.write(line1)
        filehandlecopy.write(line2)
    filehandlecopy.close()
    filehandle.close()

def main(argv):
    CreateFailedCopylisFile('pvt_RunTime\VTxFailed.lis')
    CreateFailedXMLlisFile('pvt_RunTime\VTxFailedCopy.lis', 'out_vs2012_win64')
    CopyFiles('pvt_RunTime\VTxFailedCopy.lis', argv)
    CopyFiles('pvt_RunTime\VTxFailedXML.lis', argv)
                    
if __name__ == '__main__':
    if( len(sys.argv) == 1 ):
        # if running without argument, show help
        print("Wrong parameters.")
        sys.exit(1)

    main(sys.argv[1])
