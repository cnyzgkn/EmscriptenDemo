
import os, sys

#Count number of .xml files in Data folder
def CountXmlFilesinDataFolder(folderPath):
    numOfXmlFilesinDataFolder = 0;
    
    for root,dirs,files in os.walk(folderPath):
        for filesPath in files:
            if( filesPath[-4:] == '.xml' ):
                if( root[-5:] == '\Data' ):
                    numOfXmlFilesinDataFolder += 1
    print 'Number of xml files that are in Data folder '
    print numOfXmlFilesinDataFolder
    print '\n'
    return numOfXmlFilesinDataFolder

#loop and record useless .xml files in this folder
def PrintUselessXmlFiles(folderPath):
    numOfUselessXmlFiles = 0;
    UselessXmlFileList = []
    for root,dirs,files in os.walk(folderPath):
        for filesPath in files:
            if( filesPath[-4:] == '.xml' ):
                if( not root[-5:] == '\Data' ):
                    if( not IsXmlUseful(os.path.join(root,filesPath)) ):
                        UselessXmlFileList.append(os.path.join(root,filesPath))
                        numOfUselessXmlFiles += 1
    print 'Number of useless xml files '
    print numOfUselessXmlFiles
    print '\n'
    return UselessXmlFileList

#if this .xml file is useful
def IsXmlUseful(filesPath):
    fileHandle = open(filesPath)
    for line in fileHandle.readlines():
        if line.find('body') != -1 or line.find('equation') != -1 or line.find('constraint') != -1:
            return True
    return False    
     
def InputCaseFolder():
    folderpath = raw_input('please input the folder path your test case is in: \n')
    if os.path.isdir(folderpath) == True:
        print 'your test case is in: ' + folderpath + '\n'
        return folderpath
    else:
        print 'please input a valid folder path'
        exit

def OutputToFile(fileList, outputFile):
    fileHandle = open(outputFile, 'w')
    for line in fileList:
        fileHandle.write(line + '\n')
    fileHandle.close()
                    
if __name__ == '__main__':
    CountXmlFilesinDataFolder(InputCaseFolder())
    UselessXmlfilelist = PrintUselessXmlFiles(InputCaseFolder())
    OutputToFile(UselessXmlfilelist, 'Z:\\UselessXmlfilelist.txt')
        
    
    
