import os
import os.path
import re

RUN_DIR = os.getcwd()
SCRIPT_DIR = os.path.dirname(__file__)
ROOT_DIR = "publish/json"
ABSOLUTE_DIR = os.path.join(SCRIPT_DIR, ROOT_DIR)

def GetFileList(dir, fileList):
    newDir = dir
    if os.path.isfile(dir):
        fileList.append(dir)
    elif os.path.isdir(dir):  
        for s in os.listdir(dir):
            newDir = os.path.join(dir,s)
            GetFileList(newDir, fileList)  
    return fileList

# relative path issues.
regex1 = '\\\"textures/(.*)\\.plist\\\"'
pattern1 = re.compile(regex1)
regex2 = '\\\"fonts/(.*)\\.ttf\\\"'
pattern2 = re.compile(regex2)
# png to pvr.ccz
regex = '\\\"\\.\\.\\/textures/(.*)\\.png\\\"'
pattern = re.compile(regex2)
list = []
GetFileList(ABSOLUTE_DIR, list)
for v in list:
	ab_path = os.path.join(RUN_DIR, v)
	print "handling with ", ab_path
	handle = open(ab_path)
	text = handle.read()

	match1 = pattern1.search(text)
	while match1:
		old = match1.group()
		new = old[:1] + "../" + old[1:]
		text = text.replace(old, new)
		match1 = pattern1.search(text)
	match2 = pattern2.search(text)
	while match2:
		old = match2.group()
		new = old[:1] + "../" + old[1:]
		text = text.replace(old, new)
		match2 = pattern2.search(text)

	match = pattern.search(text)
	while match:
		old = match.group()
		new = old[:-4] + "pvr.ccz\""
		text = text.replace(old, new)
		match = pattern.search(text)
	
	handle.close()
	handle = open(ab_path, "w")
	handle.write(text)
	handle.close()