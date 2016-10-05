import os
import sys

class MainHeader:
	def __init__(self):
		self.unRevision = ""
		self.unFirmwareSize = ""
		self.unChecksum = ""
		self.szPartNumber = ""

class SubHeader:
	def __init__(self):
		self.unDataSize	= ""
		self.unPathLength = ""
		self.unFlag = ""

class Packer:
	def __init__(self, path):
		self.m = MainHeader()
		self.p_dir = []
		self.p_file = []
		self.file_search(path)
	
	def file_search(self, path):
		try:
			files = os.listdir(path)
			for file in files:
				full_path = os.path.join(path, file)
				if os.path.isdir(full_path):
					self.p_dir.append(full_path)
					self.file_search(full_path)
				else:
					self.p_file.append(full_path)
		except:
			print "Except"

	def get_file_list(self):
		return self.p_file

	def get_dir_list(self):
		return self.p_dir

p = Packer(sys.argv[1])
