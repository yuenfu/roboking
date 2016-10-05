import os
import sys

class MainHeader:
	def __init__(self):
		self.unRevision = ""
		self.unFirmwareSize = ""
		self.unChecksum = ""
		self.szPartNumber = ""

class SubHeader:
	def __init__(self, path):
		self.unDataSize	= ""
		self.unPathLength = ""
		self.unFlag = ""		
		self.file_name = ""
		self.data = ""

		self.set_data(path)

	def set_data(self, path):
		self.file_name = path[path.find("/"):]
		self.unPathLength = len(self.file_name)
		with open(path, "rb") as f:
			self.data = f.read()
		self.unDataSize = len(self.data)

	def enc(self, data):
		ret_data = ""
		for i in data:
			ret_data += chr(~ord(i) & 0xff)
		return ret_data

	def view(self):
		print "[+] File name : " +self.file_name
		print "[+] unDataSize : " + str(self.unDataSize)
		print "[+] unPathLength : " + str(self.unPathLength)
		print "[+] unFlag : " + self.unFlag
		print "[+] Data : " + self.data[:10]
		print "\n"
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

for file in p.get_file_list():
	s = SubHeader(file)
	s.view()
